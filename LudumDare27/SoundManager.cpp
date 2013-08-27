#include "SoundManager.h"

void SoundManager::play(const std::string& soundname)
{
	sf::Sound *sound = new sf::Sound(mSoundBuffers[soundname]);
	sound->play();
}