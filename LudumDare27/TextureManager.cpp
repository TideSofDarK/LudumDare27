#include "TextureManager.h"

const sf::Texture& TextureManager::getTexture( const std::string& filename )
{
	for(std::map<std::string, sf::Texture>::const_iterator it = textures.begin(); it != textures.end(); ++it)
	{
		if(filename == it->first)
		{
			return it->second;
		}
	}

	sf::Texture image;
	if(image.loadFromFile(filename))
	{
		textures[filename] = image;
		return textures[filename];
	}

	textures[filename] = image;
	return textures[filename];
}

void TextureManager::deleteTexture(const sf::Texture& image)
{
	for( std::map<std::string, sf::Texture>::const_iterator it = textures.begin(); it != textures.end(); ++it)
	{
		if(&image == &it->second)
		{
			textures.erase(it);
			return;
		}
	}
}

void TextureManager::deleteTexture(const std::string& filename)
{
	std::map<std::string, sf::Texture>::const_iterator it = textures.find(filename);
	if(it != textures.end()) textures.erase(it);
}