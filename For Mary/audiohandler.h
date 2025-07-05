#pragma once
#include <string>
#include "gameobject.h"
#include <vector>
#include <map>


/**
* Class that handles audio files. 
*/
class AudioHandler : public GameObject
{
	/**
	* Map with key the name of the event for the value (audio file) to play
	*/
	std::map<std::string, std::string> m_sounds;

public:
	AudioHandler();
	void addMode(const std::string& mode, const std::string& sound);
	void sound(const std::string& mode, float vol, bool loop, bool music);
};