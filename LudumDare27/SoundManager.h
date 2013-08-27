#pragma once

#include <map>

#include <SFML/Audio.hpp>

#define HIT_SUCCESS_SOUND	"hit_success"
#define FAILURE_SOUND		"failure"
#define METRONOME_SOUND		"metronome"
#define START_SOUND			"start"
#define FAIL_SOUND			"fail"

class SoundManager
{
private:
	SoundManager() 
	{
		mSoundBuffers[HIT_SUCCESS_SOUND].loadFromFile("assets/sfx/hit_success.wav");
		mSoundBuffers[FAILURE_SOUND].loadFromFile("assets/sfx/failure.wav");
		mSoundBuffers[METRONOME_SOUND].loadFromFile("assets/sfx/metronome.wav");
		mSoundBuffers[START_SOUND].loadFromFile("assets/sfx/start.wav");
		mSoundBuffers[FAIL_SOUND].loadFromFile("assets/sfx/fail.wav");
	};
	SoundManager( const SoundManager& );
	SoundManager& operator =( const SoundManager& );

public:
	static SoundManager& get()
	{
		static SoundManager theSingleInstance;
		return theSingleInstance;
	}
	void play(const std::string& soundname);

private:
	std::map< std::string, sf::SoundBuffer > mSoundBuffers;
};

