#pragma once

#include "Entity.h"

class Score
{
private:
	sf::Uint32 mScore;

	Score() 
	{
		mScore = 0;
	};
	Score( const Score& );
	Score& operator =( const Score& );
public:
	static Score& get()
	{
		static Score theSingleInstance;
		return theSingleInstance;
	}
	sf::Uint32 getScore(){return mScore;};
	sf::Uint32 addScore(sf::Uint32 newScore){mScore+=newScore;return mScore;};
	void resetScore(){mScore = 0;};
};

class ScoreEffect : public Entity
{
private:
	sf::Text	mText;
	float		mNewY;
	float		mNewAlpha;
	float		mDirY;
	bool		mActive;
public:
	ScoreEffect(sf::Uint32 newScore, sf::Vector2f newPos);
	virtual void update(sf::Time time);
	virtual void input(sf::Event &event);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
