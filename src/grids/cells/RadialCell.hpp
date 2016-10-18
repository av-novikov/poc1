#ifndef RADIALCELL_HPP_
#define RADIALCELL_HPP_

#include "src/grids/cells/AbstractCell.hpp"

namespace unit
{
	template<typename Variable, typename DependentVariable = data::EmptyContainer>
	class RadialCell : public AbstractCell<Variable, DependentVariable>
	{
	public:
		Scalar r;
		Scalar hr;

		RadialCell() {};

		RadialCell(int _num, Scalar _r, Scalar _hr, Scalar _hz) :
				AbstractCell<Variable, DependentVariable>(_num),
				r(_r), hr(_hr)
		{
			this->V = 2.0 * M_PI * r * hr * _hz;
		};

		RadialCell(const RadialCell& cell) : AbstractCell<Variable, DependentVariable>(cell)
		{
			r = cell.r;	hr = cell.hr;
		};

		~RadialCell() {};

		RadialCell& operator=(const RadialCell& cell)
		{
			AbstractCell<Variable, DependentVariable>::operator=(cell);
			r = cell.r;	hr = cell.hr;
		};
	};

};

#endif /* RADIALCELL_HPP_ */
