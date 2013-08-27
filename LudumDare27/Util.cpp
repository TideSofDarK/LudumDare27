#include "Util.h"
#include "SoundManager.h"

float interpolateLinear(const float variableA, const float variableB, float factor) 
{
	if(factor > 1.f) factor = 1.f;
	else if(factor < 0.f) factor = 0.f;
	return variableA + (variableB - variableA) * factor;
}

sf::Vector2f interpolateVector(const sf::Vector2f& pointA, const sf::Vector2f& pointB, float factor) 
{
	if(factor > 1.f) factor = 1.f;
	else if(factor < 0.f) factor = 0.f;
	return pointA + (pointB - pointA) * factor;
}

void Rhythm::start(float newBpm)
{
	mBpm = newBpm;
	mClock.restart();
	SoundManager::get().play(METRONOME_SOUND);
}

bool Rhythm::onBeat(bool restart)
{
	if (mClock.getElapsedTime().asSeconds() >= mBpm/60.f/4.f)
	{
		if(restart) 
		{
			SoundManager::get().play(METRONOME_SOUND);
			mClock.restart();
		}
		return true;
	}
	else
	{
		return false;
	}
}