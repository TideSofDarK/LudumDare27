#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Beat.h"
#include "Song.h"

#define MENUSTATE		1
#define OPTIONSSTATE	2
#define GAMESTATE		3
#define RESULTSTATE		4

#define StateManager SM

class State : public sf::Drawable
{
public:
	virtual void update(sf::Time time)=0;
	virtual void input(sf::Event &event)=0;
private:
	virtual void draw(const sf::RenderTarget& target, const sf::RenderStates states) const {};
};

class MenuState : public State
{
private:
	sf::Sprite			mBackSprite;
	sf::Shader			mShader;
	sf::FloatRect		mRect;
	AnimatedSprite		mReadySprite;
	Animation			mReadyAnimation;
	AnimatedSprite		mCreditSprite;
	Animation			mCreditAnimation;
	AnimatedSprite		mAuraSprite;
	Animation			mAuraAnimation;
	sf::Sprite			mTitle;
	sf::Music			mMusic1;
public:
	MenuState();
	virtual void update(sf::Time time);
	virtual void input(sf::Event &event);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class GameState : public State
{
private:
	sf::Sprite			mBackSprite;
	std::vector<Beat>	mBeats;
	Song				*mSong;
public:
	GameState();
	virtual void update(sf::Time time);
	virtual void input(sf::Event &event);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class ResultsState : public State
{
private:
	sf::Sprite			mBackSprite;
	sf::Text			mScoreText;
	sf::Sprite			mMenuSprite;
	sf::Sprite			mStartSprite;
	sf::Sprite			mQuitSprite;
	AnimatedSprite		mStart;
	Animation			mStartAnimation;
	AnimatedSprite		mQuit;
	Animation			mQuitAnimation;
	AnimatedSprite		mMenu;
	Animation			mMenuAnimation;
public:
	ResultsState();
	virtual void update(sf::Time time);
	virtual void input(sf::Event &event);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class WarningState : public State
{
private:
	sf::Sprite			mBackSprite;
	AnimatedSprite		mOne;
	Animation			mOneAnimation;
	AnimatedSprite		mTwo;
	Animation			mTwoAnimation;
	AnimatedSprite		mThree;
	Animation			mThreeAnimation;
	AnimatedSprite		mStars;
	Animation			mStarsAnimation;
	sf::Uint32			mCurrent;
	sf::Clock			mClock;
public:
	WarningState();
	virtual void update(sf::Time time);
	virtual void input(sf::Event &event);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class StateManager : public State
{
private:
	typedef enum STATE_MANAGER_STATE { WORKING, TRANSITION };

	STATE_MANAGER_STATE mState;

	State				*mCurrentState;
	State				*mPreviousState;

	sf::Uint32			mNextState;
	float				mStateTransitionCounter;

	StateManager() 
	{
		mStateTransitionCounter = 0.f;

		mState = WORKING;

		mCurrentState = mPreviousState = nullptr;
	};
	StateManager( const StateManager& );
	StateManager& operator =( const StateManager& );
public:
	static StateManager& get()
	{
		static StateManager theSingleInstance;
		return theSingleInstance;
	}

	STATE_MANAGER_STATE getState() {return mState;};
	State &getCurrentState(){return *mCurrentState;};
	State &getPreviousState(){return *mPreviousState;};
	bool setPreviousState();
	bool setState(sf::Uint32 stateNumber = MENUSTATE);
	bool startTransition(sf::Uint32 stateNumber);

	virtual void update(sf::Time time);
	virtual void input(sf::Event &event);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};