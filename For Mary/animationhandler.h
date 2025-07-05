#pragma once
#include <string>
#include "gameobject.h"
#include <vector>
#include <map>


/**
* Class that handles the animations of a drawable object.
*/
class AnimationHandler : public GameObject
{
	/**
	* Map with key the name of the animation sequence and value a vector with sprites to animate.
	*/
	std::map<std::string, std::vector<std::string>> m_sprites;

public:

	AnimationHandler();
	void addMode(const std::string& mode, const std::vector<std::string>& sprites);
	std::string animate(const std::string& mode, int index);
};