#pragma once

#include <SFML/Graphics.hpp>

//Linear interpolation
float interpolateLinear(const float variableA, const float variableB, float factor);

//Vector interpolation
sf::Vector2f interpolateVector(const sf::Vector2f& pointA, const sf::Vector2f& pointB, float factor);

class Rhythm
{
private:
	sf::Clock			mClock;
	float				mBpm;

	Rhythm() {};
	Rhythm( const Rhythm& );
	Rhythm& operator =( const Rhythm& );

public:
	static Rhythm& get()
	{
		static Rhythm theSingleInstance;
		return theSingleInstance;
	}
	void start(float newBpm);
	bool onBeat(bool restart);
	float getBpm(){return mBpm;};
};

class FontManager
{
public:
	static FontManager& get()
	{
		static FontManager theSingleInstance;
		return theSingleInstance;
	}

private:
	sf::Font mDefaultFont;

	FontManager() 
	{
		mDefaultFont.loadFromFile("assets/fonts/default.ttf");
	};
	FontManager( const FontManager& );
	FontManager& operator =( const FontManager& );

public:
	sf::Font &getFont(){return mDefaultFont;};
};

class WindowAPI
{
public:
	static WindowAPI& get()
	{
		static WindowAPI theSingleInstance;
		return theSingleInstance;
	}
	sf::Vector2f &getMousePosition(){return sf::Vector2f(sf::Mouse::getPosition(*mWindow));};
	void setWindow(sf::Window *window){mWindow = window;};
	sf::Window *getWindow(){return mWindow;};

private:
	WindowAPI() {};
	WindowAPI( const WindowAPI& );
	WindowAPI& operator =( const WindowAPI& );
	sf::Window *mWindow;
};