#include "player.h"
#include <sgg/graphics.h>
#include "util.h"
#include <iostream>
#include <sstream>


/**
* Player movement
*/
void Player::movePlayer(float dt)
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
	if (!m_jumped)
		if (m_vy == 0 || graphics::getKeyState(graphics::SCANCODE_W) || graphics::getKeyState(graphics::SCANCODE_S))
			m_land = m_pos_y;
	if (m_land <= m_pos_y) {
		if (!m_falling) {
			m_pos_y = m_land; 
			m_vy = 0;
		}
	}

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

	m_vy += delta_time * m_gravity;

	m_pos_y += delta_time * m_vy;
}



void Player::update(float dt)
{
	movePlayer(dt);

	m_floor.m_pos_y = m_pos_y + 0.28f;

	m_state->m_global_offset_x = m_drawPos[0] - m_pos_x; // at the start the player will be at the cented already (in this program)
	m_state->m_global_offset_y = m_drawPos[1] - m_pos_y;

	GameObject::update(dt);
}

void Player::init()
{
	setParameters(m_state->getFullAssetPath(m_filename).c_str()); // pass file name for loading starting varible values

	m_floor = Box(m_pos_x, m_pos_y + 0.28f, 0.5f, 0.07f);

	m_brush_player.outline_opacity = 0.0f;

	m_brush_player_shadow.outline_opacity = 0.0f;
	m_brush_player_shadow.fill_opacity = 0.5f;
	m_brush_player_shadow.texture = m_state->getFullAssetPath("players\\player_1\\shadow_player.png");

	m_brush_player_debug.fill_opacity = 0.1f;
	SETCOLOR(m_brush_player_debug.fill_color, 1.0f, 0.2f, 0.1f);
	SETCOLOR(m_brush_player_debug.outline_color, 1.0f, 0.3f, 0.2f);

	m_brush_text_debug.fill_opacity = 1.0f;
	SETCOLOR(m_brush_text_debug.fill_color, 1.0f, 0.2f, 0.1f);
	SETCOLOR(m_brush_text_debug.outline_color, 1.0f, 0.3f, 0.2f);

	m_land = m_pos_y;
}

void Player::draw()
{
	m_brush_player.texture = m_animations.animate("run", (int)fmodf(m_pos_x * 5.0f, 10.0f));

	if (m_vx == 0 && m_vy == 0)
		m_brush_player.texture = m_animations.animate("idle", 0);

	graphics::drawRect(m_drawPos[0], m_drawPos[1], 0.65f, 0.65f, m_brush_player);
	if (m_jumped)
	{
		float size = std::min(0.55f, fabsf(0.55f - fabsf(m_pos_y - m_land) * 0.2f));
		if (m_falling) size = 0.0f;
		graphics::drawRect(m_drawPos[0], m_land + m_state->m_global_offset_y + 0.28f, size, size, m_brush_player_shadow);
	}
	else
		graphics::drawRect(m_drawPos[0], m_drawPos[1] + 0.28f, 0.55f, 0.55f, m_brush_player_shadow);

	graphics::resetPose();

	if (m_state->m_debugging) { // debugging
		std::string s = "Pos: (";
		s.append(std::to_string(m_pos_x));
		s.append(", ");
		s.append(std::to_string(m_pos_y));
		s.append(") - Vel: (");
		s.append(std::to_string(m_vx));
		s.append(", ");
		s.append(std::to_string(m_vy));
		s.append(")");
		graphics::drawRect(m_state->getCanvasWidth() * 0.3f, m_state->getCanvasHeight() * 0.7f + 0.28f, m_floor.m_width, m_floor.m_height, m_brush_player_debug);
		graphics::setFont(m_state->getFullAssetPath("debug_font.ttf"));
		graphics::drawText(m_state->getCanvasWidth() * 0.5f - 3.0f, m_state->getCanvasHeight() * 0.5f + 0.5f, 0.2f, s, m_brush_text_debug);
	}
}

/**
* \param filename is the name of the file from which the starting varible values are loaded
*/
void Player::setParameters(const char* fileName)
{
	std::ifstream file(fileName);
	std::string line, param, value;
	if (!file.is_open())
		return;
	while (std::getline(file, line,'\n'))
	{
		std::istringstream stream(line);
		if (std::getline(stream, param, '='))
		{
			stream >> value;
			if (param == "VERTICAL_ACCELERATION")
				m_accel_vertical = std::stof(value);
			else if (param == "HORIZONTAL_ACCELERATION")
				m_accel_horizontal = std::stof(value);
			else if (param == "MAXIMUM_HORIZONTAL_VELOCITY")
				m_maximum_horizontal_velocity = std::stof(value);
			else if (param == "MAXIMUM_VERTICAL_VELOCITY")
				m_maximum_vertical_velocity = std::stof(value);
			else if (param == "VELOCITY_X")
				m_vx = std::stof(value);
			else if (param == "VELOCITY_Y")
				m_vy = std::stof(value);
			else if (param == "POSITION_X")
				m_pos_x = std::stof(value);
			else if (param == "POSITION_Y")
				m_pos_y = std::stof(value);
			else if (param == "ANIMATION_RUN") {
				std::istringstream s(value);
				std::string token;
				std::vector<std::string> sprites;
				while (std::getline(s, token, ',')) {
					sprites.push_back(token);
				}
				m_animations.addMode("run", sprites);
			}
			else if (param == "ANIMATION_IDLE") {
				std::istringstream s(value);
				std::string token;
				std::vector<std::string> sprites;
				while (std::getline(s, token, ',')) {
					sprites.push_back(token);
				}
				m_animations.addMode("idle", sprites);
			}
			else
				return;
		}
	}
	file.close();
}

