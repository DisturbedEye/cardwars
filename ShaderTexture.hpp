#pragma once


class engine::ShaderTexture : public sf::Drawable
{
	sf::RenderTexture *rtexture = new sf::RenderTexture();
	sf::Shader shader;
	void draw(sf::RenderTarget &win, sf::RenderStates st) const override
	{
		render();
		win.draw(sprite, st);
	}
	sf::Sprite sprite;
public:
	ShaderTexture(const Vec2u &size, const std::string &file, sf::Shader::Type type)
	{
		load(size, file, type);
	}
	ShaderTexture() = default;
	void load(const Vec2u &size, const std::string &file, sf::Shader::Type type)
	{
		rtexture->create(size.x, size.y);
		sprite = sf::Sprite(rtexture->getTexture());
		shader.loadFromFile(file, type);
	}
	template<class GlslType>
	void setUniform(const std::string &name, const GlslType &Val)
	{
		shader.setUniform(name, Val);
	}
	const sf::Texture *getTexture() const { return sprite.getTexture(); }
	sf::Sprite getSprite() const { return sprite; }
	sf::Image getImage() const { return sprite.getTexture()->copyToImage(); }
	ShaderTexture(const ShaderTexture &) = delete;
	ShaderTexture(ShaderTexture &&) = delete;
	void render() const
	{
		rtexture->draw(sprite, &shader);
	}
	~ShaderTexture() override { delete rtexture; }
	ShaderTexture &operator=(const ShaderTexture &) = delete;
	ShaderTexture &operator=(ShaderTexture &&) = delete;
};