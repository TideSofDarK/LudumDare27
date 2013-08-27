#include "Score.h"
#include "Util.h"

ScoreEffect::ScoreEffect(sf::Uint32 newScore, sf::Vector2f newPos)
{
	double p = (newScore/255.f) * 100.f;
	mText.setColor(sf::Color(newScore,255,255,255));
	mText.setFont(FontManager::get().getFont());
	mText.setString("+"+std::to_string(newScore));
	mText.setOrigin(mText.getLocalBounds().width/2, mText.getLocalBounds().height/2);
	mText.setPosition(newPos);
	mText.setCharacterSize(50);
	mActive = true;
	mNewY = newPos.y;
	mNewAlpha = 255;
}

void ScoreEffect::update(sf::Time time)
{
	if (mActive)
	{
		if (mNewAlpha > 0)
		{
			mNewAlpha -= 5.0;
		}

		if (mNewAlpha > mDirY)
		{
			mNewY -= 5.0;
		}

		if (mNewAlpha <= 0)
		{
			mActive=!mActive;
		}

		mText.setPosition(mText.getPosition().x, mNewY);
		mText.setColor(sf::Color(mText.getColor().r, mText.getColor().g, mText.getColor().b, mNewAlpha));
	}
}

void ScoreEffect::input(sf::Event &event)
{

}

void ScoreEffect::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (mActive)
	{
		/*mText.setColor(sf::Color(255u, 255u, 255u, mNewAlpha));
		mText.move(1,0);
		target.draw(mText);

		mText.move(-2,0);
		target.draw(mText);

		mText.move(1,0);

		mText.move(0,1);
		target.draw(mText);

		mText.move(0,-2);
		target.draw(mText);

		mText.move(0,1);

		mText.setColor(sf::Color(255u, 0, 0, mNewAlpha));
		target.draw(mText);*/
		target.draw(mText);
	}
}