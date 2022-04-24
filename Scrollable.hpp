#pragma once
#include "Slider.hpp"


template <class T>
class engine::Scrollable : public sf::Drawable
{
	Vec2f position;
	Vec2f origin;
	Vec2f ssize;
	Vec2f ind;
	Slider slider;
	Vec2f esize; // element size
	Vec2u n; // elements count by width and height
	std::vector<T*> elems;
public:
	Scrollable(const std::vector<T> &values, const unsigned int &count_by_width, const float &height)
	{
		for (const auto &i : values)
			elems.push_back(new T(i));
		esize = elems[0]->getSize();
		slider.setSize(Vec2f(30, 0));
		setSize(count_by_width, height);
	}
	Scrollable(const T &sc) : position(sc.position),
		origin(sc.origin), ssize(sc.ssize), ind(sc.ind),
		slider(sc.slider), esize(sc.esize), n(sc.n)
	{
		for (auto &i : sc.elems)
			elems.push_back(new T(*i));
	}
	~Scrollable() override 
	{
		for (auto &i : elems)
			delete i;
	}
	void setOrigin(const Vec2f &or_)
	{
		origin = or_;
	}
	void setIndents(const Vec2f &inds)
	{
		ind = inds;
		recount_slider();
	}
	void setIndents(const float &x, const float &y)
	{
		setIndents(Vec2f(x, y));
	}
	void setSliderWidth(const float &width)
	{
		slider.setSize(Vec2f(width, slider.getSize().y));
		slider.setLimit(position.y, position.y + ssize.y - slider.getSize().y);
	}

	void setSliderPos(const float &y)
	{
		slider.setPosition(slider.getPosition().x, y);
	}

	void setPosition(const Vec2f &p)
	{
		position = p;
		recount_slider();
	}

	void setPosition(const float &x, const float &y)
	{
		setPosition(Vec2f(x, y));
	}

	void setSize(unsigned int card_count_by_width, const float &height)
	{
		const size_t card_count = elems.size();
		n.x = card_count_by_width;
		n.y = static_cast<int>(ceil(card_count / n.x)) + 1;
		ssize.x = n.x * (esize.x + ind.x);
		ssize.y = height;
		recount_slider();
	}
	void push_back(const T &val)
	{
		elems.push_back(new T(val));
		n.y = static_cast<int>(ceil(elems.size() / n.x)) + 1;
		recount_slider();
	}
	bool sliderIsClicked(sf::Mouse::Button b, const Vec2f &p) { return slider.isClicked(b, p); }
	bool sliderIsPressed(sf::Mouse::Button b, const Vec2f &p) { return slider.isPressed(b, p); }
	bool sliderIsHold(sf::Mouse::Button b, const Vec2f &p) { return slider.isHold(b, p); }
	bool sliderIsClicked(sf::Mouse::Button b) { return slider.isClicked(b); }
	bool sliderIsPressed(sf::Mouse::Button b) { return slider.isPressed(b); }
	bool sliderIsHold(sf::Mouse::Button b) { return slider.isHold(b); }
	Vec2f getValueSize() const { return esize; }
	size_t size() const { return elems.size(); }
	Vec2f getIndents() const { return ind; }
	Vec2f getOrigin() const { return origin; }
	Vec2f getPosition() const { return position; }
	Vec2f getSize() const { return ssize; }
	Vec2f getSliderSize() const { return slider.getSize(); }
	Vec2f getSliderPos() const { return slider.getPosition(); }
	sf::Color getSliderFillColor() const { return slider.getFillColor(); }
	sf::Color getSliderOutlineColor() const { return slider.getOutlineColor(); }
	float getSliderOutlineThickness() const { return slider.getOutlineThickness(); }
	sf::FloatRect getLocalBounds() const { return sf::FloatRect(position, ssize); }
	sf::FloatRect getGlobalBounds() const { return sf::FloatRect(position, Vec2f(ssize.x + slider.getSize().x, ssize.y)); }
	T &at(const size_t &id) { return *elems[id]; }
	T &operator[](const size_t &id) { return *elems[id]; }
	const T &operator[](const size_t &id) const { return *elems[id]; }

private:
	void recount_slider()
	{
		const Vec2f sls = Vec2f(slider.getSize().x, powf(ssize.y, 2) / (n.y * (esize.y + ind.y))); // slider size
		slider.setSize(sls);
		slider.setPosition(position.x + n.x * (esize.x + ind.x), slider.getPosition().y);
		slider.setLimit(position.y, position.y + ssize.y - sls.y);
	}
	void draw(sf::RenderTarget &win, sf::RenderStates st) const override
	{
		const float t = (slider.getPosition().y - position.y) / ssize.y;
		{
			size_t i = 0;
			for (auto &el : elems)
			{
				const float x = static_cast<float>(i % n.x), y = floorf(static_cast<float>(i) / n.x);
				const float x1 = position.x + x * (esize.x + ind.x), y1 = position.y + (esize.y + ind.y) * (y - t * n.y);
				el->setPosition(x1, y1);
				if (math::inside(Vec2f(x1, y1), position, ssize) or
					math::inside(Vec2f(x1, y1 + esize.y), position, ssize))
					win.draw(*el);
				i++;
			}
		}
		if (slider.getSize().y < ssize.y)
			win.draw(slider);
	}
};

