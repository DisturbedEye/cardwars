#pragma once

namespace engine
{
	struct random
	{
	private:
		// plz don't use 'std::srand()'
		std::random_device rd;
		std::mt19937 generator = std::mt19937(rd());
	public:
		random() {}
		template<class T>
		T real(const T &min, const T &max); // returns random real number from min to max 
		template<class T>
		T integer(const T &min, const T &max); // returns random integer from min to max
		bool chance(const float &x); // x belongs to interval from 0.0 to 1.0, for example if x = 0.01f then it have 1% chance to return true
		template<class First, class Last>
		void shuffle(const First &begin, const Last &end); // shuffling
	};
	template<class T>
	T random::real(const T &min, const T &max)
	{
		std::uniform_real_distribution dist(min, max);
		return dist(generator);
	}
	template<class T>
	T random::integer(const T &min, const T &max)
	{
		std::uniform_int_distribution dist(min, max);
		return dist(generator);
	}
	inline bool random::chance(const float &x)
	{
		return real(0.f, 1.f) < x;
	}
	template <class First, class Last>
	void random::shuffle(const First &begin, const Last &end)
	{
		std::shuffle(begin, end, generator);
	}
}