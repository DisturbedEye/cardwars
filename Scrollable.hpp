#pragma once
#include "Slider.hpp"


// vertical scroll class specialization
 template <class T>
class engine::Scrollable<T, engine::ScrollType::Vertical> : public sf::Drawable
{
	Vec2f position;
	Vec2f origin;
	Vec2f ssize; // size
	Vec2f ind; // indents between elements
	Slider<engine::ScrollType::Vertical> slider;
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
			length - is a max height of slider
		*/
		if(!elems->empty())
			esize = elems->front()->getSize();
		slider = Slider<engine::ScrollType::Vertical>(Vec2f(30, 1));
		setSize(count, length);
	}
	Scrollable(const Scrollable<T> &sc)
	{
		*this = sc;
	}
	~Scrollable() override = default;
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
	void setSliderLength(const float &length)
	{
		slider.setSize(Vec2f(length, slider.getSize().y));
		slider.setLimit(position.y, position.y + ssize.y);
	}

	void setSliderPos(const float &pos)
	{
		slider.setPosition(slider.getPosition().x, pos);
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

	void setSize(unsigned int count, const float &length)
	{
		const size_t val_count = elems->size();
		n.x = count;
		n.y = static_cast<int>(ceil(val_count / n.x)) + 1;
		ssize.x = n.x * (esize.x + ind.x);
		ssize.y = length;
		recount_slider();
	}
	void push_back(const T &val)
	{
		elems->push_back(&val);
		n.y = static_cast<int>(ceil(elems->size() / n.x)) + 1;
		recount_slider();
	}
	bool sliderIsClicked(sf::Mouse::Button b, const Vec2f &p) { return slider.isClicked(b, p); }
	bool sliderIsPressed(sf::Mouse::Button b, const Vec2f &p) { return slider.isPressed(b, p); }
	bool sliderIsHold(sf::Mouse::Button b, const Vec2f &p) { return slider.isHold(b, p); }
	bool sliderIsClicked(sf::Mouse::Button b) { return slider.isClicked(b); }
	bool sliderIsPressed(sf::Mouse::Button b) { return slider.isPressed(b); }
	bool sliderIsHold(sf::Mouse::Button b) { return slider.isHold(b); }
	void setSliderTexture(const sf::Texture *texture) { slider.setTexture(texture); }
	Slider<ScrollType::Vertical> getSlider() const { return slider; }
	Vec2f getValueSize() const { return esize; }
	Vec2u getValueCount() const { return n; } // returns vector2 where x is val count by width, y - by height
	size_t size() const { return elems->size(); }
	Vec2f getIndents() const { return ind; }
	Vec2f getOrigin() const { return origin; }
	Vec2f getPosition() const { return position; }
	Vec2f getSize() const { return ssize; }
	Vec2f getSliderSize() const { return slider.getSize(); }
	Vec2f getSliderPos() const { return slider.getPosition(); }
	sf::Color getSliderFillColor() const { return slider.getFillColor(); }
	sf::Color getSliderOutlineColor() const { return slider.getOutlineColor(); }
	float getSliderOutlineThickness() const { return slider.getOutlineThickness(); }
	sf::FloatRect getLocalBounds() const { return sf::FloatRect(Vec2f(), ssize); }
	sf::FloatRect getGlobalBounds() const { return sf::FloatRect(position - origin, Vec2f(ssize.x + slider.getSize().x, ssize.y)); }
	Scrollable<T, ScrollType::Vertical> &operator=(const Scrollable<T, ScrollType::Vertical> &sc)
	{
		position = sc.position;
		origin = sc.origin;
		ssize = sc.ssize;
		ind = sc.ind;
		slider = sc.slider;
		esize = sc.esize;
		n = sc.n;
		elems = sc.elems;
		return *this;
	}
private:
	void recount_slider()
	{
			const Vec2f sls = Vec2f(slider.getSize().x, powf(ssize.y, 2) / (n.y * (esize.y + ind.y))); // slider size
			slider.setSize(sls);
			slider.setPosition(position.x + n.x * (esize.x + ind.x), slider.getPosition().y);
			slider.setLimit(position.y, position.y + ssize.y);
	}
	void draw(sf::RenderTarget &win, sf::RenderStates st) const override
	{
		size_t i = 0;
		const float t = (slider.getPosition().y - position.y) / ssize.y;
		for (auto el : *elems)
		{
			const float x = static_cast<float>(i % n.x), y = floorf(static_cast<float>(i) / n.x);
			const float x1 = position.x + x * (esize.x + ind.x), y1 = position.y + (esize.y + ind.y) * (y - t * n.y);
			el->setPosition(x1, y1);
			win.draw(*el, st);
			i++;
		}
		if (slider.getSize().y < ssize.y) // excepting a way when slider height >= this height 
			win.draw(slider, st);
	}
};


// horizontal scroll class specialization 
template<class T>
class engine::Scrollable<T, engine::ScrollType::Horizontal> : public sf::Drawable
{
	Vec2f position;
	Vec2f origin;
	Vec2f ssize; // size
	Vec2f ind; // indents between elements
	Slider<engine::ScrollType::Horizontal> slider;
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
		slider = Slider<engine::ScrollType::Horizontal>(Vec2f(1, 30));
		setSize(count, length);
		Vec2f sls = slider.getSize();
	}
	Scrollable(const Scrollable<T> &sc)
	{
		*this = sc;
	}
	~Scrollable() override = default;
	void setOrigin(const Vec2f & or_)
	{
		origin = or_;
	}
	void setIndents(const Vec2f & inds)
	{
		ind = inds;
		recount_slider();
	}
	void setIndents(const float &x, const float &y)
	{
		setIndents(Vec2f(x, y));
	}
	void setSliderLength(const float &length)
	{
		slider.setSize(Vec2f(slider.getSize().x, length));
		slider.setLimit(position.x, position.x + ssize.x - slider.getSize().x);
	}

	void setSliderPos(const float &pos)
	{
		slider.setPosition(pos, slider.getPosition().y);
	}

	void setPosition(const Vec2f & p)
	{
		position = p;
		recount_slider();
	}

	void setPosition(const float &x, const float &y)
	{
		setPosition(Vec2f(x, y));
	}

	void setSize(unsigned int count, const float &length)
	{
		const size_t val_count = elems->size();
	
		n.y = count;
		n.x = static_cast<int>(ceil(val_count / n.y)) + 1;
		ssize.y = n.y * (esize.y + ind.y);
		ssize.x = length;

		recount_slider();
	}
	void push_back(const T & val)
	{
		elems->push_back(&val);
		n.x = static_cast<int>(ceil(elems->size() / n.y)) + 1;
		recount_slider();
	}
	bool sliderIsClicked(sf::Mouse::Button b, const Vec2f & p) { return slider.isClicked(b, p); }
	bool sliderIsPressed(sf::Mouse::Button b, const Vec2f & p) { return slider.isPressed(b, p); }
	bool sliderIsHold(sf::Mouse::Button b, const Vec2f & p) { return slider.isHold(b, p); }
	bool sliderIsClicked(sf::Mouse::Button b) { return slider.isClicked(b); }
	bool sliderIsPressed(sf::Mouse::Button b) { return slider.isPressed(b); }
	bool sliderIsHold(sf::Mouse::Button b) { return slider.isHold(b); }
	void setSliderTexture(const sf::Texture * texture) { slider.setTexture(texture); }
	Slider<ScrollType::Horizontal> getSlider() const { return slider; }
	Vec2f getValueSize() const { return esize; }
	size_t size() const { return elems->size(); }
	Vec2f getIndents() const { return ind; }
	Vec2f getOrigin() const { return origin; }
	Vec2f getPosition() const { return position; }
	Vec2f getSize() const { return ssize; }
	Vec2f getSliderSize() const { return slider.getSize(); }
	Vec2f getSliderPos() const { return slider.getPosition(); }
	sf::Color getSliderFillColor() const { return slider.getFillColor(); }
	sf::Color getSliderOutlineColor() const { return slider.getOutlineColor(); }
	float getSliderOutlineThickness() const { return slider.getOutlineThickness(); }
	sf::FloatRect getLocalBounds() const { return sf::FloatRect(Vec2f(), ssize); }
	sf::FloatRect getGlobalBounds() const { return sf::FloatRect(position - origin, Vec2f(ssize.x + slider.getSize().x, ssize.y)); }
	Scrollable<T, ScrollType::Horizontal> &operator=(const Scrollable<T, ScrollType::Horizontal> &sc)
	{
		position = sc.position;
		origin = sc.origin;
		ssize = sc.ssize;
		ind = sc.ind;
		slider = sc.slider;
		esize = sc.esize;
		n = sc.n;
		elems = sc.elems;
		return *this;
	}
private:
	void recount_slider()
	{
		const Vec2f sls = Vec2f(powf(ssize.x, 2) / (n.x * (esize.x + ind.x)), slider.getSize().y);
		slider.setSize(sls);
		slider.setPosition(slider.getPosition().x, position.y + n.y * (esize.y + ind.y));
		slider.setLimit(position.x, position.x + ssize.x - sls.x);
	}
	void draw(sf::RenderTarget & win, sf::RenderStates st) const override
	{
		size_t i = 0;
		const float t = (slider.getPosition().x - position.x) / ssize.x;
		for (auto el : *elems)
		{
			const float x = floorf(static_cast<float>(i) / n.y), // card id by width
				y = static_cast<float>(i % n.y); // card id by height
			const float x1 = position.x + (esize.x + ind.x) * (x - t * n.x), y1 = position.y + y * (esize.y + ind.y);
			el->setPosition(x1, y1);
			win.draw(*el, st);
			i++;
		}
		if (slider.getSize().x < ssize.x) // excepting a way when slider width >= this width
			win.draw(slider, st);
	}
};