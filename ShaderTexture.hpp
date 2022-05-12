#pragma once


class engine::ShaderTexture : public sf::Drawable
{
	sf::RenderTexture rtexture = sf::RenderTexture();
	sf::Shader shader;
	void draw(sf::RenderTarget &win, sf::RenderStates st) const override
	{
		win.draw(sprite);
	}
	std::string path;
	sf::Sprite sprite;
public:
	ShaderTexture(const std::string &file_path, const sf::Texture &texture)
		: path(file_path)
	{
		Vec2u utsize = texture.getSize();
		rtexture.create(utsize.x, utsize.y);
		sprite = sf::Sprite(rtexture.getTexture());
		shader.loadFromFile(path, sf::Shader::Fragment);
		shader.setUniform("u_texture", texture);
		setUniform("u_texres", sf::Glsl::Vec2(utsize));
	}
	ShaderTexture(const std::string &file_path, const Vec2u &size)
		: path(file_path)
	{
		rtexture.create(size.x, size.y);
		sprite = sf::Sprite(rtexture.getTexture());
		shader.loadFromFile(path, sf::Shader::Fragment);
		rtexture.draw(sprite, &shader);
	}
	ShaderTexture() {}
	template<class GlslType>
	void setUniform(const std::string &name, const GlslType &Val)
	{
		shader.setUniform(name, Val);
		rtexture.draw(sprite, &shader);
	}
	const sf::Texture *toTexture() const { return sprite.getTexture(); }
	sf::Sprite toSprite() const { return sprite; }
	sf::Image toImage() const { return sprite.getTexture()->copyToImage(); }
	ShaderTexture(const ShaderTexture &sht) : path(sht.path)
	{
		*this = sht;
	}
	~ShaderTexture() override = default;
	ShaderTexture &operator=(const ShaderTexture &sht)
	{
		path = sht.path;
		const Vec2u utsize = sht.sprite.getTexture()->getSize();
		rtexture.create(utsize.x, utsize.y);
		sprite = sf::Sprite(rtexture.getTexture());
		shader.loadFromFile(path, sf::Shader::Fragment);
		shader.setUniform("u_texture", sht.sprite.getTexture());
		setUniform("u_texres", sf::Glsl::Vec2(utsize));
		return *this;
	}
};