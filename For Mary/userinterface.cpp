#include "userinterface.h"
#include "gamestate.h"
#include "util.h"
#include "player.h"
#include "util.h"


/**
* Draws leaderboard for player positions
*/
void UserInterface::drawLeaderboard()
{
	int i = 1;
	for (Player* p : m_state->getPlayers())
	{
		std::string leaderboard_text = "";
		leaderboard_text += std::to_string(i) + ". " + p->m_name;
		graphics::drawText(m_leaderboard_x, m_leaderboard_y + (i-1) * 0.28f, m_leaderboard_size, leaderboard_text, m_brush_leaderboard[i - 1]);
		i++; 
	}
}

UserInterface::UserInterface()
{
}

UserInterface::~UserInterface()
{
}

bool UserInterface::loadGame()
{
	return m_load_game;
}

void UserInterface::draw()
{
	if (m_state->m_countdown)
	{
		graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.3f, 2.0f, 1.0f, m_brush_lights);
		if (!m_starting_timer.isRunning())
			m_starting_timer.start();
		else
			m_brush_lights.texture = m_animations.animate("countdown", m_state->m_light_counter);
	}

	if (!m_load_game)
	{
		graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 5.0f, 5.0f, m_brush_background);
		graphics::drawText(m_state->getCanvasWidth() * 0.325f, m_state->getCanvasHeight() * 0.7, 0.4f, "Press space to start", m_button);
		SETCOLOR(m_brush_instructions.fill_color, 1.0f, 1.0f, 0.3f);
		
		SETCOLOR(m_brush_instructions.fill_color, 0.9f, 0.9f, 0.8f);
		graphics::drawText(m_state->getCanvasWidth() * 0.0f, m_state->getCanvasHeight() * 0.45f, 0.24f, "SPACE: Jump", m_brush_instructions);
		graphics::drawText(m_state->getCanvasWidth() * 0.0f, m_state->getCanvasHeight() * 0.50f, 0.24f, "W:     Up", m_brush_instructions);
		graphics::drawText(m_state->getCanvasWidth() * 0.0f, m_state->getCanvasHeight() * 0.55f, 0.24f, "S:     Down", m_brush_instructions);
		
		m_brush_instructions.outline_opacity = 0.0f;
		SETCOLOR(m_brush_instructions.fill_color, 0.1f, 0.1f, 0.1f);
		graphics::drawText(m_state->getCanvasWidth() * 0.30f, m_state->getCanvasHeight() * 0.78f, 0.3f, "Hit the ", m_brush_instructions);
		SETCOLOR(m_brush_instructions.fill_color, 0.8f, 0.0f, 0.0f);
		graphics::drawText(m_state->getCanvasWidth() * 0.42f, m_state->getCanvasHeight() * 0.78f, 0.3f, "boost", m_brush_instructions);
		SETCOLOR(m_brush_instructions.fill_color, 0.1f, 0.1f, 0.1f);
		graphics::drawText(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.78f, 0.3f, ", avoid ", m_brush_instructions);
		SETCOLOR(m_brush_instructions.fill_color, 0.0f, 0.0f, 0.8f);
		graphics::drawText(m_state->getCanvasWidth() * 0.59f, m_state->getCanvasHeight() * 0.78f, 0.3f, "water", m_brush_instructions);
		SETCOLOR(m_brush_instructions.fill_color, 0.1f, 0.1f, 0.1f);
		graphics::drawText(m_state->getCanvasWidth() * 0.37f, m_state->getCanvasHeight() * 0.84f, 0.3f, "and ", m_brush_instructions);
		SETCOLOR(m_brush_instructions.fill_color, 0.1f, 0.1f, 0.0f);
		graphics::drawText(m_state->getCanvasWidth() * 0.43f, m_state->getCanvasHeight() * 0.84f, 0.3f, "obstacles", m_brush_instructions);
		SETCOLOR(m_brush_instructions.fill_color, 0.1f, 0.1f, 0.1f);
		graphics::drawText(m_state->getCanvasWidth() * 0.3f, m_state->getCanvasHeight() * 0.93f, 0.47f, "Go on, Espresso...", m_brush_instructions);
	}
	else
	{
		graphics::setFont(m_state->getFullAssetPath(m_state->m_font));
		graphics::drawText(m_state->getCanvasWidth() * 0.02f, m_state->getCanvasHeight() * 0.08f, 0.4f, "Round " + std::to_string(std::min(m_state->m_rounds, 3)) + "/ 3", m_brush_rounds);

		drawLeaderboard();
		
		SETCOLOR(m_brush_ending.fill_color, 0.0f, 0.0f, 0.0f);
		graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 5.0f, 5.0f, m_brush_ending);
		SETCOLOR(m_brush_ending.fill_color, 0.6f, 0.0f, 0.0f);
		if (m_state->m_player_win)
			graphics::drawText(m_state->getCanvasWidth() * 0.37f, m_state->getCanvasHeight() * 0.3f, 0.6f, "Victory!", m_brush_ending);
		else
			graphics::drawText(m_state->getCanvasWidth() * 0.37f, m_state->getCanvasHeight() * 0.3f, 0.6f, "Loss...", m_brush_ending);
		SETCOLOR(m_brush_ending.fill_color, 1.0f, 1.0f, 1.0f);
		graphics::drawText(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.1f, 0.4f, "ESC: Exit", m_brush_ending);
	}
}

void UserInterface::update(float dt)
{
	if (!m_load_game)
	{
		if (graphics::getKeyState(graphics::SCANCODE_SPACE))
		{
			m_load_game = true;
			return;
		}
		float p = 0.5f + fabs(cos(graphics::getGlobalTime() / 400.0f));
		SETCOLOR(m_button.fill_color, p, p, p);
	}
	else
	{
		if (m_state->m_countdown)
		{
			if ((float)m_starting_timer < 0.01f)
				m_state->m_light_counter++;
		}

		if (!m_state->m_positioning && !m_state->m_countdown)
		{
			if (m_state->m_destroy_flag)
			{
				m_leaderboard_x = m_state->getCanvasWidth() * 0.35f;
				m_leaderboard_y = m_state->getCanvasHeight() * 0.5f;
				m_leaderboard_size = 0.3f;
				m_brush_ending.fill_opacity = 1.0f;
				float p = 0.5f + fabs(cos(graphics::getGlobalTime() / 200.0f));
				SETCOLOR(m_brush_leaderboard[0].fill_color, p * 1.0f, p * 1.0f, p * 0.0f);
				SETCOLOR(m_brush_leaderboard[1].fill_color, 8.0f, 0.8f, 0.0f);
				SETCOLOR(m_brush_leaderboard[2].fill_color, 8.0f, 0.8f, 0.0f);
				if (!m_music_playing)
				{
					if (m_state->m_player_win)
						m_music.sound("credits_win", 1.0f, true, true);
					else
						m_music.sound("credits_lose", 1.0f, true, true);
					m_music_playing = true;
				}
			}
		}
	}
}

void UserInterface::init()
{
	graphics::preloadBitmaps(m_state->getAssetDir());

	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.fill_opacity = 1.2f;
	m_brush_background.texture = m_state->getFullAssetPath("menu.png");

	graphics::setFont(m_state->getFullAssetPath(m_state->m_font));

	SETCOLOR(m_button.fill_color, 1.0f, 1.0f, 1.0f);
	m_button.fill_opacity = 2.0f;

	m_brush_lights.outline_opacity = 0.0f;
	m_animations.addMode("countdown", { "lights_3.png", "lights_0.png", "lights_1.png", "lights_2.png" });
	m_starting_timer = Timer(1.0f, Timer::TIMER_LOOPING);

	m_brush_rounds.outline_opacity = 0.0f;
	SETCOLOR(m_brush_rounds.fill_color, 1.0f, 1.0f, 1.0f);

	m_leaderboard_x = m_state->getCanvasWidth() * 0.05f;
	m_leaderboard_y = m_state->getCanvasHeight() * 0.2f;

	SETCOLOR(m_brush_leaderboard[0].fill_color, 0.0f, 0.0f, 0.0f);
	SETCOLOR(m_brush_leaderboard[1].fill_color, 0.0f, 0.0f, 0.0f);
	SETCOLOR(m_brush_leaderboard[2].fill_color, 0.0f, 0.0f, 0.0f);

	m_brush_ending.outline_opacity = 0.0f;
	m_brush_ending.fill_opacity = 0.0f;

	m_music.addMode("menu", "jib_jig.mp3");
	m_music.addMode("credits_win", "credits_music.mp3");
	m_music.addMode("credits_lose", "lose_ending.mp3");

	m_music.sound("menu", 1.0f, true, true);
}
