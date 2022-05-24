#pragma once

// it need to cut the object 


template<class DrawableType>
class engine::Cutter : public sf::Drawable
{
	sf::RenderTexture *rt = new sf::RenderTexture();
	sf::Sprite bg_spr;
	sf::Shader *reverse_shader = new sf::Shader();
	sf::Sprite *full_spr = new sf::Sprite();
	DrawableType *obj;
	sf::Texture t;
public:
	Cutter(const Vec2u &size, DrawableType *object) : obj(object)
	{
		rt->create(size.x, size.y);
		full_spr->setTexture(rt->getTexture());
		reverse_shader->loadFromFile("reverse.frag", sf::Shader::Fragment);
	}
	void update(const sf::Window &win)
	{
		t.update(win);
		bg_spr.setTexture(t);
		bg_spr.setPosition(-full_spr->getPosition());
	}
	~Cutter() override
	{
		delete full_spr;
		delete reverse_shader;
		delete rt;
	}
private:
	void draw(sf::RenderTarget &win, sf::RenderStates st) const override
	{
		rt->clear();
		rt->draw(bg_spr);
		full_spr->setPosition(obj->getPosition());
		obj->setPosition(0, 0);
		rt->draw(*obj, st);
		reverse_shader->setUniform("uTexture", rt->getTexture());
		reverse_shader->setUniform("res", Vec2f(rt->getSize()));
		win.draw(*full_spr, reverse_shader);
		obj->setPosition(full_spr->getPosition());
	}
};