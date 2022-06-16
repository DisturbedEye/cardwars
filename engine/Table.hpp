#pragma once


namespace engine
{
	class Table : public sf::Drawable, public sf::Transformable, std::vector<std::vector<sf::FloatRect>>
	{
	public:
		Table(const size_t &x, const size_t &y, Vec2f sample) : std::vector<std::vector<sf::FloatRect>>(x, std::vector(y, sf::FloatRect()))
		{
			setCellsSize(sample);
		}
		Table(const size_t &width, const size_t &height) : std::vector<std::vector<sf::FloatRect>>(width, std::vector(height, sf::FloatRect())) {}
		Table() = default;
		auto line(const size_t &) const;
		auto lines() const;
		auto column(const size_t &) const;
		size_t getColumnCount() const { return size(); }
		size_t getLineCount() const { return begin()->size(); }
		void setColumnWidth(const size_t &, const float &);
		void setLineHeight(const size_t &, const float &);
		void setCellsSize(const Vec2f &);
		void setSize(const Vec2f &);
		Vec2f getSize() const;
		Vec2f getCellPosition(const size_t &x, const size_t &y) const;
		Vec2f getCellSize(const size_t &x, const size_t &y) const;
		sf::FloatRect getColumnRect(const size_t &) const; // returns a FloatRect of current column
		sf::FloatRect getLineRect(const size_t &) const; // returns a FloatRect of current line 
		sf::FloatRect getCellRect(const size_t &, const size_t &) const; // return a FloatRect of cell
		sf::FloatRect getGlobalBounds() const { return {getPosition(), getSize()}; }
		sf::FloatRect getLocalBounds() const { return {Vec2f(), getSize()}; }
	private:
		void setCellSize(const size_t &x, const size_t &y, const Vec2f &);
		using std::vector<std::vector<sf::FloatRect>>::at;
		const sf::FloatRect &at(const size_t &, const size_t &) const;
		sf::FloatRect &at(const size_t &, const size_t &);
		void recount();
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	};
	inline auto Table::line(const size_t &y) const
	{
		std::vector<sf::FloatRect> line;
		for(size_t x = 0; x < size(); x++)
			line.push_back(at(x).at(y));
		return line;
	}
	inline auto Table::lines() const
	{
		std::vector<std::vector<sf::FloatRect>> lines;
		for(size_t i = 0; i < begin()->size(); i++)
			lines.push_back(line(i));
		return lines;
	}
	inline auto Table::column(const size_t &x) const
	{
		return at(x);
	}
	inline void Table::setCellSize(const size_t& x, const size_t& y, const Vec2f &size)
	{
		sf::FloatRect &cell = at(x, y);
		cell = sf::FloatRect(cell.left, cell.top, size.x, size.y);
	}
	inline void Table::setSize(const Vec2f &size)
	{
		Vec2f cell_size = {size.x/static_cast<float>(getColumnCount()), size.y/static_cast<float>(getLineCount())};
		setCellsSize(cell_size);
	}
	inline Vec2f Table::getCellPosition(const size_t &x, const size_t &y) const
	{
		auto cell = getCellRect(x, y);
		return {cell.left, cell.top};
	}
	inline Vec2f Table::getCellSize(const size_t &x, const size_t &y) const
	{
		auto cell = getCellRect(x, y);
		return { cell.width, cell.height };
	}



	inline void Table::setColumnWidth(const size_t &x, const float &width)
	{
		for (size_t i = 0; i < begin()->size(); i++)
			setCellSize(x, i, Vec2f(width, at(x, i).height));
		recount();
	}
	inline void Table::setLineHeight(const size_t &y, const float &height)
	{
		for (size_t i = 0; i < begin()->size(); i++)
			setCellSize(i, y, Vec2f(at(i, y).width, height));
		recount();
	}

	inline const sf::FloatRect &Table::at(const size_t &x, const size_t &y) const
	{
		return at(x).at(y);
	}
	inline sf::FloatRect &Table::at(const size_t &x, const size_t &y)
	{
		return at(x).at(y);
	}
	inline void Table::setCellsSize(const Vec2f &sample)
	{
		Vec2f position;
		for(auto &column : *this)
		{
			for(auto &cell : column)
			{
				cell = sf::FloatRect(position.x, position.y, sample.x, sample.y);
				position.y += sample.y;
			}
			position.y = 0;
			position.x += sample.x;
		}
	}
	inline Vec2f Table::getSize() const
	{
		Vec2f ss; // size
		for (auto x = begin(); x != end(); ++x)
			ss.x += x->begin()->width;
		for (auto y = begin()->begin(); y != begin()->end(); ++y)
			ss.y += y->height;
		return ss;
	}
	inline sf::FloatRect Table::getColumnRect(const size_t &x) const
	{
		sf::FloatRect box;
		box.width = std::max(at(x).begin(), at(x).end())->width;
		box.left = getPosition().x + at(x).begin()->left;
		box.top = getPosition().y + at(x).begin()->top;
		for (auto &cell : at(x))
			box.height += cell.height;
		return box;
	}
	inline sf::FloatRect Table::getLineRect(const size_t &y) const
	{
		sf::FloatRect box;
		auto line = this->line(y);
		box.height = std::max(line.begin(), line.end())->height;
		box.left = getPosition().x + begin()->at(y).left;
		box.top = getPosition().y + begin()->at(y).top;
		for(auto &cell : line)
			box.width += cell.width;
		return box;
	}
	inline sf::FloatRect Table::getCellRect(const size_t &x, const size_t &y) const
	{
		sf::FloatRect box = at(x).at(y);
		box.left += getPosition().x;
		box.top += getPosition().y;
		return box;
	}
	inline void Table::recount()
	{
		
		for(auto &column : *this)
		{
			float pos_y = 0;
			for (auto &cell : column)
			{
				cell.top = pos_y;
				pos_y += cell.height;
			}
			pos_y = 0;
		}
		
		for (size_t y = 0; y < begin()->size(); y++)
		{
			float pos_x = 0;
			for(size_t x = 0; x < size(); x++)
			{
				auto &cell = at(x, y);
				cell.left = pos_x;
				pos_x += cell.width;
			}
		}
	}
	inline void Table::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		sf::VertexArray borders(sf::Lines, 2);
		for (auto &column : *this)
		{
			const bool is_last_column = &column == &*--end();
			for (auto cell = column.begin(); cell != column.end(); ++cell)
			{
				borders[0].position = Vec2f{cell->left, cell->top};
				borders[1].position = borders[0].position + Vec2f{cell->width, 0};
				target.draw(borders, states);
				borders[1].position = borders[0].position + Vec2f{ 0, cell->height };
				target.draw(borders, states);
				if (is_last_column)
				{
					borders[0].position = Vec2f(cell->left + cell->width, cell->top);
					borders[1].position = Vec2f(cell->left + cell->width, cell->top + cell->height);
					target.draw(borders, states);
				}
				if (cell == --column.end())
				{
					borders[0].position = Vec2f(cell->left, cell->top + cell->height);
					borders[1].position = Vec2f(cell->left + cell->width, cell->top + cell->height);
					target.draw(borders, states);
				}
			}
		}

	}

}