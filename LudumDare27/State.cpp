#include "State.h"
#include "Config.h"
#include "SoundManager.h"
#include "Util.h"

/************************************************************************/
/* Results state class													*/
/************************************************************************/

ResultsState::ResultsState()
{
	mBackSprite.setTexture(TextureManager::get().getTexture("assets/gfx/results/back.png"));
	mScoreText.setFont(FontManager::get().getFont());
	mScoreText.setCharacterSize(200);
	mScoreText.setString(std::to_string(Score::get().getScore()));
	mScoreText.setColor(sf::Color::White);
	mScoreText.move(0,150);

	mMenuSprite.setTexture(TextureManager::get().getTexture("assets/gfx/results/menu.png"));
	mMenuSprite.setPosition(835, 367);
	mStartSprite.setTexture(TextureManager::get().getTexture("assets/gfx/results/start.png"));
	mStartSprite.setPosition(835, 477);
	mQuitSprite.setTexture(TextureManager::get().getTexture("assets/gfx/results/quit.png"));
	mQuitSprite.setPosition(855, 580);

	mMenuAnimation.setSpriteSheet(TextureManager::get().getTexture("assets/gfx/results/letsgo.png"));
	mMenuAnimation.addFrame(sf::IntRect(0, 0, 367, 236/2));
	mMenuAnimation.addFrame(sf::IntRect(0, 236/2, 367, 236/2));

	mMenu = AnimatedSprite(sf::seconds(0.2f));
	mMenu.setPosition(mMenuSprite.getPosition());
	mMenu.setAnimation(mMenuAnimation);
	mMenu.play();

	mStartAnimation.setSpriteSheet(TextureManager::get().getTexture("assets/gfx/results/moar.png"));
	mStartAnimation.addFrame(sf::IntRect(0, 0, 396, 107));
	mStartAnimation.addFrame(sf::IntRect(0, 107, 396, 107));

	mStart = AnimatedSprite(sf::seconds(0.15f));
	mStart.setPosition(mStartSprite.getPosition());
	mStart.setAnimation(mStartAnimation);
	mStart.play();

	mQuitAnimation.setSpriteSheet(TextureManager::get().getTexture("assets/gfx/results/boohoo.png"));
	mQuitAnimation.addFrame(sf::IntRect(0, 0, 316, 107));
	mQuitAnimation.addFrame(sf::IntRect(0, 107, 316, 107));

	mQuit = AnimatedSprite(sf::seconds(0.13f));
	mQuit.setPosition(mQuitSprite.getPosition());
	mQuit.setAnimation(mQuitAnimation);
	mQuit.play();
}

void ResultsState::update(sf::Time time)
{
	mMenu.update(time);
	mStart.update(time);
	mQuit.update(time);
}

void ResultsState::input(sf::Event &event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (mMenuSprite.getGlobalBounds().contains(WindowAPI::get().getMousePosition()))
		{
			StateManager::get().startTransition(MENUSTATE);
			Score::get().resetScore();
		}

		if (mStartSprite.getGlobalBounds().contains(WindowAPI::get().getMousePosition()))
		{
			StateManager::get().startTransition(GAMESTATE);
			Score::get().resetScore();
		}

		if (mQuitSprite.getGlobalBounds().contains(WindowAPI::get().getMousePosition()))
		{
			WindowAPI::get().getWindow()->close();
		}
	}
}

void ResultsState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mBackSprite);
	target.draw(mScoreText);

	if (mMenuSprite.getGlobalBounds().contains(WindowAPI::get().getMousePosition()))
	{
		target.draw(mMenu);
	}
	else
	{
		target.draw(mMenuSprite);
	}

	if (mStartSprite.getGlobalBounds().contains(WindowAPI::get().getMousePosition()))
	{
		target.draw(mStart);
	}
	else
	{
		target.draw(mStartSprite);
	}

	if (mQuitSprite.getGlobalBounds().contains(WindowAPI::get().getMousePosition()))
	{
		target.draw(mQuit);
	}
	else
	{
		target.draw(mQuitSprite);
	}
}

/************************************************************************/
/* Menu state class														*/
/************************************************************************/

MenuState::MenuState()
{
	mBackSprite.setTexture(TextureManager::get().getTexture("assets/gfx/menu/menu1.png"));
	mRect = sf::FloatRect(WIDTH/3, HEIGHT/4, WIDTH/3, HEIGHT/2);

	mReadyAnimation.setSpriteSheet(TextureManager::get().getTexture("assets/gfx/menu/anus.png"));
	mReadyAnimation.addFrame(sf::IntRect(0,0, 335, 259));
	mReadyAnimation.addFrame(sf::IntRect(335,0, 335, 259));

	mReadySprite = AnimatedSprite(sf::seconds(0.1f));
	mReadySprite.setPosition(WIDTH/3 + 34, HEIGHT/4 + 34);
	mReadySprite.setAnimation(mReadyAnimation);
	mReadySprite.play();

	mCreditAnimation.setSpriteSheet(TextureManager::get().getTexture("assets/gfx/menu/credit.png"));
	mCreditAnimation.addFrame(sf::IntRect(0,0, 616, 109));
	mCreditAnimation.addFrame(sf::IntRect(0, 109, 616, 109));

	mCreditSprite = AnimatedSprite(sf::seconds(0.15f));
	mCreditSprite.setPosition(30, HEIGHT-150);
	mCreditSprite.setAnimation(mCreditAnimation);
	mCreditSprite.play();

	mAuraAnimation.setSpriteSheet(TextureManager::get().getTexture("assets/gfx/menu/aura.png"));
	mAuraAnimation.addFrame(sf::IntRect(0,0, 926, 662));
	mAuraAnimation.addFrame(sf::IntRect(0, 662, 926, 662));

	mAuraSprite = AnimatedSprite(sf::seconds(0.15f));
	
	mAuraSprite.setAnimation(mAuraAnimation);
	mAuraSprite.play();
	mAuraSprite.setOrigin(926/2, 662/2);
	mAuraSprite.setPosition(WIDTH/2,HEIGHT/2);

	mTitle.setTexture(TextureManager::get().getTexture("assets/gfx/menu/title.png"));
	mTitle.setPosition(WIDTH/2 - mTitle.getTextureRect().width/2,0);

	mMusic1.openFromFile("assets/sfx/unt1tled.ogg");
}

void MenuState::update(sf::Time time)
{
	mCreditSprite.update(time);
	mAuraSprite.update(time);
	if (mRect.contains(WindowAPI::get().getMousePosition()))
	{
		mBackSprite.setTexture(TextureManager::get().getTexture("assets/gfx/menu/menu2.png"));
		mReadySprite.update(time);
	}
	else
	{
		mBackSprite.setTexture(TextureManager::get().getTexture("assets/gfx/menu/menu1.png"));
	}

	ShaderManager::get().setCurrentEffect("menu", sf::seconds(120.f));

	if (mMusic1.getStatus() != sf::Sound::Status::Playing)
	{
		mMusic1.play();
	}
}

void MenuState::input(sf::Event &event)
{
	if (mRect.contains(WindowAPI::get().getMousePosition()) && event.type == sf::Event::MouseButtonPressed)
	{
		StateManager::get().startTransition(GAMESTATE);
		mMusic1.stop();
	}
}

void MenuState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mBackSprite);
	if (mRect.contains(WindowAPI::get().getMousePosition()))
	{
		target.draw(mReadySprite);
		target.draw(mAuraSprite);
	}
	else
	{
		target.draw(mCreditSprite);
		target.draw(mTitle);
	}
}

/************************************************************************/
/* Game state class														*/
/************************************************************************/

GameState::GameState()
{
	sf::Uint32 seed = thor::random(0,4);
	switch (seed)
	{
	case 0:
		mSong = new Song("drug");
		break;
	case 1:
		mSong = new Song("blow");
		break;
	case 2:
		mSong = new Song("boots");
		break;
	case 3:
		mSong = new Song("grow");
		break;
	case 4:
		mSong = new Song("kissntell");
		break;
	default:
		mSong = new Song("drug");
		break;
	}
}

void GameState::update(sf::Time time)
{
	mSong->update(time);
	if (mSong->getState() == END)
	{
		if (Score::get().getScore() > 5000)
		{
			StateManager::get().startTransition(RESULTSTATE);
		}
		else
		{
			delete mSong;
			sf::Uint32 seed = thor::random(0,4);
			switch (seed)
			{
			case 0:
				mSong = new Song("drug");
				break;
			case 1:
				mSong = new Song("blow");
				break;
			case 2:
				mSong = new Song("boots");
				break;
			case 3:
				mSong = new Song("grow");
				break;
			case 4:
				mSong = new Song("kissntell");
				break;
			default:
				mSong = new Song("drug");
				break;
			}
		}
	}
}

void GameState::input(sf::Event &event)
{
	mSong->input(event);
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*mSong);
}

/************************************************************************/
/* Warning state class													*/
/************************************************************************/

WarningState::WarningState()
{
	mBackSprite.setTexture(TextureManager::get().getTexture("assets/gfx/warning/back.png"));

	mOneAnimation.setSpriteSheet(TextureManager::get().getTexture("assets/gfx/warning/one.png"));
	mOneAnimation.addFrame(sf::IntRect(0,0, 1134, 200));
	mOneAnimation.addFrame(sf::IntRect(0,200, 1134, 200));

	mOne = AnimatedSprite(sf::seconds(0.13f));
	mOne.setPosition(100, 60);
	mOne.setAnimation(mOneAnimation);
	mOne.play();

	mStarsAnimation.setSpriteSheet(TextureManager::get().getTexture("assets/gfx/warning/stars.png"));
	mStarsAnimation.addFrame(sf::IntRect(0,0, 860, 1052/2));
	mStarsAnimation.addFrame(sf::IntRect(0,1052/2, 860, 1052/2));

	mStars = AnimatedSprite(sf::seconds(0.13f));
	mStars.setPosition(420, 105);
	mStars.setAnimation(mStarsAnimation);
	mStars.play();

	mTwoAnimation.setSpriteSheet(TextureManager::get().getTexture("assets/gfx/warning/two.png"));
	mTwoAnimation.addFrame(sf::IntRect(0,0, 944, 206));
	mTwoAnimation.addFrame(sf::IntRect(0,206, 944, 206));

	mTwo = AnimatedSprite(sf::seconds(0.11f));
	mTwo.setPosition(270, 160);
	mTwo.setAnimation(mTwoAnimation);
	mTwo.play();

	mThreeAnimation.setSpriteSheet(TextureManager::get().getTexture("assets/gfx/warning/three.png"));
	mThreeAnimation.addFrame(sf::IntRect(0,0, 1236, 422));
	mThreeAnimation.addFrame(sf::IntRect(0,422, 1236, 422));

	mThree = AnimatedSprite(sf::seconds(0.15f));
	mThree.setPosition(45, 320);
	mThree.setAnimation(mThreeAnimation);
	mThree.play();

	mClock.restart();

	mCurrent = 0;
}

void WarningState::update(sf::Time time)
{
	mOne.update(time);
	mTwo.update(time);
	mThree.update(time);
	mStars.update(time);

	if (mClock.getElapsedTime().asSeconds() > 0.5f && mCurrent == 1)
	{
		mCurrent++;
		mClock.restart();
	}
	if (mClock.getElapsedTime().asSeconds() > 1.5f && mCurrent < 3)
	{
		mCurrent++;
		mClock.restart();
	}
}

void WarningState::input(sf::Event &event)
{

}

void WarningState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mBackSprite);

	if (mCurrent == 0)
	{
		target.draw(mOne);
	}
	else if (mCurrent == 1)
	{
		target.draw(mOne);
		target.draw(mStars);
	}
	else if (mCurrent == 2)
	{
		target.draw(mOne);
		target.draw(mTwo);
	}
	else if (mCurrent == 3)
	{
		target.draw(mOne);
		target.draw(mTwo);
		target.draw(mThree);
	}
}

/************************************************************************/
/* State manager class													*/
/************************************************************************/

bool StateManager::setState(sf::Uint32 stateNumber)
{
	if (stateNumber == MENUSTATE || stateNumber == GAMESTATE || stateNumber == RESULTSTATE)
	{
		if (mCurrentState != nullptr) //!= nullptr)
		{
			mPreviousState = mCurrentState;
			mCurrentState = nullptr;
		}

		switch (stateNumber)
		{
		case RESULTSTATE:
			mCurrentState = new ResultsState();
			break;
		case MENUSTATE:
			mCurrentState = new MenuState();
			break;
		case GAMESTATE:
			mCurrentState = new GameState();
			break;
		default:
			break;
		}

		return true;
	}
	else return false;
}

bool StateManager::startTransition(sf::Uint32 stateNumber)
{
	mState = TRANSITION;
	mNextState = stateNumber;
	return true;
}

bool StateManager::setPreviousState()
{
	if (mPreviousState != nullptr)
	{
		std::swap(mCurrentState, mPreviousState);
		return true;
	}
	else return false;
}

void StateManager::update(sf::Time time)
{
	if (mState != TRANSITION) mCurrentState->update(time);
	else
	{
		if (mStateTransitionCounter < 255.f)
		{
			mStateTransitionCounter+=5.f;
		}
		else
		{
			mStateTransitionCounter = 0.f;
			mState = WORKING;
			setState(mNextState);
		}
	}
}

void StateManager::input(sf::Event &event)
{
	if (mState != TRANSITION) mCurrentState->input(event);
}

void StateManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*mCurrentState);
	if (mState == TRANSITION)
	{
		sf::RectangleShape blackRect;
		blackRect.setSize(sf::Vector2f(WIDTH, HEIGHT));
		blackRect.setFillColor(sf::Color(0u,0u,0u,(int)mStateTransitionCounter));
		target.draw(blackRect);
	}
}