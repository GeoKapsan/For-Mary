#pragma once
#include "gameobject.h"
#include <sgg/graphics.h>
#include <list>
#include "box.h"
#include "effect.h"
#include "audiohandler.h"


/**
* Class that represent the state of the race. All effects, player positions and events are
* supervised in here.
*/
class Level : public GameObject
{
	graphics::Brush m_brush_background[2];

	std::vector<std::string> m_tiles; // Vector that holds the names of the track tiles. Each tile is a png file/
	unsigned int m_current_tile = 0; // The current tile that is being drawn at the moment.
	unsigned int m_current_brush = 0; // The current brush that will draw the next tile.
	unsigned int m_tiles_drawn = 0; // Number of total tiles drawn.
	graphics::Brush m_track_brushes[2]; // Two brushed used to draw at the same time two tiles.

	std::list<Effect*> m_effects; // List of effects. Dynamically updated according to player position.
	std::list<int> m_total_effects_per_tile; // Number of effect loaded for current track tile. Aids to the deletion of the effects of a tile.

	void drawTrack(float offset_x, float offset_y, float width, float height);
	void checkEffects();
	void createTileEffects(float offset_x, float offset_y);
	void deleteTileEffects();

	AudioHandler m_music; // Music manipulation of the track.

	std::function<bool(const Player*, const Player*)> m_comparator = [](const Player* p1, const Player* p2) { return p1->m_pos_x > p2->m_pos_x; }; // comparator for players according to their X position

public:
	void update(float dt) override;
	void init() override;
	virtual void draw() override;

	bool m_end = false; // Flag that is raised when the race ends.

	Level(const std::string& name = "Level 0");
	~Level();

};