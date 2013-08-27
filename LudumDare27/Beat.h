#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"

#define BEAT_LEFT 0
#define BEAT_RIGHT 1

#define BEAT_POS_TYPE_RANDOM 0
#define BEAT_POS_TYPE_CURVE 1

typedef enum BEAT_STATE {WAITING, PRESSED, FAILED, ENDED};

class LastPos
{
public:
	static LastPos& get()
	{
		static LastPos theSingleInstance;
		return theSingleInstance;
	}
	sf::Vector2f &getLasPos(){return mLastPos;};
	void setLastPos(sf::Vector2f newPos){mLastPos = newPos;};
private:
	sf::Vector2f mLastPos;
	LastPos() {};
	LastPos( const LastPos& );
	LastPos& operator =( const LastPos& );
};

class Beat : public StaticEntity
{
private:
	BEAT_STATE	mState;
	sf::Uint32	mType;
	sf::Uint32	mPosType;
	sf::Uint32	mYVelocity;		
public:
	Beat(sf::String style, sf::Uint32 posType, sf::Uint32 type);
	virtual void update(sf::Time time);
	void disappear();
	void fail();
	BEAT_STATE getState(){return mState;};
	sf::Uint32 getType(){return mType;};
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

