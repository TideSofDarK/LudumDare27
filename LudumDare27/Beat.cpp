#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <iostream>

#include <Thor/Math.hpp>

#include "Beat.h"
#include "TextureManager.h"
#include "Config.h"
#include "SoundManager.h"
#include "Util.h"

Beat::Beat(sf::String style, sf::Uint32 posType, sf::Uint32 type) : mType(type), mPosType(posType)
{
	switch (mType)
	{
	case BEAT_LEFT:
		mSprite.setTexture(TextureManager::get().getTexture("assets/gfx/" + style + "/beat_left.png"));
		break;
	case BEAT_RIGHT:
		mSprite.setTexture(TextureManager::get().getTexture("assets/gfx/" + style + "/beat_right.png"));
		break;
	default:
		break;
	}
	mYVelocity = 5 + (rand() % (int)(5));
	mState = WAITING;
	mSprite.setColor(sf::Color(255,255,255,0));

	int seed = thor::random(0,7);
	std::cout << std::to_string(seed) << std::endl;

	if(BEAT_POS_TYPE_CURVE)
	{
		switch (seed)
		{
		case 0:
			LastPos::get().getLasPos().x+=120;
			break;
		case 1:
			LastPos::get().getLasPos().x-=120;
			break;
		case 2:
			LastPos::get().getLasPos().y-=120;
			break;
		case 3:
			LastPos::get().getLasPos().y+=120;
			break;
		case 4:
			LastPos::get().getLasPos().x+=120;
			LastPos::get().getLasPos().y-=120;
			break;
		case 5:
			LastPos::get().getLasPos().y-=120;
			LastPos::get().getLasPos().x-=120;
			break;
		case 6:
			LastPos::get().getLasPos().y+=120;
			LastPos::get().getLasPos().x+=120;
			break;
		case 7:
			LastPos::get().getLasPos().y+=120;
			LastPos::get().getLasPos().x-=120;
			break;
		default:
			break;
		}
		mSprite.setPosition(LastPos::get().getLasPos());
	}

	sf::FloatRect rect(50, 50, WIDTH-100, HEIGHT-100);
	if (!rect.contains(LastPos::get().getLasPos()))
	{
		posType = BEAT_POS_TYPE_RANDOM;
	}

	switch (posType)
	{
	case BEAT_POS_TYPE_RANDOM:
		mSprite.setPosition(WIDTH/3 + (rand() % (int)(WIDTH+1-mSprite.getTextureRect().width - WIDTH/3)), HEIGHT/3 + (rand() % (int)(HEIGHT+1-mSprite.getTextureRect().height - (HEIGHT/3))));
		break;
	default:
		break;
	}

	mSprite.setOrigin(mSprite.getTextureRect().width/2, mSprite.getTextureRect().height/2);
}

void Beat::update(sf::Time time)
{
	if (mState == WAITING && mState != FAILED) 
	{
		mSprite.setColor(sf::Color(255,255,255,interpolateLinear(mSprite.getColor().a, 255, 150.f / Rhythm::get().getBpm() / 20.f)));		
		if (mSprite.getPosition().y > HEIGHT)
		{
			mState = FAILED;
			SoundManager::get().play("failure");
		}
	}
	else if (mState == PRESSED)
	{
		switch (mPosType)
		{
		case BEAT_POS_TYPE_RANDOM:
			mSprite.scale(1.3f, 1.3f);
			break;
		case BEAT_POS_TYPE_CURVE:
			mSprite.move(0, 15);
			break;
		default:
			break;
		}
		
		mSprite.setColor(sf::Color(255,255,255,interpolateLinear(mSprite.getColor().a, 0, 0.2f)));
		if (!sf::FloatRect(0,0,WIDTH,HEIGHT).intersects(mSprite.getLocalBounds()) || mSprite.getColor().a == 0)
		{
			mState = ENDED;
		}
	}
	else if (mState == FAILED)
	{
		switch (mPosType)
		{
		case BEAT_POS_TYPE_RANDOM:
			mSprite.scale(1.3f, 1.3f);
			break;
		case BEAT_POS_TYPE_CURVE:
			mSprite.move(0, -15);
			break;
		default:
			break;
		}

		mSprite.setColor(sf::Color(255,interpolateLinear(mSprite.getColor().g, 0, 0.2f),interpolateLinear(mSprite.getColor().b, 0, 0.2f),interpolateLinear(mSprite.getColor().a, 0, 0.2f)));
		if (!sf::FloatRect(0,0,WIDTH,HEIGHT).intersects(mSprite.getLocalBounds()) || mSprite.getColor().a == 0)
		{
			mState = ENDED;
		}
	}
}

void Beat::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite);
}

void Beat::disappear()
{
	mState = PRESSED;
	SoundManager::get().play(HIT_SUCCESS_SOUND);
}

void Beat::fail()
{
	mState = FAILED;
	SoundManager::get().play(FAIL_SOUND);
}