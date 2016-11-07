#ifndef ABSTRACTMETHOD_HPP_
#define ABSTRACTMETHOD_HPP_

#include <cassert>

template<class ModelType>
class AbstractMethod
{
public:
	typedef ModelType Model;
	typedef typename Model::Grid Grid;
	typedef	typename Grid::DependentVariable DependentVariable;
	typedef typename Grid::Cell Cell;
	typedef typename Cell::Point Point;
protected:
	Grid* grid;
};

#endif /* ABSTRACTMETHOD_HPP_ */