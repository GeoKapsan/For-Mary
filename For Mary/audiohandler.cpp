#include "audiohandler.h"
#include "sgg/graphics.h"
#include "gamestate.h"

#include <iostream>

AudioHandler::AudioHandler()
{
}

/**
* \param mode is the name of the event to play the sound for
* \param sound is the name of the file to save
*/
void AudioHandler::addMode(const std::string& mode, const std::string& sound)
{
	m_sounds[mode] = sound;
}

/**
* \param is the name of the event to play the sound for
* \param vol is the volume
* \param mucic is flag for playing a music or sound as defined by the SGG Library
* \param loop is flag for looping or not
*/
void AudioHandler::sound(const std::string& mode, float vol, bool loop, bool music)
{
	if (music)
	{
		graphics::playMusic(m_state->getFullAssetPath("sounds\\" + m_sounds[mode]), vol, loop, 0.5f);
		return;
	}
	graphics::playSound(m_state->getFullAssetPath("sounds\\" + m_sounds[mode]), vol, loop);
}
