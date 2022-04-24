#pragma once

class engine::CardTexture
{
	sf::Texture *texture = new sf::Texture();
public:
	CardTexture(const std::string &path)
	{
		if (!texture->loadFromFile(path))
		{
			std::cerr << "[FileNotFoundError] " << "'" << path << "' is not correct." << '\n';
			throw;
		}
	}
	CardTexture(const CardTexture &another_texture)
	{
		texture = new sf::Texture(*another_texture.texture);
	}
	~CardTexture() 
	{
		delete texture; 
	}
	
	const sf::Texture *operator*() const { return texture; }
};