#pragma once

namespace engine
{
	namespace algorithm
	{
		template<class T>
		bool in(const T &value, const std::vector<T> &values)
		{
			return std::find(values.begin(), values.end(), value) != values.end();
		}
	}
}