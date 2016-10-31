#ifndef ITERATOR_HPP_
#define ITERATOR_HPP_

#include "src/grids/variables/Matrix.hpp"

namespace grids
{

	template <class gridType>
	struct BasicIterator : public gridType::Indexes
	{
	public:
		typedef typename gridType::Cell Cell;
		typedef typename gridType::Indexes Indexes;
	private:
		Cell* ptr;

		void increment(const uint axis)
		{
			this->values[axis] = (this->values[axis] + 1 - left.values[axis]) %
				(right.values[axis] - left.values[axis]) + left.values[axis];
			if (this->values[axis] == left.values[axis])
				if(axis > 0)
					increment(axis-1);
				else
					ptr = nullptr;
		};

	protected:
		Indexes left, right, sizes;
	public:
		BasicIterator()
		{
			ptr = nullptr;
		};

		BasicIterator(const BasicIterator& it) = default;
		BasicIterator(Cell* _ptr, Indexes _left, Indexes _right, Indexes _sizes):
						ptr(_ptr), left(_left), right(_right), sizes(_sizes) 
		{
			if (ptr != nullptr)
			{
				switch (Cell::dim)
				{
				case 1:
					this->values[0] = ptr->num;
				}
			}
		};
		~BasicIterator() {};

		BasicIterator& operator++()
		{
			increment(Cell::dim - 1);

			if(ptr != nullptr)
				ptr += (getIdx() - ptr->num);

			return (*this);
		}

		BasicIterator& operator=(const BasicIterator& rhs)
		{
			ptr = rhs.ptr;

			Indexes::operator=(rhs);
			left = rhs.left;
			right = rhs.right;
			sizes = rhs.sizes;

			return (*this);
		};

		bool operator==(const BasicIterator& rhs)
		{
			return ptr == rhs.ptr;
		};

		bool operator!=(const BasicIterator& rhs)
		{
			return ptr != rhs.ptr;
		};

		Cell* operator->() const
		{
			return ptr;
		};

		int getIdx() const
		{
			switch (Cell::dim)
			{
			case 1:
				return	this->values[0];
			case 2:
				return	this->values[0] * sizes.values[1] +
						this->values[1];
			case 3:
				return 	this->values[0] * sizes.values[1] * sizes.values[2] +
						this->values[1] * sizes.values[2] +
						this->values[2];
			}
		};

		Cell* getPtr() const
		{
			return ptr;
		};
	};

	template <class gridType>
	inline bool operator!=(const BasicIterator<gridType>& it, const std::nullptr_t null)
	{
		return it.getPtr() != null;
	}

	template <class gridType>
	inline bool operator==(const BasicIterator<gridType>& it, const std::nullptr_t null)
	{
		return it.getPtr() == null;
	}

	template <class gridType>
	inline std::ostream& operator<<(std::ostream& os, const BasicIterator<gridType>& it)
	{
		os << it->num << std::endl;
		return os;
	};
};

#endif /* ITERATOR_HPP_ */
