#pragma once
#include "effect.h"


/**
* Effect that when activated slows the player down.
*/
class SlowEffect : public Effect
{
	SlowEffect* m_trap = nullptr;
	
	AudioHandler m_sounds;

public:
	SlowEffect();
	SlowEffect(int type) : Effect(type) {};
	~SlowEffect();
	bool intersect(Box &other) override;
	void init(float offset_x, float offset_y);
	void activate(Player* player);
	void deactivate(Player* player);
};