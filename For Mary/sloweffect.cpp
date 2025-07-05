#include "sloweffect.h"


void SlowEffect::init(float offset_x, float offset_y)
{
	m_sounds.addMode("activate", "run_water.mp3");
	if (m_type == 0)
	{
		m_trap = new SlowEffect[9];
		m_trap[0].setPos(8.0f + offset_x, 3.8f + offset_y, 1.0f, 1.0f);
		m_trap[1].setPos(9.0f + offset_x, 3.8f + offset_y, 1.0f, 1.3f);
		m_trap[2].setPos(10.0f + offset_x, 3.8f + offset_y, 1.0f, 1.2f);
		m_trap[3].setPos(11.0f + offset_x, 3.7f + offset_y, 1.0f, 1.0f);
		m_trap[4].setPos(12.0f + offset_x, 3.7f + offset_y, 1.0f, 1.0f);
		m_trap[5].setPos(12.0f + offset_x, 3.1f + offset_y, 0.5f, 0.2f);
		m_trap[6].setPos(12.5f + offset_x, 3.1f + offset_y, 0.5f, 0.2f);
		m_trap[7].setPos(12.75f + offset_x, 3.7f + offset_y, 0.5f, 0.6f);
		m_trap[8].setPos(12.7f + offset_x, 3.3f + offset_y, 0.4f, 0.2f);
	}
}

/**
* When activated, player is slowed down
*/
void SlowEffect::activate(Player* player)
{
	player->m_velocity_coef = 0.5f;
	if (player->m_sounded)
		return;
	m_sounds.sound("activate", 0.2f, false, false);
	player->m_sounded = true;
}

void SlowEffect::deactivate(Player* player)
{
		player->m_sounded = false;
		player->m_velocity_coef = 1.0f;
}

bool SlowEffect::intersect(Box &other)
{
	for (int i = 0; i < 9; i++)
	{
		if (other.intersect(m_trap[i]))
			return true;
	}
	return false;
}

SlowEffect::SlowEffect()
{
}

SlowEffect::~SlowEffect()
{
	if (m_trap) delete[] m_trap;
}

