#pragma once
#include "Slider.hpp"


// vertical scroll class specialization
namespace engine
{
	template <class T>
	class Scrollable<T, ScrollType::Vertical> : public sf::Drawable, public sf::Transformable
	{
		Vec2f ssize; // size
		Vec2f ind; // indents between elements
		Slider<Rect, ScrollType::Vertical> slider;
		Vec2f esize; // element size
		Vec2u n; // elements count by width and height
		std::vector<T> *elems; // values is a pointers
	public:
		Scrollable(std::vector<T> *values, const unsigned int &count, const float &length)
			: elems(values)
		{
			/*
				scroll_type - type of generating (vertical, horizontal)
				count - is number of elements by width or height, it depends on scroll type
				values - it is that what will be copy by pointer!
					size of first values element is a template for all of elements 
				length - is a local height of slider
			*/
			if(!elems->empty())
				esize = elems->front()->getSize();
			slider = Slider(Rect(Vec2f(30, 1)));
			setSize(count, length);
			setSliderPos(0);
		}
		Scrollable() : elems() {}
		void setIndents(const Vec2f &inds)
		{
			ind = inds;
			setSize(n.x, ssize.y);
		}
		void setIndents(const float &x, const float &y)
		{
			setIndents(Vec2f(x, y));
		}
		void setSliderLength(const float &length)
		{
			slider.setSize(Vec2f(length, slider.getSize().y));
			slider.setLimit(0, ssize.y);
		}

		void setSliderPos(const float &pos)
		{
			slider.setPosition(slider.getPosition().x, pos);
			size_t i = 0;
			const float t = slider.getPosition().y / ssize.y;
			for (auto &el : *elems)
			{
				const float x = static_cast<float>(i % n.x), y = floorf(static_cast<float>(i) / n.x);
				const float x1 = x * (esize.x + ind.x), y1 = (esize.y + ind.y) * (y - t * n.y);
				el->setPosition(x1, y1);
				i++;
			}
		}

		void setPosition(const Vec2f &p)
		{
			Transformable::setPosition(p);
			slider.setPosition(n.x * (esize.x + ind.x), slider.getPosition().y);
			slider.setLimit(0, ssize.y);
		}

		void setPosition(const float &x, const float &y)
		{
			setPosition(Vec2f(x, y));
		}

		void setSize(unsigned count, const float &length)
		{
			/// <summary>
			/// it sets size to a list
			/// </summary>
			/// <param name="count">a value of cards by width</param>
			/// <param name="length">local list height</param>
			const size_t val_count = elems->size();
			n.x = count;
			n.y = static_cast<unsigned>(ceil(val_count / n.x)) + 1;
			ssize.x = n.x * (esize.x + ind.x);
			ssize.y = length;
			recount_slider();
		}
		void push_back(T val)
		{
			elems->push_back(&val);
			n.y = static_cast<int>(ceil(elems->size() / n.x)) + 1;
			recount_slider();
		}
		const auto &getSlider() { return slider; }
		void setSliderTexture(const sf::Texture *texture) { slider.setTexture(texture); }
		Vec2f getValueSize() const { return esize; }
		Vec2u getValueCount() const { return n; } // returns vector2 where x is val count by width, y - by height
		size_t size() const { return elems->size(); }
		Vec2f getIndents() const { return ind; }
		Vec2f getSize() const { return ssize; }
		sf::FloatRect getLocalBounds() const { return sf::FloatRect(Vec2f(), ssize); }
		sf::FloatRect getGlobalBounds() const { return sf::FloatRect(getPosition(), Vec2f(ssize.x + slider.getSize().x, ssize.y)); }

	private:
		void recount_slider()
		{
			const Vec2f sls = Vec2f(slider.getSize().x, powf(ssize.y, 2) / (n.y * (esize.y + ind.y))); // slider size
			slider.setSize(sls);
			slider.setPosition(n.x * (esize.x + ind.x), slider.getPosition().y);
			slider.setLimit(0, ssize.y);
		}
		void draw(sf::RenderTarget &win, sf::RenderStates st) const override
		{
			st.transform *= getTransform();
			for (auto &el : *elems)
				win.draw(*el, st);
			if (slider.getSize().y < ssize.y) // excepting a way when slider height >= local height 
				win.draw(slider, st);
		}
	};


	// horizontal scroll class specialization 
	template<class T>
	class Scrollable<T, ScrollType::Horizontal> : public sf::Drawable, public sf::Transformable
	{
		Vec2f ssize; // size
		Vec2f ind; // indents between elements
		Slider<Rect, ScrollType::Horizontal> slider;
		Vec2f esize; // element size
		Vec2u n; // elements count by width and height
		std::vector<T> *elems;
	public:
		Scrollable(std::vector<T> *values, const unsigned int &count, const float &length)
			: elems(values)
		{
			/*
				scroll_type - type of generating (vertical, horizontal)
				count - is number of elements by width or height, it depends on scroll type
				values - it is that what will be copy by pointer!
					size of first values element is a template for all of elements
				length - is a max width of slider
			*/
			if (!elems->empty())
				esize = elems->front()->getSize();
			slider = Slider<Rect, ScrollType::Horizontal>(Rect(Vec2f(1, 30)));
			setSize(count, length);
			setSliderPos(0);
		}
		void setIndents(const Vec2f &inds)
		{
			ind = inds;
			setSize(n.y, ssize.x);
		}
		void setIndents(const float &x, const float &y)
		{
			setIndents(Vec2f(x, y));
		}
		void setSliderLength(const float &length)
		{
			slider.setSize(Vec2f(slider.getSize().x, length));
			slider.setLimit(0, ssize.x);
		}

		void setSliderPos(const float &pos)
		{
			slider.setPosition(pos, slider.getPosition().y);
			size_t i = 0;
			const float t = slider.getPosition().x / ssize.x;
			for (auto el : *elems)
			{
				const float x = floorf(static_cast<float>(i) / n.y), // card id by width
					y = static_cast<float>(i % n.y); // card id by height
				const float x1 = (esize.x + ind.x) * (x - t * n.x), y1 = y * (esize.y + ind.y);
				el->setPosition(x1, y1);
				i++;
			}
		}

		void setPosition(const Vec2f & p)
		{
			Transformable::setPosition(p);
			slider.setPosition(slider.getPosition().x, n.y * (esize.y + ind.y));
			slider.setLimit(0, ssize.x);
		}

		void setPosition(const float &x, const float &y)
		{
			setPosition(Vec2f(x, y));
		}

		void setSize(unsigned int count, const float &length)
		{
			// count - count by height
			// length - local length
			const size_t val_count = elems->size();
	
			n.y = count;
			n.x = static_cast<unsigned>(ceil(val_count / n.y)) + 1;
			ssize.y = n.y * (esize.y + ind.y);
			ssize.x = length;

			recount_slider();
		}
		void push_back(T val)
		{
			elems->push_back(&val);
			n.x = static_cast<int>(ceil(elems->size() / n.y)) + 1;
			recount_slider();
		}
		const auto &getSlider() { return slider; }
		void setSliderTexture(const sf::Texture * texture) { slider.setTexture(texture); }
		Vec2f getValueSize() const { return esize; }
		size_t size() const { return elems->size(); }
		Vec2f getIndents() const { return ind; }
		Vec2f getSize() const { return ssize; }
		sf::FloatRect getLocalBounds() const { return sf::FloatRect(Vec2f(), ssize); }
		sf::FloatRect getGlobalBounds() const { return sf::FloatRect(getPosition(), Vec2f(ssize.x, ssize.y + slider.getSize().y)); }

	private:
		void recount_slider()
		{
			const Vec2f sls = Vec2f(powf(ssize.x, 2) / (n.x * (esize.x + ind.x)), slider.getSize().y);
			slider.setSize(sls);
			slider.setPosition(slider.getPosition().x, n.y * (esize.y + ind.y));
			slider.setLimit(0, ssize.x);
		}
		void draw(sf::RenderTarget &win, sf::RenderStates st) const override
		{
			st.transform *= getTransform();
			for (auto el : *elems)
				win.draw(*el, st);
			if (slider.getSize().x < ssize.x) // excepting a way when slider width >= local width
				win.draw(slider, st);
		}
	};
}