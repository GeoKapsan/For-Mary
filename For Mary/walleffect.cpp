#include "walleffect.h"

WallEffect::WallEffect()
{
}

WallEffect::~WallEffect()
{
    if (m_trap) delete[] m_trap;
}

bool WallEffect::intersect(Box& other)
{
    return WallEffect::intersectSideways(other);
}

/**
* Stop player when they hit wall.
*/
float WallEffect::intersectSideways(Box& other)
{

    if (m_trap)
		for (int i = 0; i < m_total_traps; i++)
		{
			if (m_offset = other.intersectSideways(m_trap[i]))
			{
				return m_offset;
			}
		}
    return 0.0f;
}

void WallEffect::init(float offset_x, float offset_y)
{
    if (m_type == 0)
    {
        m_trap = new WallEffect[3];
        m_total_traps = 3;
        m_trap[0].setPos(7.3f + offset_x, 3.0f + offset_y, 0.3f, 1.0f);
        m_trap[1].setPos(7.3f + offset_x, 4.0f + offset_y, 0.3f, 1.0f);
        m_trap[2].setPos(7.3f + offset_x, 5.0f + offset_y, 0.3f, 1.0f);
    }
}

void WallEffect::activate(Player* player)
{
    player->m_pos_x += m_offset * 1.5f;
    player->m_vx = 0.0f;
}

void WallEffect::deactivate(Player* player)
{
}
