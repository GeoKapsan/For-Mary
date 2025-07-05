#include "enemy.h"
#include "gamestate.h"
#include "util.h"


Enemy::Enemy(std::string name, const char* filename, int competence = 25) : Player(name, filename), m_competence(competence) {}

Enemy::~Enemy()
{

}

/**
* Moves like the normal player (tries to mimic him) but acts as him if only the random number generator return a number less than the
* competence of the enemy. Higher competence the more likely is the enemy to follow the player movements.
*/
void Enemy::movePlayer(float dt)
{
	float delta_time = dt / 1000.0f;

	// X
	m_vx = std::min(m_vx + delta_time * m_accel_horizontal, m_maximum_horizontal_velocity);
	m_vx = std::max(m_vx, -m_maximum_horizontal_velocity);
	if (fabs(m_vx) < 0.01f)
		m_vx = 0.0f;

	m_pos_x += delta_time * m_vx * m_velocity_coef * m_boost;
	m_floor.m_pos_x = m_pos_x;

	if (m_state->m_positioning)
	{
		if (m_pos_x >= 11.0f)
		{
			m_pos_x -= delta_time * m_vx;
			m_vx = 0;
			m_state->m_countdown = true;
		}
		return;
	}


	// Y
	int chance = rand() % 501; // random number [0, 500]

	if (!m_jumped)
		if (m_vy == 0 || graphics::getKeyState(graphics::SCANCODE_W) || graphics::getKeyState(graphics::SCANCODE_S))
			m_land = m_pos_y;
	if (m_land <= m_pos_y) {
		if (!m_falling) {
			m_pos_y = m_land;
			m_vy = 0;
		}
	}

	if (chance < m_competence)
	{
		if (m_vy == 0)
		{
			m_jumped = false;
			m_vy -= graphics::getKeyState(graphics::SCANCODE_SPACE) ? m_accel_vertical : 0.0f;
			if (graphics::getKeyState(graphics::SCANCODE_SPACE))
				m_jumped = true;
			m_canCollide = !m_jumped;

		}

		float move = 0.0f;
		if (!m_jumped)
		{
			if (graphics::getKeyState(graphics::SCANCODE_W))
				move = -1.0f;
			else if (graphics::getKeyState(graphics::SCANCODE_S))
				move = 1.0f;
		}

		m_vy = std::min(m_vy + delta_time * move * 100.0f, m_maximum_vertical_velocity);
		m_vy = std::max(m_vy, -m_maximum_vertical_velocity);
	}

	m_vy += delta_time * m_gravity;

	m_pos_y += delta_time * m_vy;
}

void Enemy::update(float dt)
{
	m_floor.m_pos_y = m_pos_y + 0.28f; // Box -feet- collision box is drawn a little bit lower

	m_drawPos[0] = m_pos_x + m_state->m_global_offset_x;
	m_drawPos[1] = m_pos_y + m_state->m_global_offset_y;
	Enemy::movePlayer(dt);
}

void Enemy::init()
{
	Player::init();
}

void Enemy::draw()
{
	m_brush_player.texture = m_animations.animate("run", (int)fmodf(m_pos_x * 5.0f, 10.0f));

	if (m_jumped)
	{
		float size = std::min(0.55f, fabsf(0.55f - fabsf(m_pos_y - m_land) * 0.2f));
		graphics::drawRect(m_drawPos[0], m_land + m_state->m_global_offset_y + 0.28f, size, size, m_brush_player_shadow);
	}
	else
		graphics::drawRect(m_drawPos[0], m_drawPos[1] + 0.28f, 0.55f, 0.55f, m_brush_player_shadow);

	if (m_vx == 0 && m_vy == 0)
		m_brush_player.texture = m_animations.animate("idle", 0);

	graphics::drawRect(m_drawPos[0], m_drawPos[1], 0.65f, 0.65f, m_brush_player);
}
