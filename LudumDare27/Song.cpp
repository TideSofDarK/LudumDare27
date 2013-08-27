#include "iostream"

#include "Song.h"
#include "Util.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Config.h"

Chunk::Chunk(sf::String style, sf::Uint32 offset, sf::Uint32 type, sf::Uint32 count) : mType(type), mCount(count), mOffset(offset)
{
	for (int i = 0; i < count; i++)
	{
		//mBeats.push_back(Beat(type, (rand() % (int)(101)) % 2 ? BEAT_LEFT : BEAT_RIGHT, color));
		mBeats.push_back(Beat(style, type, BEAT_LEFT));
	}
}

void Chunk::beat()
{
	for (auto i = mBeats.begin(); i != mBeats.end(); i++)
	{	
		if (i->getState() != ENDED)
		{
			if (i->getState() == WAITING) 
			{
				//i->fail();
				break;
			}
		}
	}
}

void Chunk::update(sf::Time time)
{
	for (auto i = mBeats.begin(); i != mBeats.end();)
	{	
		if (i->getState() != ENDED)
		{
			i->update(time);

			if (i->getState() == WAITING) 
			{
				break;
			}
			i++;
		}
		else
		{
			i = mBeats.erase(i);
		}
	}
}

Beat &Chunk::getCurrentBeat()
{
	for (auto i = mBeats.begin(); i != mBeats.end(); i++)
	{	
		if (i->getState() != ENDED)
		{
			if (i->getState() == WAITING) 
			{
				return *i;
				break;
			}
		}
	}
	return mBeats.back();
}

void Chunk::input(sf::Event &event)
{

}

void Chunk::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto i = mBeats.begin(); i != mBeats.end(); i++)
	{
		target.draw(*i);
	}
	//target.draw(mBeats.back());
}

Song::Song(std::string filename)
{
	ShaderManager::get().stop();

	LastPos::get().setLastPos(sf::Vector2f(WIDTH/2, HEIGHT/2));

	mDoc = new pugi::xml_document();
	pugi::xml_parse_result result = mDoc->load_file(("assets/songs/" + filename + ".xml").c_str());
	if (result.status == pugi::status_ok)
	{
		pugi::xml_node songNode = mDoc->child("song");

		for (pugi::xml_node chunk: songNode.children())
		{
			mChunks.push_front(Chunk(songNode.attribute("style").as_string(), chunk.attribute("time").as_int(), chunk.attribute("type").as_int(), chunk.attribute("count").as_int()));
		}

		mBpm = songNode.attribute("bpm").as_int();

		sf::String tmp = songNode.attribute("filename").as_string();
		mMusic.openFromFile("assets/sfx/" + tmp);
		tmp = songNode.attribute("style").as_string();
		mStylename = tmp;
		mBack.setTexture(TextureManager::get().getTexture("assets/gfx/" + mStylename + "/" + mStylename + ".png"));
	}

	Rhythm::get().start(mBpm);

	mState = COUNTIN;
	mCountIn = 0;

	resetPointer();
	mPointer.setOrigin(mPointer.getTextureRect().width/2, mPointer.getTextureRect().height/2);

	mCountText.setFont(FontManager::get().getFont());
	mCountText.setString(std::to_string(mCountIn+1));
	mCountText.setCharacterSize(400);
	mCountText.setColor(sf::Color(192,255,0,255));
	mCountText.setScale(0.5f, 0.5f);
	mCountText.setOrigin(mCountText.getLocalBounds().width/2, mCountText.getLocalBounds().height/2);
	mCountText.setPosition(sf::Vector2f(WIDTH/2, HEIGHT/2));

	mScoreText.setFont(FontManager::get().getFont());
	mScoreText.setCharacterSize(40);
	mScoreText.setPosition(30,30);
	if (mStylename == "canyon")
	{
		mScoreText.setColor(sf::Color::Black);
	}
	else
	{
		mScoreText.setColor(sf::Color::White);
	}
	mScore=0;

	mAllScoreText = mScoreText;
	mAllScoreText.setCharacterSize(25);
	mAllScoreText.move(0,60);
}

void Song::update(sf::Time time)
{
	if ((int)mMusic.getPlayingOffset().asSeconds() != 0 && (int)mMusic.getPlayingOffset().asSeconds() != 11) mCountdown.setTexture(TextureManager::get().getTexture("assets/gfx/countdown/" + std::to_string((int)mMusic.getPlayingOffset().asSeconds()) + ".png"));
	mCountdown.setOrigin(mCountdown.getTextureRect().width/2, mCountdown.getTextureRect().height/2);
	mCountdown.setColor(sf::Color(255,255,255,interpolateLinear(mCountdown.getColor().a, 255, 0.05)));
	mCountdown.setScale(interpolateLinear(mCountdown.getScale().x, 1.f, 150.f / mBpm / 10.f), interpolateLinear(mCountdown.getScale().y, 1.f, 150.f / mBpm / 10.f));
	mCountdown.setPosition(WIDTH/2, HEIGHT/2);
	if (mStylename == "eyeball")
	{
		if ((rand() % (int)(51)) == 1)
		{
			mBack.setTexture(TextureManager::get().getTexture("assets/gfx/" + mStylename + "/eyeball3.png"));
		}
		else if ((rand() % (int)(51)) == 2)
		{
			mBack.setTexture(TextureManager::get().getTexture("assets/gfx/" + mStylename + "/eyeball2.png"));
		}
		else
		{
			mBack.setTexture(TextureManager::get().getTexture("assets/gfx/" + mStylename + "/eyeball.png"));
		}
	}
	if (mStylename == "canyon")
	{
		if ((rand() % (int)(51)) != 1)
		{
			mBack.setTexture(TextureManager::get().getTexture("assets/gfx/" + mStylename + "/canyon.png"));
		}
		else
		{
			mBack.setTexture(TextureManager::get().getTexture("assets/gfx/" + mStylename + "/canyon1.png"));
		}
	}
	if (mStylename == "space")
	{
		if ((rand() % (int)(51)) != 1)
		{
			mBack.setTexture(TextureManager::get().getTexture("assets/gfx/" + mStylename + "/space.png"));
		}
		else
		{
			mBack.setTexture(TextureManager::get().getTexture("assets/gfx/" + mStylename + "/space.png"));
		}
	}
	mCursor.update(time);
	if (Rhythm::get().onBeat(true))
	{
		beat();
	}
	if (mState == COUNTIN)
	{
		mCountText.setScale(interpolateLinear(mCountText.getScale().x, 1.f, 150.f / mBpm / 10.f), interpolateLinear(mCountText.getScale().y, 1.f, 150.f / mBpm / 10.f));
		mCountTextWhite = mCountText;
		mCountTextWhite.setColor(sf::Color::White);
		mCountTextWhite.move(0,15);

		if (mCountIn >= 4  && mMusic.getPlayingOffset().asSeconds() >= mChunks.back().getOffset())
		{
			updatePointer();
		}
	}
	else if (mState == PLAYING)
	{
		mScoreText.setString(std::to_string(mScore) + " now");
		mScoreTextWhite = mScoreText;
		if (mStylename != "canyon")
		{
			mScoreTextWhite.setColor(sf::Color::Black);
		}
		else
		{
			mScoreTextWhite.setColor(sf::Color::White);
		}
		mScoreTextWhite.move(7,7);

		mAllScoreText.setString(std::to_string(Score::get().getScore()) + " overall");
		mAllScoreTextWhite = mAllScoreText;
		if (mStylename != "canyon")
		{
			mAllScoreTextWhite.setColor(sf::Color::Black);
		}
		else
		{
			mAllScoreTextWhite.setColor(sf::Color::White);
		}
		mAllScoreTextWhite.move(7,7);

		mChunks.back().update(time);

		if (mChunks.back().getBeatList().size() >= 1)updatePointer();
	}
	if (mChunks.back().getBeatList().size() != 0 && mChunks.back().getCurrentBeat().getState() == WAITING && mPointer.getScale().x <= 1.25f)
	{
		mChunks.back().getCurrentBeat().fail();
		ShaderManager::get().setCurrentEffect("tv", sf::seconds(0.1f));
		resetPointer();
	}
	for (auto i = mScoreEffects.begin(); i != mScoreEffects.end(); i++)
	{
		i->update(time);
	}
}

void Song::beat()
{
	if (mState == COUNTIN)
	{
		if (mCountIn <=3)
		{
			ShaderManager::get().setCurrentEffect("glitch", sf::seconds(0.5f));
			mCountIn++;
			mCountText.setString(std::to_string(mCountIn+1));
			mCountText.setScale(0.5f, 0.5f);
		}

		if (mCountIn+1 == 4)
		{
			mCountText.setColor(sf::Color(255,0,255,255));
		}

		if (mCountIn >= 4)
		{
			if (mMusic.getPlayingOffset().asSeconds() >= mChunks.back().getOffset())
			{
				mState = PLAYING;
				SoundManager::get().play(START_SOUND);
				mLastSec=1;
			}		

			if (mMusic.getStatus() != sf::Music::Playing) mMusic.play();
		}
	}
	else if (mState == PLAYING)
	{		
		if (mLastSec != (int)mMusic.getPlayingOffset().asSeconds())
		{
			mCountdown.setColor(sf::Color(255,255,255,0));
			mCountdown.setScale(sf::Vector2f(12.f,12.f));

			mLastSec = (int)mMusic.getPlayingOffset().asSeconds();
		}		
		if (mChunks.back().getBeatList().size() != 0)
		{
			mChunks.back().beat();
			resetPointer();
		}
		else
		{
			if (mChunks.size() > 1)
			{
				mChunks.pop_back();
				SoundManager::get().play(START_SOUND);
				resetPointer();
			}
			else
			{
				if (mMusic.getStatus() != sf::Music::Status::Playing)mState = END;
			}		
		}	
	}
}

void Song::updatePointer()
{
	if (mChunks.back().getBeatList().size() != 0 )
	{
		mPointer.setPosition(mChunks.back().getCurrentBeat().getSprite().getPosition());
		mPointer.setColor(sf::Color(255,255,255,interpolateLinear(mPointer.getColor().a, 255, 0.05)));
		mPointer.setScale(interpolateLinear(mPointer.getScale().x, 1.f, 150.f / mBpm / 10.f), interpolateLinear(mPointer.getScale().y, 1.f, 150.f / mBpm / 10.f));
	}	
}

void Song::input(sf::Event &event)
{
	mCursor.input(event);
	if (mState == PLAYING)
	{
		mChunks.back().input(event);
	}	

	if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed) 
	{
		if (mChunks.back().getBeatList().size() != 0 && mChunks.back().getCurrentBeat().getSprite().getGlobalBounds().contains(WindowAPI::get().getMousePosition().x, WindowAPI::get().getMousePosition().y) && mChunks.back().getCurrentBeat().getState() == WAITING && mPointer.getScale().x < 1.7f)
		{
			double p = (1.25f / mPointer.getScale().x) * 100.f;
			mScore+=p;
			Score::get().addScore(p);

			mScoreEffects.push_back(ScoreEffect(p, mChunks.back().getCurrentBeat().getSprite().getPosition()));
			mChunks.back().getCurrentBeat().disappear();
			ShaderManager::get().setCurrentEffect("tv", sf::seconds(0.5f));
			resetPointer();			
		}
	}
}

void Song::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mBack);
	if (mState != COUNTIN)
	{
		target.draw(mScoreTextWhite);
		target.draw(mScoreText);

		target.draw(mAllScoreTextWhite);
		target.draw(mAllScoreText);
	}
	if (mState == COUNTIN)
	{
		target.draw(mCountTextWhite);
		target.draw(mCountText);
	}
	if (mState == PLAYING)
	{
		target.draw(mCountdown);
		target.draw(mChunks.back());
	}
	if (mState != END) target.draw(mPointer);
	target.draw(mCursor);
	for (auto i = mScoreEffects.begin(); i != mScoreEffects.end(); i++)
	{
		target.draw(*i);
	}
}

void Song::resetPointer()
{
	mPointer.setTexture(TextureManager::get().getTexture("assets/gfx/pointer.png"));
	mPointer.setColor(sf::Color(255,255,255,0));
	mPointer.setScale(sf::Vector2f(12.f,12.f));
}