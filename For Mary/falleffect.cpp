#include "falleffect.h"
#include <iostream>


FallEffect::FallEffect()
{
}

FallEffect::~FallEffect()
{
    if (m_trap) delete[] m_trap;
}

bool FallEffect::intersect(Box& other)
{
	for (int i = 0; i < 2; i++)
	{
		if (other.intersect(m_trap[i]))
			return true;
	}
	return false;
}

void FallEffect::init(float offset_x, float offset_y)
{
	if (m_type == 0)
	{
		m_trap = new FallEffect[2];
		m_trap[0].setPos(13.2f + offset_x, 4.3f + offset_y, 3.7f, 0.5f);
		m_trap[1].setPos(13.2f + offset_x, 3.0f + offset_y, 3.7f, 0.5f);
	}
	else if (m_type == 1)
	{
		m_trap = new FallEffect[2];
		m_trap[0].setPos(4.0f + offset_x, 4.25f + offset_y, 2.2f, 0.5f);
		m_trap[1].setPos(4.0f + offset_x, 3.0f + offset_y, 2.2f, 0.5f);
	}
}

/**
* If activated, drops the player of the track
*/
void FallEffect::activate(Player* player)
{
	player->m_falling = true;
	player->m_vx = 0.0f;
	player->m_jumped = true;
}

/**
* When deactivated after dropping the player, if the player drops more than some constant
* then teleport him back to the track
*/
void FallEffect::deactivate(Player* player)
{	
	if (player->m_pos_y > 11.0f)
	{
		player->m_land = 3.45f;
		player->m_pos_x -= 1.0f;

		player->m_falling = false;
		player->m_jumped = false;
	}
}
