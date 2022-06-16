#pragma once
namespace engine
{
	class CardTexture
	{
		sf::Texture *texture;
	public:
		CardTexture(const std::string &path) : texture(new sf::Texture())
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
		CardTexture(CardTexture &&ct) noexcept
		{
			texture = new sf::Texture(*ct.texture);
			ct.texture = nullptr;
		}
		~CardTexture() 
		{
			delete texture; 
		}
		const sf::Texture &operator*() const { return *texture; }
		sf::Texture *operator->() const
		{
			return texture;
		}
		CardTexture &operator=(const CardTexture &) = default;
		CardTexture &operator=(CardTexture &&) = default;
	};
}