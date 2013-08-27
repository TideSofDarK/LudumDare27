#pragma once

#include <SFML/Graphics.hpp>

#include "AnimatedSprite.h"

class Entity : public sf::Drawable
{
public:
	virtual void update(sf::Time time)=0;
private:
	virtual void draw(const sf::RenderTarget& target, const sf::RenderStates states) const {};
};

class AnimatedEntity : public Entity
{
protected:
	AnimatedSprite mSprite;
public:
	virtual void update(sf::Time time)=0;
private:
	virtual void draw(const sf::RenderTarget& target, const sf::RenderStates states) const {};
};

class StaticEntity : public Entity
{
protected:
	sf::Sprite mSprite;
public:
	virtual void update(sf::Time time)=0;
	sf::Sprite &getSprite(){return mSprite;};
private:
	virtual void draw(const sf::RenderTarget& target, const sf::RenderStates states) const {};
};
