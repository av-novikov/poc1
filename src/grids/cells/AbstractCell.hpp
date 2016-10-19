#ifndef ABSTRACTCELL_HPP_
#define ABSTRACTCELL_HPP_

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

#include "src/grids/variables/Variables.hpp"

namespace unit {
	using data::uint;
	using data::Scalar;

/**
 Basic type of cell as an element of any hand-made grid

 @tparam Variable Type of container that has vector of variables
 @tparam DependentVariable Type of container that has all dependent variables which need to be stored
 */
	template<typename Variable, typename DependentVariable = data::EmptyContainer>
	class AbstractCell 
	{
	public:
		typedef Variable Variable;
		typedef DependentVariable DependentVariable;
	public:
		// Number of cell in grid
		int num;
		// Volume of cell
		Scalar V;

		// Vectors of variables for temporary discretization
		Variable u_next, u_iter, u_prev;
		// Vectors of dependent variables for temporary discretization
		DependentVariable d_next, d_iter, d_prev;

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
};

#endif /* ABSTRACTCELL_HPP_ */
