#pragma once
#include "effect.h"
#include "player.h"


/**
* Effect that defines the limit of each tile of the track.
*/
class MarginEffect : public Effect
{
	MarginEffect* m_trap = nullptr;
	unsigned int m_total_traps = 0; // Number of 'traps' in specific tile according to 'm_type'
	float m_offset = 0.0f;
public:
	MarginEffect();
	MarginEffect(int type) : Effect(type) {};
	~MarginEffect();
	bool intersect(Box& other) override;
	float intersectDown(Box& other) override;
	void init(float offset_x, float offset_y);
	void activate(Player* player);
	void deactivate(Player* player);
};