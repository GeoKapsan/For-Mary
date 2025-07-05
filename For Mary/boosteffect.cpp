#include "boosteffect.h"

BoostEffect::BoostEffect()
{
}

BoostEffect::~BoostEffect()
{
}

bool BoostEffect::intersect(Box& other)
{
    return other.intersect(*this);
}

void BoostEffect::init(float offset_x, float offset_y)
{
    m_sounds.addMode("activated", "boost.mp3");
    this->setPos(m_x + offset_x, m_y + offset_y, 0.7f, 0.75f);

    m_brush_boost.outline_opacity = 0.0f;
    m_brush_boost.texture = m_state->getFullAssetPath("track\\boost_pad.png");
}

/**
* \param player is the player for whom the effect is activated
* When activated player velovity is doubled
*/
void BoostEffect::activate(Player* player)
{
    player->m_boost = 2.0f;
    if (player->m_sounded)
        return;
    m_sounds.sound("activated", 0.2f, false, false);
    player->m_sounded = true;
}

/**
* \param player is the player for whom the effect is deactivated
* If the effect has been activated, then disable it after some metres.
*/
void BoostEffect::deactivate(Player* player)
{
    player->m_sounded = false;
    if ((player->m_pos_x - m_pos_x) > 6.0f)
    {
        player->m_boost = 1.0f;
    }
}

void BoostEffect::draw()
{
    graphics::drawRect(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->m_global_offset_y, m_width + 0.3f, m_height, m_brush_boost);
}
