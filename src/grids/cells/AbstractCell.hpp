#ifndef ABSTRACTCELL_HPP_
#define ABSTRACTCELL_HPP_

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

#include "src/grids/variables/Variables.hpp"

namespace units {
	using data::uint;
	using data::Scalar;
/**
 Basic type of cell as an element of any hand-made grid

 @tparam Variable Type of container that has vector of variables
 @tparam DependentVariable Type of container that has all dependent variables which need to be stored
 */
	template<typename PointType,
	typename TVariable, typename TDependentVariable = data::EmptyContainer>
	class AbstractCell
	{
	public:
		typedef PointType Point;
		typedef TVariable Variable;
		typedef TDependentVariable DependentVariable;
	public:
		// Geometry dimension of cell
		static const uint dim;
		// Center of cell
		PointType coords;
		// Cell sizes;
		PointType sizes;

		// Number of cell in grid
		int num;
		// Volume of cell
		Scalar V;

		// Vectors of variables for temporary discretization
		TVariable u_next, u_iter, u_prev;
		// Vectors of dependent variables for temporary discretization
		TDependentVariable d_next, d_iter, d_prev;

		AbstractCell() : num(-1), V(0.0) {};
		AbstractCell(int _num) : num(_num) {};
		AbstractCell(const AbstractCell& cell)
		{
			u_next = cell.u_next;	u_iter = cell.u_iter;	u_prev = cell.u_prev;
			d_next = cell.d_next;	d_iter = cell.d_iter;	d_prev = cell.d_prev;
			V = cell.V;
		};
		~AbstractCell() {};

		AbstractCell& operator=(const AbstractCell& cell)
		{
			u_next = cell.u_next;	u_iter = cell.u_iter;	u_prev = cell.u_prev;
			d_next = cell.d_next;	d_iter = cell.d_iter;	d_prev = cell.d_prev;
			V = cell.V;
		};
	};

	template<typename PointType,
	typename TVariable, typename TDependentVariable>
	const uint AbstractCell<PointType, TVariable, TDependentVariable>::dim = PointType::size;
};



#endif /* ABSTRACTCELL_HPP_ */
