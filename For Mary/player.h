#pragma once
#include "gameobject.h"
#include "gamestate.h"
#include <sgg/graphics.h>
#include "box.h"
#include "animationhandler.h"
#include "audiohandler.h"
#include <fstream>

/**
* Player class. Represents all movement and appereance for the player. 
*/
class Player : public GameObject
{
protected:
	graphics::Brush m_brush_player; // Main brush for player and their animations.
	graphics::Brush m_brush_player_shadow; // For player shadow
	
	graphics::Brush m_brush_player_debug; // Debug use
	graphics::Brush m_brush_text_debug; // Debug use

	AnimationHandler m_animations; // Animation manipulation for player.

	float m_gravity = 10.0f; // Gravity for player.
	float m_accel_vertical = 0.0f; // Vertical acceleration 
	float m_accel_horizontal = 0.0f; // Horizontal acceleration
	float m_maximum_horizontal_velocity = 0.0f; // Maximum horizontal velocity
	float m_maximum_vertical_velocity = 0.0f; // Macimum vertical velocity

	const char* m_filename; // File name for player configuration that contains variable values.

	virtual void movePlayer(float dt);
	void setParameters(const char* fileName);
public:
	float m_vx = 0.0f;
	float m_vy = 0.0f;

	float m_pos_x = 0.0f;
	float m_pos_y = 0.0f;

	float m_land = 0.0f; // Y coordinate that keeps the player on track.

	float m_drawPos[2] = {m_state->getCanvasWidth() * 0.3f, m_state->getCanvasHeight() * 0.7f}; // X and Y coordinate to where to draw the player.

	Box m_floor; // Box class element for player collision. The player 'collision radius' is their feet.

	Player(std::string name, const char* filename) : GameObject(name), m_filename(filename){};
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;

	int m_position = 0;

	bool m_jumped = false;
	bool m_canCollide = true;
	float m_velocity_coef = 1.0f;
	float m_boost = 1.0f;
	bool m_falling = false;
	bool m_sounded = false;
};