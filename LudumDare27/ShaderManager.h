#ifndef SHADERMANAGER_INCLUDE
#define SHADERMANAGER_INCLUDE

#include <iostream>
#include <list>
#include <string>

#include <SFML/Graphics.hpp>

class ShaderManager
{
private:
	//Effect shader
	sf::Shader mShader;

	//Window size
	sf::Vector2f mSize;

	//Timer
	sf::Clock mClock;
	sf::Time mDuration;

	//Seconds counter
	unsigned int mCounter;

	//Is working
	bool mWorking;

	//YOBA
	sf::Shader mVingette;

	//Shader list
	std::map< std::string, sf::Shader > mShaders;

	ShaderManager();
	ShaderManager( const ShaderManager& );
	ShaderManager& operator =( const ShaderManager& );

public:
	static ShaderManager& get()
	{
		static ShaderManager theSingleInstance;
		return theSingleInstance;
	}
	void init(sf::Vector2f resolution);
	void update();
	void draw(sf::RenderTexture &rt, sf::RenderTarget &target);
	sf::Shader& getCurrentEffect();
	void setCurrentEffect(std::string name, sf::Time time);
	bool isWorking() {return mWorking;};
	void stop(){mCounter = 0; mWorking = false;};
};

#endif