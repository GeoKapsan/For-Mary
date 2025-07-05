#pragma once
#include <sgg/graphics.h>
#include "box.h"
#include "player.h"


/**
* General effect class. Everything in a game that a player can interact with is an effect. Each effect is a derived class
* of this one. Each effect specifies it's influence to the player's state.
*/
class Effect : public Box, public GameObject
{
protected:
	const int m_type; // some effects have more than one type e.g. MarginEffect
public:
	Effect(int type = 0) : m_type(type) {};
	virtual ~Effect();
	void setPos(float pos_x, float pos_y, float width, float height);
	virtual void init(float offset_x, float offset_y) = 0;
	virtual void activate(Player* player) = 0;
	virtual void deactivate(Player* player) = 0;
};