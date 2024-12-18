//SO MANY CONSTANTS! AAAAAAAH!
#pragma once

#include <cmath>

constexpr unsigned char BASE_SIZE = 16; 
constexpr unsigned char ENEMY_BULLET_SPEED = 2; 
constexpr unsigned char ENEMY_HIT_TIMER_DURATION = 2; 
constexpr unsigned char ENEMY_MOVE_PAUSE_DECREASE = 1; 

constexpr unsigned char ENEMY_MOVE_PAUSE_MIN = 3; 
constexpr unsigned char ENEMY_MOVE_PAUSE_START = 63;
constexpr unsigned char ENEMY_MOVE_PAUSE_START_MIN = 47;
constexpr unsigned char ENEMY_MOVE_SPEED = 2;
constexpr unsigned char ENEMY_TYPES = 3;
constexpr unsigned char EXPLOSION_ANIMATION_SPEED = 2;

constexpr unsigned char FAST_RELOAD_DURATION = 7;
constexpr unsigned char NEXT_LEVEL_TRANSITION = 64;
constexpr unsigned char PLAYER_BULLET_SPEED = 4;
constexpr unsigned char PLAYER_MOVE_SPEED = 2;
constexpr unsigned char POWERUP_ANIMATION_SPEED = 16;
constexpr unsigned char POWERUP_SPEED = 2;
constexpr unsigned char POWERUP_TYPES = 4;
constexpr unsigned char RELOAD_DURATION = 31;
constexpr unsigned char SCREEN_RESIZE = 4;
constexpr unsigned char TOTAL_LEVELS = 8;
constexpr unsigned char UFO_ANIMATION_SPEED = 8;
constexpr unsigned char UFO_MOVE_SPEED = 1;

constexpr unsigned short ENEMY_SHOOT_CHANCE = 4096;
constexpr unsigned short ENEMY_SHOOT_CHANCE_INCREASE = 64;
constexpr unsigned short ENEMY_SHOOT_CHANCE_MIN = 1024;
constexpr unsigned short POWERUP_DURATION = 512;
constexpr unsigned short SCREEN_HEIGHT = 180;
constexpr unsigned short SCREEN_WIDTH = 320;

constexpr unsigned short UFO_TIMER_MAX = 1024;
constexpr unsigned short UFO_TIMER_MIN = 768;

constexpr std::chrono::microseconds FRAME_DURATION(16667);


struct Bullet
{
	bool dead;

	float real_x;
	float real_y;
	float step_x;
	float step_y;

	short x;
	short y;

	std::array<short, 3> previous_x;
	std::array<short, 3> previous_y;

	Bullet(float i_step_x, float i_step_y, short i_x, short i_y) :
		dead(0),
		real_x(i_x),
		real_y(i_y),
		step_x(i_step_x),
		step_y(i_step_y),
		x(i_x),
		y(i_y)
	{
		previous_x.fill(x);
		previous_y.fill(y);
	}

	void update()
	{
		if (!dead)
		{
			
			real_x += step_x;
			real_y += step_y;

			for (unsigned char a = 0; a < previous_x.size() - 1; a++)
			{
				previous_x[a] = previous_x[1 + a];
				previous_y[a] = previous_y[1 + a];
			}

			previous_x[previous_x.size() - 1] = x;
			previous_y[previous_y.size() - 1] = y;

			x = round(real_x);
			y = round(real_y);

			if (x <= -BASE_SIZE || y <= -BASE_SIZE || SCREEN_HEIGHT <= y || SCREEN_WIDTH <= x)
			{
				dead = 1;
			}
		}
	}

	sf::IntRect get_hitbox() const
	{
		return sf::IntRect(x + 0.375f * BASE_SIZE, y + 0.375f * BASE_SIZE, 0.25f * BASE_SIZE, 0.25f * BASE_SIZE);
	}
};

struct Powerup
{
	bool dead;

	short x;
	short y;

	unsigned char type;

	Powerup(short i_x, short i_y, unsigned char i_type) :
		dead(0),
		x(i_x),
		y(i_y),
		type(i_type)
	{

	}

	sf::IntRect get_hitbox() const
	{
		return sf::IntRect(x + 0.25f * BASE_SIZE, y + 0.25f * BASE_SIZE, 0.5f * BASE_SIZE, 0.5f * BASE_SIZE);
	}
};


