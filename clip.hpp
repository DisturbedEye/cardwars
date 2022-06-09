#pragma once

template<class DrawableType>
class engine::clip : public sf::Drawable
{
	sf::RenderTexture rt;
	sf::Sprite spr;
	sf::RenderStates rs;
public:
	clip(const Vec2u &size, const DrawableType &object)
	{
		/// <summary>
		///  it draws a clipped object  
		/// </summary>
		/// <param name="size">is a clip size</param>
		/// <param name="object">is a object to clip</param>
		rt.create(size.x, size.y);
		spr.setTexture(rt.getTexture());
		rt.clear({ 0, 0, 0, 0 });
		sf::Transform t;
		t.translate(0, object.getGlobalBounds().height);
		t.scale(1.f, -1.f);
		rs.transform = object.getInverseTransform();
		rt.draw(object, rs);
		rt.setActive(false);
		rs.transform = object.getTransform();
		rs.transform *= t;
	}
private:
	void draw(sf::RenderTarget &win, sf::RenderStates st) const override
	{
		st.transform *= rs.transform;
		win.draw(spr, st);
	}
};