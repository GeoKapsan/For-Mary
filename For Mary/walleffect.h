#pragma once
#include "effect.h"
#include "player.h"

/**
* Class that simulations a wall. Stops the player when activated
*/
class WallEffect : public Effect
{
	WallEffect* m_trap = nullptr;
	float m_offset = 0.0f;
	bool m_activated = false;
	int m_total_traps = 0;
public:
	WallEffect();
	WallEffect(int type) : Effect(type) {};
	~WallEffect();
	bool intersect(Box& other) override;
	float intersectSideways(Box& other);
	void init(float offset_x, float offset_y);
	void activate(Player* player);
	void deactivate(Player* player);
};
