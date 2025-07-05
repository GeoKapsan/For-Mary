#include "gamestate.h"
#include <string>
#include "util.h"
#include "sgg/graphics.h"
#include "level.h"
#include "player.h"
#include <thread>
#include <chrono>
#include <iostream>
#include "enemy.h"


GameState::GameState()
{
}

void GameState::init()
{
	m_font = "Crusades.ttf";
	m_interface = new UserInterface();
	m_interface->init();
}

/**
* Main game/race initialization. Afte menu is closed, main game is loaded.
*/
void GameState::gameInit()
{
	m_current_level = new Level();
	m_current_level->init();

	m_players.push_back(new Player("Espresso", "config\\level_1\\player_1_defaults.txt"));
	m_players[0]->init();
	m_global_offset_x = m_players[0]->m_drawPos[0] - m_players[0]->m_pos_x;
	m_global_offset_y = m_players[0]->m_drawPos[1] - m_players[0]->m_pos_y;
	
	m_players.push_back(new Enemy("Moriarti", "config\\level_1\\player_2_defaults.txt", 20));
	m_players[1]->init();

	m_players.push_back(new Enemy("The Spanish Inquisition", "config\\level_1\\player_3_defaults.txt", 40));
	m_players[2]->init();
}

void GameState::draw()
{
	if (!m_interface->loadGame())
	{
		m_interface->draw();
		return;
	}

	if (m_countdown)
	{
		if (m_light_counter == 4) // counter for starting lights
		{
			m_countdown = false;
			m_positioning = false;
		}
	}

	if (!m_current_level)
		return;
	m_current_level->draw();

	m_interface->draw();

}

void GameState::update(float dt)
{
	if (dt > 600.0f) // fragmos poly argwn allagwn
		return;

	float sleep_time = std::max(0.0f, 17.0f - dt);

	std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));

	m_interface->update(dt);

	if (!m_game_running)
	{
		if (m_interface->loadGame()) // if the game/race must be loaded
		{
			m_game_running = true; 
			m_positioning = true;
			gameInit();
			return;
		}
	}
	
	if (!m_current_level)
		return;
	m_current_level->update(dt);

	if (m_current_level->m_end) // when race ends, stop the players
	{
		for (Player* p : m_players)
		{
			p->m_vx = 0;
		}
		m_destroy_flag = true;
		
		if (m_players[0]->m_name == "Espresso") // if the one who one is 'Espresso' then player wins
			m_player_win = true;
	}

	m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
}

GameState* GameState::getInstance()
{
	// for singleton class
	if (m_unique_instance == nullptr)
		m_unique_instance = new GameState();
	return m_unique_instance;
}

GameState::~GameState()
{
	if (m_players.size() > 0) {
		for (auto& p : m_players) {
			delete p;
		}
	}
		
	if (m_current_level)
		delete m_current_level;
}

std::string GameState::getAssetDir()
{
	return m_asset_path;
}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return m_asset_path + asset;
}

GameState* GameState::m_unique_instance = nullptr;