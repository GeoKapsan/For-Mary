#include "effect.h"

Effect::~Effect()
{
}

/**
* Where and how big should the area of the effect should be
*/
void Effect::setPos(float pos_x, float pos_y, float width, float height)
{
	m_pos_x = pos_x;
	m_pos_y = pos_y;
	m_width = width;
	m_height = height;
}
