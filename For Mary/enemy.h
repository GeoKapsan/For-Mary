#pragma once
#include "player.h"
#include "timer.h"

/**
* Class that defines the main enemy of the game. It presents an A.I that tries to outrun the player.
* It shares some basic function from the Player class but it's movement is different as it is controlled
* by itself. The ability to win the player is defined by the 'm_competence' field.
*/
class Enemy : public Player
{
	void movePlayer(float dt) override;
	
	int m_competence; // An integer number that defines how good is the enemy i.e. how likely it is to win the player.

public:
	float m_drawPos[2] = { m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->m_global_offset_y};

	Enemy(std::string name, const char* filename, int competence);
	~Enemy();

	void init() override;
	void draw() override;
	void update(float dt) override;
	
};