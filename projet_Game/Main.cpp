#include <array>
#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "DrawText.h"
#include "Global.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Ufo.h"
#include "Player.h"

int main()
{
	bool game_over = 0;
	bool next_level = 0;

	//The current level.
	unsigned short level = 0;
	unsigned short next_level_timer = NEXT_LEVEL_TRANSITION;

	//We'll use this to make the game frame rate independent.
	std::chrono::microseconds lag(0);

	std::chrono::steady_clock::time_point previous_time;

	
	//Random.
	std::mt19937_64 random_engine(std::chrono::system_clock::now().time_since_epoch().count());

	sf::Event event;

	sf::RenderWindow window(sf::VideoMode(SCREEN_RESIZE * SCREEN_WIDTH, SCREEN_RESIZE * SCREEN_HEIGHT), "CA-Space");
	
	//Resizing the screen.
	window.setView(sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)));

	sf::Sprite background_sprite;
	sf::Sprite powerup_bar_sprite;

	sf::Texture background_texture;
	background_texture.loadFromFile("Resources/Images/bg2.jpg");

	sf::Texture powerup_bar_texture;
	powerup_bar_texture.loadFromFile("Resources/Images/PowerupBar.png");

	EnemyManager enemy_manager;

	Player player;

	Ufo ufo(random_engine);

	background_sprite.setTexture(background_texture);
	background_sprite.scale(0.6f, 0.5f); 

	powerup_bar_sprite.setTexture(powerup_bar_texture);

	previous_time = std::chrono::steady_clock::now();

	while (window.isOpen())
	{
		//Making the game frame rate independent.
		std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time);

		lag += delta_time;

		previous_time += delta_time;

		while (FRAME_DURATION <= lag)
		{
			lag -= FRAME_DURATION;

			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
				{
					window.close();
				}
				}
			}

			if (player.get_dead_animation_over())
			{
				game_over = 1;
			}

			if (enemy_manager.reached_player(player.get_y()))
			{
				player.die();
			}

			if (!game_over)
			{
				if (!enemy_manager.get_enemies().size())
				{
					if (!next_level_timer)
					{
						next_level = 0;

						level++;
						next_level_timer = NEXT_LEVEL_TRANSITION;

						player.reset();

						enemy_manager.reset(level);

						ufo.reset(1, random_engine);
					}
					else //next level transition.
					{
						next_level = 1;

						next_level_timer--;
					}
				}
				else
				{
					player.update(random_engine, enemy_manager.get_enemy_bullets(), enemy_manager.get_enemies(), ufo);

					enemy_manager.update(random_engine);

					ufo.update(random_engine);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				game_over = 0;

				level = 0;

				player.reset();

				enemy_manager.reset(level);

				ufo.reset(1, random_engine);
			}

			if (FRAME_DURATION > lag)
			{
				window.clear();

				window.draw(background_sprite);

				if (!player.get_dead())
				{
					enemy_manager.draw(window);

					ufo.draw(window);

					if (0 < player.get_current_power())
					{
						powerup_bar_sprite.setColor(sf::Color(255, 255, 255));
						powerup_bar_sprite.setPosition(SCREEN_WIDTH - powerup_bar_texture.getSize().x - 0.25f * BASE_SIZE, 0.25f * BASE_SIZE);
						powerup_bar_sprite.setTextureRect(sf::IntRect(0, 0, powerup_bar_texture.getSize().x, BASE_SIZE));

						window.draw(powerup_bar_sprite);

						powerup_bar_sprite.setPosition(SCREEN_WIDTH - powerup_bar_texture.getSize().x - 0.125f * BASE_SIZE, 0.25f * BASE_SIZE);
						//length of the bar.
						powerup_bar_sprite.setTextureRect(sf::IntRect(0.125f * BASE_SIZE, BASE_SIZE, ceil(player.get_power_timer() * static_cast<float>(powerup_bar_texture.getSize().x - 0.25f * BASE_SIZE) / POWERUP_DURATION), BASE_SIZE));

						switch (player.get_current_power())
						{
						case 1:
						{
							powerup_bar_sprite.setColor(sf::Color(0, 146, 255));

							break;
						}
						case 2:
						{
							powerup_bar_sprite.setColor(sf::Color(255, 0, 0));

							break;
						}
						case 3:
						{
							powerup_bar_sprite.setColor(sf::Color(255, 219, 0));

							break;
						}
						case 4:
						{
							powerup_bar_sprite.setColor(sf::Color(219, 0, 255));
						}
						}

						window.draw(powerup_bar_sprite);
					}
				}

				player.draw(window);

				draw_text(0.25f * BASE_SIZE, 0.25f * BASE_SIZE, "Level: " + std::to_string(level + 1), window, sf::Color::White);

				if (1 == game_over)
				{
					draw_text(0.5f * (SCREEN_WIDTH - 5 * BASE_SIZE), 0.5f * (SCREEN_HEIGHT - BASE_SIZE), "Game over!", window, sf::Color::Red);
				}
				if (1 == next_level)
				{
					draw_text(0.5f * (SCREEN_WIDTH - 5.5f * BASE_SIZE), 0.5f * (SCREEN_HEIGHT - BASE_SIZE), "Next level!", window, sf::Color::White);
				}

				window.display();
			}
		}
	}
}