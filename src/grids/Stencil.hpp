#ifndef STENCIL_HPP_
#define STENCIL_HPP_

namespace grids
{
template <typename Iterator, int N = 3>
class BaseStencil
{
public:
	static const int size;
	Iterator iter [N];
	Iterator& cur;

	void initialize(const Iterator& it)
	{
		int j = 0;
		for(int i = -(N-1)/2; i < (N+1)/2; i++)
			iter[j++] = it + i;

		cur = iter[(N - 1) / 2];
	};

	Iterator& operator++()
	{
		for(int i = 0; i < N; i++)
			++iter[i];

		return *this;
	}
};

template <typename Iterator, int N>
const int BaseStencil<Iterator, N>::size = N;

};

#endif /* STENCIL_HPP_ */
