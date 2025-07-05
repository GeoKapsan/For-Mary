#pragma once
#include <string>
#include "sgg/graphics.h"
#include "animationhandler.h"
#include "timer.h"
#include "userinterface.h"


class GameState
{
private:
	std::string m_asset_path = "assets\\";
	float m_canvas_width = 8.0f;
	float m_canvas_height = 5.0f;

	static GameState* m_unique_instance;

	GameState();

	class Level* m_current_level = 0;
	std::vector<class Player*> m_players; // all enemies and players

	bool m_game_running = false; // if game has started it's main sequence i.e. the race
	class UserInterface* m_interface = 0;


public:
	std::string m_font;

	float m_global_offset_x = 0.0f;
	float m_global_offset_y = 0.0f;
	bool m_debugging = false;

	void init();
	void draw();
	void update(float dt);
	void gameInit();

	static GameState* getInstance();
	~GameState();

	float getCanvasWidth() const { return m_canvas_width; }
	float getCanvasHeight() const { return m_canvas_height; }

	std::string getAssetDir();
	std::string getFullAssetPath(const std::string& asset);

	std::vector<class Player*>& getPlayers() { return m_players; }
	
	int m_light_counter = 0; // the starting lights counter

	bool m_positioning = false; // flag that is raised when the menu is passed, puts the player in the starting position
	bool m_countdown = false; // flag that is raised when the starting lights are on

	int m_rounds = 1; // how many rounds will the players make around the track

	bool m_destroy_flag = false; // flag that is raised when the raced is finished
	bool m_player_win = false; // flag that indicates if the user (player) has won at the race
};