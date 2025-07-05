#pragma once
#include "effect.h"
#include "player.h"

/**
* Effect that makes a player fall when activated.
*/
class FallEffect : public Effect
{
	FallEffect* m_trap = nullptr;
	float m_offset = 0.0f;
public:
	FallEffect();
	FallEffect(int type) : Effect(type) {};
	~FallEffect();
	bool intersect(Box& other) override;
	void init(float offset_x, float offset_y);
	void activate(Player* player);
	void deactivate(Player* player);
};
