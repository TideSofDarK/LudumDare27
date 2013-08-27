#pragma once

#include <string>
#include <vector>
#include <deque>

#include "pugixml.hpp"

#include <SFML/Audio.hpp>

#include "ShaderManager.h"
#include "Entity.h"
#include "Beat.h"
#include "Score.h"
#include "Cursor.h"

class Chunk : public Entity
{
private:
	std::vector<Beat>	mBeats;
	sf::Uint32			mType, mCount;
	sf::Clock			mBeatClock;
	sf::Uint32			mOffset;
public:
	Chunk(sf::String style, sf::Uint32 offset, sf::Uint32 type, sf::Uint32 count);
	virtual void update(sf::Time time);
	virtual void input(sf::Event &event);
	std::vector<Beat> &getBeatList(){return mBeats;};
	Beat &getCurrentBeat();
	void beat();
	sf::Uint32 getOffset(){return mOffset;};
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

typedef enum SONG_STATE {COUNTIN, PLAYING, END};

class Song : public Entity
{
private:
	std::deque<ScoreEffect>	mScoreEffects;
	std::deque<Chunk>		mChunks;
	pugi::xml_document		*mDoc;
	SONG_STATE				mState;
	float					mBpm;
	sf::Uint32				mCountIn;
	sf::Sprite				mPointer;
	sf::Sprite				mBack;
	sf::Music				mMusic;
	sf::Text				mCountText;
	sf::Text				mCountTextWhite;
	Cursor					mCursor;
	sf::Uint64				mScore;
	sf::Text				mScoreText;
	sf::Text				mScoreTextWhite;
	sf::Text				mAllScoreText;
	sf::Text				mAllScoreTextWhite;
	sf::String				mStylename;
	sf::Sprite				mCountdown;
	sf::Uint32				mLastSec;
public:
	Song(std::string filename);
	virtual void update(sf::Time time);
	virtual void input(sf::Event &event);
	void resetPointer();
	void updatePointer();
	void beat();
	SONG_STATE getState(){return mState;};
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
