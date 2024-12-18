#pragma once

class EnemyManager
{
	
	unsigned short move_pause;
	
	unsigned short move_timer;

	//To use the randomness from the <random> library, we need to define the distribution.
	std::uniform_int_distribution<unsigned short> shoot_distribution;

	std::vector<Animation> enemy_animations;

	std::vector<Bullet> enemy_bullets;

	std::vector<Enemy> enemies;

	sf::Sprite enemy_bullet_sprite;

	sf::Texture enemy_bullet_texture;
public:
	EnemyManager();

	bool reached_player(unsigned short i_player_y) const;

	void draw(sf::RenderWindow& i_window);
	void reset(unsigned short i_level);
	void update(std::mt19937_64& i_random_engine);

	std::vector<Bullet>& get_enemy_bullets();

	std::vector<Enemy>& get_enemies();
};