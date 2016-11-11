#ifndef ITERATOR_HPP_
#define ITERATOR_HPP_

namespace grids
{
	template <class Iter>
	class Range
	{
	private:
		Iter b;
		Iter e;
	public:
		Range(Iter _b, Iter _e) : b(_b), e(_e) {};

		Iter begin()	{ return b; };
		Iter end()		{ return e; };
	};

	template <class Container>
	Range<typename Container::iterator>
		make_range(Container& c, size_t b, size_t e)
	{
		return Range<typename Container::iterator>(c.begin() + b, c.begin() + e);
	};
};

#endif /* ITERATOR_HPP_ */
