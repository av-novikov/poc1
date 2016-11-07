#ifndef RADIALCELL_HPP_
#define RADIALCELL_HPP_

#include <iostream>

#include "src/grids/cells/AbstractCell.hpp"
#include "src/grids/variables/Coordinates.hpp"

namespace units
{
	using data::Point1d;

	template<typename TVariable, typename TDependentVariable = data::EmptyContainer>
	class RadialCell : public AbstractCell<Point1d, TVariable, TDependentVariable>
	{
	public:
		typedef AbstractCell<Point1d, TVariable, TDependentVariable> Base;
		using typename Base::Point;
		using typename Base::TPoint;
		using typename Base::Indexes;
		using typename Base::Variable;
		using typename Base::DependentVariable;

		using Base::num;
		using Base::coords;
		using Base::sizes;
		using Base::faces_up;
		using Base::faces_down;
		using Base::V;
		using Base::dim;
	public:
		RadialCell() {};

		RadialCell(int _num, Scalar _r, Scalar _hr, Scalar _hz)
		{
			num = _num;
			coords.r = _r;
			sizes.r = _hr;
			faces_up.r = 2.0 * M_PI * (_r + _hr / 2.0) * _hz;
			faces_down.r = 2.0 * M_PI * (_r - _hr / 2.0) * _hz;
			V = 2.0 * M_PI * coords.r * sizes.r * _hz;
		};

		RadialCell(const RadialCell& cell) = default;
		~RadialCell() {};

		RadialCell& operator=(const RadialCell& cell) = default;
	};
};

#endif /* RADIALCELL_HPP_ */
