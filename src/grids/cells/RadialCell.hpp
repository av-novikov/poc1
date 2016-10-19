#ifndef RADIALCELL_HPP_
#define RADIALCELL_HPP_

#include "src/grids/cells/AbstractCell.hpp"
#include "src/grids/variables/Coordinates.hpp"

namespace units
{
	using data::Point1d;

	template<typename Variable, typename DependentVariable = data::EmptyContainer>
	class RadialCell : public AbstractCell<Point1d, Variable, DependentVariable>
	{
	public:
		typedef AbstractCell<Point1d, Variable, DependentVariable> Base;
	public:
		RadialCell() {};

		RadialCell(int _num, Scalar _r, Scalar _hr, Scalar _hz) : Base(_num)
		{
			this->coords.r = _r;
			this->sizes.r = _hr;
			this->V = 2.0 * M_PI * this->coords.r * this->sizes.r * _hz;
		};

		RadialCell(const RadialCell& cell) : Base(cell)
		{
		};

		~RadialCell() {};

		RadialCell& operator=(const RadialCell& cell)
		{
			Base::operator=(cell);
		};
	};
};

#endif /* RADIALCELL_HPP_ */
