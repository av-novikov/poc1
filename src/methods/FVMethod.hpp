#ifndef FVMETHOD_HPP_
#define FVMETHOD_HPP_

#include "src/methods/AbstractMethod.hpp"

template <class ModelType>
class FVMethod : public AbstractMethod<ModelType>
{
public:
	typedef AbstractMethod<ModelType> Base;
	using typename Base::Model;
	using typename Model::Flux;
	using typename Base::Grid;
	using typename Base::Variable;
	using typename Base::DependentVariable;
	using typename Base::Cell;
	using typename Base::Point;

public:
};

#endif /* FVMETHOD_HPP_ */
