#pragma once

namespace engine
{
	template<class DrawableType>
	class clip : public sf::Drawable
	{
		sf::RenderTexture rt;
		sf::Sprite spr;
		sf::RenderStates rs;
	public:
		clip(const DrawableType &object, const Vec2u *size = nullptr)
		{
			/// <summary>
			///  clips the object in surrent time and draw it
			/// </summary>
			/// <param name="size">is a clip size</param>
			/// <param name="object">is a object to clip</param>
			bool size_is_null = false;
			if (size == nullptr)
			{
				size_is_null = true;
				size = new Vec2u(object.getGlobalBounds().width, object.getGlobalBounds().height);
			}
			rt.create(size->x, size->y);
			if (size_is_null)
				delete size;
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
}