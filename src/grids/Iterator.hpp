#ifndef ITERATOR_HPP_
#define ITERATOR_HPP_

#include "src/grids/variables/Matrix.hpp"

namespace grids
{

	template <class cellType>
	struct Iterator : public data::Vector<cellType::dim, cellType::Point::Base>
	{
	public:
		typedef data::Vector<cellType::dim, cellType::Point::Base> VectorInt;
	private:
		cellType* ptr;
	protected:
		VectorInt left, right, sizes;
	public:
		Iterator()
		{
			ptr = nullptr;
		};

		Iterator(const Iterator& it) = default;
		Iterator(cellType* _ptr, VectorInt _left, VectorInt _right, VectorInt _sizes);
		~Iterator() {};

		Iterator& operator++();

		Iterator& operator=(const Iterator& rhs)
		{
			ptr = rhs.ptr;

			VectorInt::operator=(rhs);
			left = rhs.left;
			right = rhs.right;
			sizes = rhs.sizes;

			return (*this);
		};

		bool operator==(const Iterator& rhs)
		{
			return ptr == rhs.ptr;
		};

		bool operator!=(const Iterator& rhs)
		{
			return ptr != rhs.ptr;
		};

		cellType* operator->() const
		{
			return ptr;
		};

		int getIdx() const;
	};

	template <class cellType>
	Iterator<cellType>::Iterator(cellType* _ptr, VectorInt _left, VectorInt _right, VectorInt _sizes) :
				ptr(_ptr), left(_left), right(_right), sizes(_sizes)
	{
	};

	template <class cellType>
	inline Iterator& Iterator<cellType>::operator++()
	{
	};

	template <class cellType>
	inline int Iterator<cellType>::getIdx() const
	{

	};

	template <class cellType>
	inline std::ostream& operator<<(std::ostream& os, const Iterator<cellType>& it)
	{
		os << it << std::endl;
		return os;
	};

};

#endif /* ITERATOR_HPP_ */
