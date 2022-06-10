#pragma once

namespace engine
{
	class ShaderTexture : public sf::Drawable, public sf::Transformable
	{
		sf::RenderTexture *render_texture = new sf::RenderTexture();
		sf::Shader shader;
		sf::Sprite sprite;
	public:
		ShaderTexture(const Vec2u &size, const std::string &file, sf::Shader::Type type)
		{
			render_texture->create(size.x, size.y);
			sprite = sf::Sprite(render_texture->getTexture());
			load(file, type);
		}
		ShaderTexture() {}
		ShaderTexture(const ShaderTexture &) = delete;
		ShaderTexture(ShaderTexture &&) = delete;
		void render() const
		{
			render_texture->draw(sprite, &shader);
		}
		~ShaderTexture() override { delete render_texture; }
		void load(const std::string &file, sf::Shader::Type type)
		{
			shader.loadFromFile(file, type);
		}
		void add(const Drawable &drawable, sf::RenderStates states = sf::RenderStates::Default) const
		{
			render_texture->draw(drawable, states);
		}
		void fill(sf::Color clr = {0, 0, 0, 255}) const
		{
			render_texture->clear(clr);
		}
		template<class GlslType>
		void setUniform(const std::string &name, const GlslType &Val)
		{
			shader.setUniform(name, Val);
		}
		const sf::Texture *getTexture() const { return sprite.getTexture(); }
		sf::Sprite getSprite() const { return sprite; }
		sf::Image getImage() const { return sprite.getTexture()->copyToImage(); }
		ShaderTexture &operator=(const ShaderTexture &) = delete;
		ShaderTexture &operator=(ShaderTexture &&) = delete;
	private:
		void draw(sf::RenderTarget &win, sf::RenderStates states) const override
		{
			render();
			states.transform *= getTransform();
			win.draw(sprite, states);
		}
	};
}