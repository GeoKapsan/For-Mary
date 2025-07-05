#include "margineffect.h"


MarginEffect::MarginEffect()
{
}

MarginEffect::~MarginEffect()
{
	if (m_trap) delete[] m_trap;
}

bool MarginEffect::intersect(Box& other)
{
	return MarginEffect::intersectDown(other);
}

float MarginEffect::intersectDown(Box& other)
{
	if (m_trap)
		for (int i = 0; i < m_total_traps; i++)
		{
			if (m_trap[i].m_pos_y < other.m_pos_y && other.Box::intersect(m_trap[i])) // collision check for upper bound track
			{
				return m_offset = 0.05f;
			}
			if (m_offset = other.intersectDown(m_trap[i])) // collision check for lower bound track
			{
				return m_offset;
			}
		}
	return 0.0f;
}

void MarginEffect::init(float offset_x, float offset_y)
{
	if (m_type == 0)
	{
		m_trap = new MarginEffect[30];
		m_total_traps = 30;
		m_trap[0].setPos(3.0f + offset_x, 5.25f + offset_y, 0.5f, 0.5f);
		m_trap[1].setPos(3.5f + offset_x, 5.5f + offset_y, 0.5f, 0.5f);
		m_trap[2].setPos(4.0f + offset_x, 5.625f + offset_y, 0.5f, 0.5f);
		m_trap[3].setPos(4.5f + offset_x, 5.65f + offset_y, 0.5f, 0.5f);
		m_trap[4].setPos(5.0f + offset_x, 5.75f + offset_y, 0.5f, 0.5f);
		m_trap[5].setPos(5.5f + offset_x, 5.8f + offset_y, 0.5f, 0.5f);
		m_trap[6].setPos(6.0f + offset_x, 5.8f + offset_y, 0.5f, 0.5f);
		m_trap[7].setPos(6.5f + offset_x, 5.8f + offset_y, 0.5f, 0.5f);
		m_trap[8].setPos(7.0f + offset_x, 5.75f + offset_y, 0.5f, 0.5f);
		m_trap[9].setPos(7.5f + offset_x, 5.7f + offset_y, 0.5f, 0.5f);
		m_trap[10].setPos(8.0f + offset_x, 5.65f + offset_y, 0.5f, 0.5f);
		m_trap[11].setPos(11.0f + offset_x, 5.5f + offset_y, 5.5f, 0.5f);
		m_trap[12].setPos(14.0f + offset_x, 5.4f + offset_y, 0.5f, 0.5f);
		m_trap[13].setPos(14.5f + offset_x, 5.35f + offset_y, 0.5f, 0.5f);
		m_trap[14].setPos(15.0f + offset_x, 5.3f + offset_y, 0.5f, 0.5f);
		m_trap[15].setPos(3.0f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[16].setPos(3.5f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[17].setPos(4.0f + offset_x, 2.7f + offset_y, 0.5f, 0.5f);
		m_trap[18].setPos(4.5f + offset_x, 2.7f + offset_y, 0.5f, 0.5f);
		m_trap[19].setPos(5.0f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[20].setPos(5.5f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[21].setPos(6.0f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[22].setPos(6.5f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[23].setPos(7.0f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[24].setPos(7.5f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[25].setPos(8.0f + offset_x, 2.65f + offset_y, 0.5f, 0.5f);
		m_trap[26].setPos(11.0f + offset_x, 2.7f + offset_y, 5.5f, 0.5f);
		m_trap[27].setPos(14.0f + offset_x, 2.75f + offset_y, 0.5f, 0.5f);
		m_trap[28].setPos(14.5f + offset_x, 2.85f + offset_y, 0.5f, 0.5f);
		m_trap[29].setPos(15.0f + offset_x, 2.9f + offset_y, 0.5f, 0.5f);
	}
	else if (m_type == 1)
	{
		m_trap = new MarginEffect[30];
		m_total_traps = 30;
		m_trap[0].setPos(3.5f + offset_x, 5.25f + offset_y, 0.5f, 0.5f);
		m_trap[1].setPos(4.0f + offset_x, 5.25f + offset_y, 0.5f, 0.5f);
		m_trap[2].setPos(4.5f + offset_x, 5.2f + offset_y, 0.5f, 0.5f);
		m_trap[3].setPos(5.0f + offset_x, 5.15f + offset_y, 0.5f, 0.5f);
		m_trap[4].setPos(5.5f + offset_x, 5.0f + offset_y, 0.5f, 0.5f);
		m_trap[5].setPos(6.0f + offset_x, 4.8f + offset_y, 0.5f, 0.5f);
		m_trap[6].setPos(6.5f + offset_x, 4.75f + offset_y, 0.5f, 0.5f);
		m_trap[7].setPos(7.0f + offset_x, 4.75f + offset_y, 0.5f, 0.5f);
		m_trap[8].setPos(7.5f + offset_x, 4.6f + offset_y, 0.5f, 0.5f);
		m_trap[9].setPos(8.0f + offset_x, 4.55f + offset_y, 0.5f, 0.5f);
		m_trap[10].setPos(8.5f + offset_x, 4.5f + offset_y, 0.5f, 0.5f);
		m_trap[11].setPos(9.0f + offset_x, 4.55f + offset_y, 0.5f, 0.5f);
		m_trap[12].setPos(9.5f + offset_x, 4.5f + offset_y, 0.5f, 0.5f);
		m_trap[13].setPos(10.0f + offset_x, 4.5f + offset_y, 0.5f, 0.5f);
		m_trap[14].setPos(10.5f + offset_x, 4.5f + offset_y, 0.5f, 0.5f);
		m_trap[15].setPos(3.0f + offset_x, 2.75f + offset_y, 0.5f, 0.5f);
		m_trap[16].setPos(3.5f + offset_x, 2.75f + offset_y, 0.5f, 0.5f);
		m_trap[17].setPos(4.0f + offset_x, 2.75f + offset_y, 0.5f, 0.5f);
		m_trap[18].setPos(4.5f + offset_x, 2.75f + offset_y, 0.5f, 0.5f);
		m_trap[19].setPos(5.0f + offset_x, 2.75f + offset_y, 0.5f, 0.5f);
		m_trap[20].setPos(5.5f + offset_x, 2.75f + offset_y, 0.5f, 0.5f);
		m_trap[21].setPos(6.0f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[22].setPos(6.5f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[23].setPos(7.0f + offset_x, 2.9f + offset_y, 0.5f, 0.5f);
		m_trap[24].setPos(7.5f + offset_x, 3.0f + offset_y, 0.5f, 0.5f);
		m_trap[25].setPos(8.0f + offset_x, 3.2f + offset_y, 0.5f, 0.5f);
		m_trap[26].setPos(8.5f + offset_x, 3.2f + offset_y, 0.5f, 0.5f);
		m_trap[27].setPos(9.0f + offset_x, 3.3f + offset_y, 0.5f, 0.5f);
		m_trap[28].setPos(9.5f + offset_x, 3.3f + offset_y, 0.5f, 0.5f);
		m_trap[29].setPos(10.0f + offset_x, 3.0f + offset_y, 0.5f, 0.5f);
	}
	else if (m_type == 2)
	{
		m_trap = new MarginEffect[19];
		m_total_traps = 19;
		m_trap[0].setPos(10.5f + offset_x, 5.55f + offset_y, 10.5f, 0.5f);
		m_trap[1].setPos(6.0f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[2].setPos(6.5f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[3].setPos(7.0f + offset_x, 2.9f + offset_y, 0.5f, 0.5f);
		m_trap[4].setPos(7.5f + offset_x, 3.0f + offset_y, 0.5f, 0.5f);
		m_trap[5].setPos(8.0f + offset_x, 3.2f + offset_y, 0.5f, 0.5f);
		m_trap[6].setPos(8.5f + offset_x, 3.2f + offset_y, 0.5f, 0.5f);
		m_trap[7].setPos(9.0f + offset_x, 3.3f + offset_y, 0.5f, 0.5f);
		m_trap[8].setPos(9.5f + offset_x, 3.3f + offset_y, 0.5f, 0.5f);
		m_trap[9].setPos(10.0f + offset_x, 3.0f + offset_y, 0.5f, 0.5f);
		m_trap[10].setPos(10.5f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[11].setPos(11.0f + offset_x, 2.9f + offset_y, 0.5f, 0.5f);
		m_trap[12].setPos(11.5f + offset_x, 3.0f + offset_y, 0.5f, 0.5f);
		m_trap[13].setPos(12.0f + offset_x, 3.2f + offset_y, 0.5f, 0.5f);
		m_trap[14].setPos(12.5f + offset_x, 3.2f + offset_y, 0.5f, 0.5f);
		m_trap[15].setPos(13.0f + offset_x, 3.3f + offset_y, 0.5f, 0.5f);
		m_trap[16].setPos(13.5f + offset_x, 3.3f + offset_y, 0.5f, 0.5f);
		m_trap[17].setPos(14.0f + offset_x, 3.0f + offset_y, 0.5f, 0.5f);
		m_trap[18].setPos(14.5f + offset_x, 3.0f + offset_y, 0.5f, 0.5f);
	}
	else if (m_type == 3)
	{
		m_trap = new MarginEffect[31];
		m_total_traps = 31;
		m_trap[0].setPos(3.0f + offset_x, 5.25f + offset_y, 0.5f, 0.5f);
		m_trap[1].setPos(3.5f + offset_x, 5.5f + offset_y, 0.5f, 0.5f);
		m_trap[2].setPos(4.0f + offset_x, 5.625f + offset_y, 0.5f, 0.5f);
		m_trap[3].setPos(4.5f + offset_x, 5.65f + offset_y, 0.5f, 0.5f);
		m_trap[4].setPos(5.0f + offset_x, 5.75f + offset_y, 0.5f, 0.5f);
		m_trap[5].setPos(5.5f + offset_x, 5.8f + offset_y, 0.5f, 0.5f);
		m_trap[6].setPos(6.0f + offset_x, 5.8f + offset_y, 0.5f, 0.5f);
		m_trap[7].setPos(6.5f + offset_x, 5.8f + offset_y, 0.5f, 0.5f);
		m_trap[8].setPos(7.0f + offset_x, 5.75f + offset_y, 0.5f, 0.5f);
		m_trap[9].setPos(7.5f + offset_x, 5.7f + offset_y, 0.5f, 0.5f);
		m_trap[10].setPos(8.0f + offset_x, 5.65f + offset_y, 0.5f, 0.5f);
		m_trap[11].setPos(11.0f + offset_x, 5.5f + offset_y, 5.5f, 0.5f);
		m_trap[12].setPos(14.0f + offset_x, 5.4f + offset_y, 0.5f, 0.5f);
		m_trap[13].setPos(14.5f + offset_x, 5.35f + offset_y, 0.5f, 0.5f);
		m_trap[14].setPos(15.0f + offset_x, 5.3f + offset_y, 0.5f, 0.5f);
		m_trap[15].setPos(3.0f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[16].setPos(3.5f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[17].setPos(4.0f + offset_x, 2.7f + offset_y, 0.5f, 0.5f);
		m_trap[18].setPos(4.5f + offset_x, 2.7f + offset_y, 0.5f, 0.5f);
		m_trap[19].setPos(5.0f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[20].setPos(5.5f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[21].setPos(6.0f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[22].setPos(6.5f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[23].setPos(7.0f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[24].setPos(7.5f + offset_x, 2.8f + offset_y, 0.5f, 0.5f);
		m_trap[25].setPos(8.0f + offset_x, 2.65f + offset_y, 0.5f, 0.5f);
		m_trap[26].setPos(11.0f + offset_x, 2.7f + offset_y, 5.5f, 0.5f);
		m_trap[27].setPos(14.0f + offset_x, 2.75f + offset_y, 0.5f, 0.5f);
		m_trap[28].setPos(14.5f + offset_x, 2.85f + offset_y, 0.5f, 0.5f);
		m_trap[29].setPos(15.0f + offset_x, 2.9f + offset_y, 0.5f, 0.5f);
		m_trap[30].setPos(10.0f + offset_x, 5.0f + offset_y, 3.5f, 0.5f);
	}
}

void MarginEffect::activate(Player* player)
{
	player->m_pos_y += m_offset;
	player->m_vy = 0.0f;
}

void MarginEffect::deactivate(Player* player)
{
}
