#ifndef ABSTRACTMETHOD_HPP_
#define ABSTRACTMETHOD_HPP_

#include <cassert>

namespace methods
{
	template<class ModelType>
	class AbstractMethod
	{
	public:
		typedef ModelType Model;
		typedef typename Model::Grid Grid;
		using typename Grid::Variable;
		using typename Grid::DependentVariable;
		using typename Grid::Cell;
		using typename Grid::Iterator;
		using typename Grid::Stencil;
		using typename Cell::Point;
		typedef data::Matrix<Variable::size, Variable::size * Stencil::size> Jacobian;
		typedef data::Vector<Variable::size * Stencil::size> Deviation;

	protected:
		Grid* grid;
		Model* model;

		Scalar ht;

		Variable H;
		Deviation dx;
		Jacobian jacob;
	};
};

#endif /* ABSTRACTMETHOD_HPP_ */
