#pragma once
#include "effect.h"
#include "sgg/graphics.h"


/**
* Class that defines a boost effect. It makes the player faster when activated.
*/
class BoostEffect : public Effect
{
	float m_x = 0.0f;
	float m_y = 0.0f;
	
	graphics::Brush m_brush_boost;

	AudioHandler m_sounds;

public:
	BoostEffect();
	BoostEffect(int type, float x, float y) : Effect(type), m_x(x), m_y(y) {};
	~BoostEffect();
	bool intersect(Box& other) override;
	void init(float offset_x, float offset_y);
	void activate(Player* player);
	void deactivate(Player* player);
	void draw() override;
};