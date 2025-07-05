#pragma once
#include "gameobject.h"
#include <sgg/graphics.h>
#include "audiohandler.h"
#include "animationhandler.h"
#include "timer.h"


/**
* Class for managing the most of the user side elements like starting/ending screens, round counter etc.
*/
class UserInterface : public GameObject
{
	graphics::Brush m_brush_background; // Background brush for menu
	graphics::Brush m_brush_instructions; // Brush for menu prompts
	graphics::Brush m_button; // Brush for 'push to play' button

	AnimationHandler m_animations; // Animation handler for starting lights
	graphics::Brush m_brush_lights; // Brush for starting lights
	Timer m_starting_timer; // Timer for starting lights

	bool m_load_game = false;

	graphics::Brush m_brush_rounds; // Brush for round counter when racing
	graphics::Brush m_brush_leaderboard[3]; // Brush for leaderboard of player position when racing
	float m_leaderboard_x;
	float m_leaderboard_y;
	float m_leaderboard_size = 0.3f;

	graphics::Brush m_brush_ending; // Brush for ending prompt

	void drawLeaderboard();

	AudioHandler m_music;
	bool m_music_playing = false;
	
public:
	UserInterface();
	~UserInterface();

	bool loadGame();

	void init() override;
	void draw() override;
	void update(float dt) override;
};