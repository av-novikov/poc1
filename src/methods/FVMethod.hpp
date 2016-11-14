#ifndef FVMETHOD_HPP_
#define FVMETHOD_HPP_

#include "src/methods/AbstractMethod.hpp"

namespace methods
{
	template <class ModelType>
	class FVMethod : public AbstractMethod<ModelType>
	{
	public:
		typedef AbstractMethod<ModelType> Base;
		using typename Base::Model;
		using typename Model::Flux;
		using typename Base::Grid;
		using typename Grid::Iterator;
		using typename Base::Variable;
		using typename Base::DependentVariable;
		using typename Base::Cell;
		using typename Base::Point;
	protected:
		using Base::model;
		using Base::grid;
		using Base::ht;

		Variable& getH(const Iterator& it) const
		{
			Variable H;
			H = model->getU(*it) - model->getU_prev(*it);

			for( auto const& beta: grid->getNeighbours(it) )
				H += ht / it->Volume * grid->getCommonSquare(*it, *beta) * getF_among(*it, *beta);

			H += ht * model->getQ(*it);

			return H;
		};
		/*Variable& getJacobian(const Iterator& it) const
		{

		};*/

	};
};

#endif /* FVMETHOD_HPP_ */
