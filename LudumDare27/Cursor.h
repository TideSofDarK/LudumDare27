#pragma once

#include <Thor/Particles.hpp>
#include <Thor/Resources.hpp>
#include <Thor/Graphics.hpp>
#include <Thor/Math.hpp>
#include <Thor/Animation.hpp>
#include <Thor/Vectors/PolarVector.hpp>

#include "Entity.h"
#include "TextureManager.h"
#include "Util.h"

class Cursor : public Entity
{
private:
	//sf::Sprite				mSprite;
	thor::ParticleSystem	*mSystem;
	thor::UniversalEmitter	mEmitter;
public:
	Cursor();
	virtual void update(sf::Time time);
	virtual void input(sf::Event &event);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

