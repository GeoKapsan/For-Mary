#include "level.h"
#include "util.h"
#include "gamestate.h"
#include "player.h"
#include "sloweffect.h"
#include <iostream>
#include <sstream>
#include "margineffect.h"
#include "falleffect.h"
#include "boosteffect.h"
#include "walleffect.h"


/**
* \param offset_x is the X coordinate of the center of the left tile currently being drawn
* \param offset_y is the Y coordinate of the center of the left tile currently being drawn
*/
void Level::drawTrack(float offset_x, float offset_y, float w, float h)
{
	float w_coef = 1.5f;
	float h_coef = 1.5f;

	// firstly the background is being drawn
	graphics::drawRect(offset_x, offset_y, w * w_coef, h * h_coef, m_brush_background[0]);
	graphics::drawRect(offset_x + w * w_coef, offset_y, w * w_coef, h * h_coef, m_brush_background[1]);

	// then the track tiles
	graphics::drawRect(offset_x, offset_y, w * w_coef, h * h_coef, m_track_brushes[m_current_brush]);
	m_current_brush = (m_current_brush + 1) % 2;
	graphics::drawRect(offset_x + w * w_coef, offset_y, w * w_coef, h * h_coef, m_track_brushes[m_current_brush]);
	m_current_brush = (m_current_brush + 1) % 2;
	
	// if left most track come of frame then delete it and append a new one to the right of the previously most right
	if (offset_x + w * w_coef / 2.0f < 0) {
		m_track_brushes[m_current_brush].texture = m_tiles[m_current_tile];
		graphics::drawRect(offset_x + 2.0f * w * w_coef, offset_y, w * w_coef, h * h_coef, m_track_brushes[m_current_brush]);
		m_current_brush = (m_current_brush + 1) % 2;
		createTileEffects((m_tiles_drawn + 2) * w * 1.5f, 0.0f);
		m_tiles_drawn++;
		m_current_tile = (m_current_tile + 1) % m_tiles.size();
		deleteTileEffects();

		if (m_current_tile - 2 == 0) // for round checking
		{
			m_state->m_rounds++;
		}
	}
}

/**
* Checks for collisions of players with effects
*/
void Level::checkEffects()
{
	for (auto& player : m_state->getPlayers())
	{
		for (auto& effect : m_effects)
		{
			if (effect->isActive())
			{
				if (player->m_canCollide)
				{
					if (effect->intersect(player->m_floor))
					{
						effect->activate(player);
						break;
					}
				}
				effect->deactivate(player);
			}
		}
	}
}

/**
* \param offset_x X coordinate of the center of the track tile for which the effects are initialized for
* \param offset_y Y coordinate of the center of the track tile for which the effects are initialized for
* This method initializes dynamically new effects to each specific track tile according to each sprite name.
*/
void Level::createTileEffects(float offset_x, float offset_y)
{
	if (m_tiles[m_current_tile] == m_state->getFullAssetPath("track/starting_finish.png"))
	{
		m_effects.push_back(new MarginEffect(0));
		m_effects.back()->init(offset_x, offset_y);

		m_total_effects_per_tile.push_back(1);
	}
	else if (m_tiles[m_current_tile] == m_state->getFullAssetPath("track/plain_0.png"))
	{
		m_effects.push_back(new MarginEffect(0));
		m_effects.back()->init(offset_x, offset_y);

		m_effects.push_back(new BoostEffect(0, 5.5f, 4.7f));
		m_effects.back()->init(offset_x, offset_y);

		m_total_effects_per_tile.push_back(2);
	}
	else if (m_tiles[m_current_tile] == m_state->getFullAssetPath("track/water_0.png")) {
		m_effects.push_back(new SlowEffect(0));
		m_effects.back()->init(offset_x, offset_y);
		
		m_effects.push_back(new BoostEffect(0, 5.5f, 4.0f));
		m_effects.back()->init(offset_x, offset_y);

		m_effects.push_back(new MarginEffect(0));
		m_effects.back()->init(offset_x, offset_y);
		
		m_total_effects_per_tile.push_back(3);
	}
	else if (m_tiles[m_current_tile] == m_state->getFullAssetPath("track/void_0.png")) {
		m_effects.push_back(new FallEffect(0));
		m_effects.back()->init(offset_x, offset_y);
		
		m_effects.push_back(new MarginEffect(1));
		m_effects.back()->init(offset_x, offset_y);
		
		m_total_effects_per_tile.push_back(2);
	}
	else if (m_tiles[m_current_tile] == m_state->getFullAssetPath("track/void_1.png")) {
		m_effects.push_back(new FallEffect(1));
		m_effects.back()->init(offset_x, offset_y);
		
		m_effects.push_back(new MarginEffect(2));
		m_effects.back()->init(offset_x, offset_y);
		
		m_total_effects_per_tile.push_back(2);
	}
	else if (m_tiles[m_current_tile] == m_state->getFullAssetPath("track/platform.png"))
	{
		m_effects.push_back(new WallEffect(0));
		m_effects.back()->init(offset_x, offset_y);

		m_effects.push_back(new MarginEffect(3));
		m_effects.back()->init(offset_x, offset_y);
		
		m_total_effects_per_tile.push_back(2);
	}
}

/**
* Deletes effects for track tiles thrown off frame
*/
void Level::deleteTileEffects()
{
	if (m_effects.size() > 1) {
		for (int i = 0; i < m_total_effects_per_tile.front(); i++)
		{
			delete m_effects.front();
			m_effects.pop_front();
		}
		m_total_effects_per_tile.pop_front();
	}
}

void Level::update(float dt)
{
	for (auto& p : m_state->getPlayers())
	{
		p->update(dt);
		std::sort(m_state->getPlayers().begin(), m_state->getPlayers().end(), m_comparator);
	}

	checkEffects();

	if (m_state->m_rounds == 4) // ending sequence for crossing finish line
	{
		for (Player* p : m_state->getPlayers())
		{
			if (p->m_pos_x > 11.5f + m_state->getCanvasWidth() * 1.5f * m_tiles_drawn)
			{
				m_end = true;
			}
		}
	}

	GameObject::update(dt);
}

void Level::init()
{
	m_brush_background[0].outline_opacity = 0.0f;
	m_brush_background[0].texture = m_state->getFullAssetPath("background_1.png");
	m_brush_background[1].outline_opacity = 0.0f;
	m_brush_background[1].texture = m_state->getFullAssetPath("background_1.png");

	// track drawing
	m_tiles.push_back(m_state->getFullAssetPath("track/starting_finish.png"));
	m_tiles.push_back(m_state->getFullAssetPath("track/plain_0.png"));
	m_tiles.push_back(m_state->getFullAssetPath("track/water_0.png"));
	m_tiles.push_back(m_state->getFullAssetPath("track/void_0.png"));
	m_tiles.push_back(m_state->getFullAssetPath("track/void_1.png"));
	m_tiles.push_back(m_state->getFullAssetPath("track/platform.png"));
	m_track_brushes[0].outline_opacity = 0.0f;
	m_track_brushes[1].outline_opacity = 0.0f;
	m_track_brushes[0].texture = m_tiles[0];
	m_track_brushes[1].texture = m_tiles[1];

	createTileEffects(0.0f, 0.0f);
	m_current_tile = (m_current_tile + 1) % m_tiles.size();
	createTileEffects(m_state->getCanvasWidth() * 1.5f, 0.0f);
	m_current_tile = (m_current_tile + 1) % m_tiles.size();


	m_music.addMode("music", "welcome_to_the_crocodile_island.mp3");
	m_music.sound("music", 1.0f, true, true);
}

void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	float offset_x = m_state->m_global_offset_x + w / 2.0f + 5.0f;
	float offset_y = m_state->m_global_offset_y + h / 2.0f;

	// draw track
	drawTrack(offset_x + w * 1.5f * m_tiles_drawn, offset_y, w, h);

	for (auto& p : m_state->getPlayers())
	{
		p->draw();
	}

	for (Effect* effect : m_effects)
	{
		if (Effect* e = dynamic_cast<Effect*>(effect))
			e->draw();
	}
}

Level::Level(const std::string& name)
{
}

Level::~Level()
{
}