#include "animationhandler.h"
#include "gamestate.h"
#include <iostream>


AnimationHandler::AnimationHandler()
{
}

/**
* \param mode is the name of the sequence
* \param sprites is the vector of sprites to be saved and later loaded
*/
void AnimationHandler::addMode(const std::string& mode, const std::vector<std::string>& sprites)
{
    m_sprites[mode] = sprites;
}

/**
* \param mode is the name of the sequence to initiate
* \param index is the index for the specific sprite to load, something non constant surely
*/
std::string AnimationHandler::animate(const std::string& mode, int index)
{
    return m_state->getFullAssetPath(m_sprites[mode][index % m_sprites[mode].size()]);
}
