#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "State.h"
#include "Config.h"
#include "SoundManager.h"
#include "ShaderManager.h"
#include "Util.h"
#include "dirent.h"

sf::Sound			mDrip;
sf::SoundBuffer		mDripBuffer;

static bool	running;
static bool	loaded;
static bool warningLoaded;

void processEvents(sf::Window *window)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		SM::get().input(event);

		if (event.type == sf::Event::Closed) window->close();
		if (event.key.code == sf::Keyboard::Escape && event.type == sf::Event::KeyPressed) window->close();
	}
}

void loadResources()
{
	mDripBuffer.loadFromFile("assets/sfx/drip.ogg");
	mDrip.setBuffer(mDripBuffer);
	mDrip.play();

	std::vector<sf::String> folders;
	folders.push_back("warning");
	folders.push_back("menu");
	folders.push_back("canyon");
	folders.push_back("space");
	folders.push_back("eyeball");
	folders.push_back("results");
	folders.push_back("stars");
	folders.push_back("countdown");

	DIR *dir;
	struct dirent *ent;
	for (auto it = folders.begin(); it != folders.end(); it++)
	{	
		sf::String dirString = "assets//gfx//" + *it + "//";
		if ((dir = opendir (dirString.toAnsiString().c_str())) != NULL) {
			int i = 0;
			while ((ent = readdir (dir)) != NULL) {
				i++;
				if (i > 2)
				{
					printf ("%s\n", ent->d_name);
					sf::String tmpString = ent->d_name;
					TextureManager::get().getTexture("assets/gfx/" + *it + "/" + tmpString);
				}			
			}
			closedir (dir);
		}
		if (*it == "warning")
		{
			warningLoaded = true;
		}
	}

	SoundManager::get();

	SM::get().setState(MENUSTATE);

	while(mDrip.getStatus() == sf::Sound::Status::Playing)
	{	
	}

	loaded = true;
}

int main()
{
	sf::RenderWindow *window;
	window = new sf::RenderWindow(sf::VideoMode((int)WIDTH, (int)HEIGHT), sf::String(L"¡rhythmo!"), sf::Style::Close | sf::Style::Titlebar);
	window->setVerticalSyncEnabled(true);
	window->clear(sf::Color::Black);
	window->display();
	WindowAPI::get().setWindow(window);

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	sf::RenderTexture rt;
	rt.create(WIDTH, HEIGHT);

	ShaderManager::get().init(sf::Vector2f(WIDTH, HEIGHT));

	sf::Thread loadingThread(&loadResources);
	loadingThread.launch();

	//while(!warningLoaded){}
	WarningState *warningState = new WarningState();

	running = true;
	while (window->isOpen())
	{
		if (!running)
		{
			window->close();
			break;
		}
		if (loaded)
		{
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate > timePerFrame)
			{
				timeSinceLastUpdate -= timePerFrame;
				processEvents(window);
				SM::get().update(timePerFrame);
				ShaderManager::get().update();
			}

			rt.clear();
			rt.draw(SM::get());
			rt.display();

			window->clear();
			ShaderManager::get().draw(rt, *window);
			window->display();
		}	
		else
		{
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate > timePerFrame)
			{
				timeSinceLastUpdate -= timePerFrame;
				warningState->update(timePerFrame);
				ShaderManager::get().setCurrentEffect("menu", sf::seconds(20.f));
				ShaderManager::get().update();
			}

			rt.clear();
			rt.draw(*warningState);
			rt.display();

			window->clear();
			ShaderManager::get().draw(rt, *window);
			window->display();
		}
	}

	return EXIT_SUCCESS;
}