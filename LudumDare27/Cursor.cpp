#include "Cursor.h"

Cursor::Cursor()
{
	mSystem = new thor::ParticleSystem(TextureManager::get().getTexture("assets/gfx/particle.png"));

	mEmitter.setEmissionRate(16.0f);
	mEmitter.setParticleLifetime( thor::Distributions::uniform(sf::seconds(4), sf::seconds(4)) );

	mEmitter.setParticleRotation( thor::Distributions::uniform(0.f, 360.f) );

	mEmitter.setParticleScale(sf::Vector2f(0.3,0.3));
	mEmitter.setParticleVelocity(sf::Vector2f(0, 1000.0f));
	mEmitter.setParticleScale(sf::Vector2f(4.f,4.f));

	mSystem->addEmitter(thor::refEmitter(mEmitter));

	thor::ColorGradient gradient;
	gradient[0.0f] = sf::Color::Magenta;
	gradient[0.1f] = sf::Color::Red;
	gradient[0.2f] = sf::Color::Blue;
	gradient[0.3f] = sf::Color::Cyan;
	gradient[0.4f] = sf::Color::Green;
	gradient[0.5f] = sf::Color::Red;
	gradient[0.6f] = sf::Color::Magenta;
	gradient[0.7f] = sf::Color::Cyan;
	gradient[0.8f] = sf::Color::Red;
	gradient[0.9f] = sf::Color::Blue;
	gradient[1.0f] = sf::Color::Red;

	thor::ColorAnimation colorizer(gradient);
	thor::FadeAnimation fader(0.15f, 0.15f);

	mSystem->addAffector( thor::AnimationAffector(colorizer) );
	mSystem->addAffector( thor::AnimationAffector(fader) );
}

void Cursor::update(sf::Time time)
{
	mEmitter.setParticlePosition(thor::Distributions::circle(WindowAPI::get().getMousePosition(), 30.f));
	mSystem->update(time);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mEmitter.setParticleVelocity(sf::Vector2f(-1400.0f, 0));
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		mEmitter.setParticleVelocity(sf::Vector2f(1400.0f, 0));
	}
	else
	{
		mEmitter.setParticleVelocity(sf::Vector2f(0, 1400.0f));
	}
}

void Cursor::input(sf::Event &event)
{
	
}

void Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*mSystem);
}