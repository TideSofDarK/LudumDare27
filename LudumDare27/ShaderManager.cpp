#include "ShaderManager.h"

#include "Config.h"

ShaderManager::ShaderManager()
{
	mVingette.loadFromFile("assets/gfx/v.frag", sf::Shader::Fragment);
	mVingette.setParameter("size", sf::Vector2f(WIDTH,HEIGHT));
}

void ShaderManager::init(sf::Vector2f resolution)
{
	mSize = resolution;
	mWorking = false;
}

void ShaderManager::update()
{
	if (mWorking)
	{
		mCounter++;

		if (mClock.getElapsedTime().asSeconds() > mDuration.asSeconds())
		{
			mWorking = false;
		}

		mShader.setParameter("seconds", (float)mCounter);
	}
}

void ShaderManager::setCurrentEffect(std::string name, sf::Time time)
{
	if (!mWorking)
	{
		mShader.loadFromFile("assets/gfx/" + name + ".frag", sf::Shader::Fragment);
		mShader.setParameter("size", mSize);
		mWorking = true;
		mDuration = time;
		mCounter = 0;
		mClock.restart();
	}
}

void ShaderManager::draw(sf::RenderTexture &rt, sf::RenderTarget &target)
{
	sf::Sprite sprite(rt.getTexture());

	sf::RenderTexture tempRenderTexture;
	tempRenderTexture.create(WIDTH, HEIGHT);

	if (mWorking)
	{
		mShader.setParameter("texture", rt.getTexture());
		tempRenderTexture.draw(sprite, &mVingette);
		sf::Sprite tempSpr(tempRenderTexture.getTexture());
		target.draw(tempSpr, &mShader);
	}
	else
	{
		mVingette.setParameter("texture", rt.getTexture());
		target.draw(sprite, &mVingette);
	}
}

sf::Shader& ShaderManager::getCurrentEffect()
{
	return mShader;
}