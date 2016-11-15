#ifndef FVMETHOD_HPP_
#define FVMETHOD_HPP_

#include <fstream>

#include "src/methods/AbstractMethod.hpp"
#include "src/solvers/block_diagonal/sweep.h"

namespace methods
{
	template <class ModelType>
	class FVMethod : public AbstractMethod<ModelType>, public Sweep
	{
	public:
		typedef AbstractMethod<ModelType> Base;
		using typename Base::Model;
		using typename Model::Flux;
		using typename Base::Grid;
		using typename Base::Iterator;
		using typename Base::Stencil;
		using typename Base::Variable;
		using typename Base::Jacobian;
		using typename Base::Deviation;
		using typename Base::DependentVariable;
		using typename Base::Cell;
		using typename Base::Point;
	private:
		void MiddleAppr(int current, int MZ, int key)
		{
			for (int i = 0; i < MZ; i++)
			{
				for (int j = 0; j < MZ; j++)
				{
					A[i][j] = 0.0;
					B[i][j] = 0.0;
					C[i][j] = 0.0;
				}
				RightSide[i][0] = 0.0;
			}

			Stencil stencil;
			model->setStencil(&stencil);
			auto const it = grid->getInnerIter();
			stencil.initialize(it.begin());



			RightSide[]

			construction_bz(MZ, 2);
		};
		void LeftBoundAppr(int MZ, int key);
		void RightBoundAppr(int MZ, int key);

	protected:
		using Base::model;
		using Base::grid;
		using Base::ht;
		using Base::H;
		using Base::dx;
		using Base::jacob;

		void construction_from_fz(int N, int n, int key)
		{
			int i = 0;
			for (auto cell : grid->getIter())
				for (int j = 0; j < Variable::size; j++)
					cell.u_next.values[j] += fz[i++][j+1];
		};
		void writeData();
		std::ofstream wellbore_pres;

		inline void calcH(const Iterator& it)
		{
			Variable H;
			H = model->getU(*it) - model->getU_prev(*it);

			for( auto const& beta: grid->getNeighbours(it) )
				H += ht / it->Volume * grid->getCommonSquare(*it, *beta) * getF_among(*it, *beta);

			H += ht * model->getQ(*it);

			return H;
		};
		inline void calcJacobian(const Iterator& it) const
		{

		};

		void doNextStep()
		{
			Stencil stencil;
			model->setStencil(&stencil);
			auto const it = grid->getInnerIter();
			stencil.initialize( it.begin() );

			for (auto const iter = it.begin(); iter != it.end(); ++iter)
			{
				calcH(it);	calcJacobian(it);


				++stencil;
			};
		};

	public:
		FVMethod()
		{
			Initialize(model->totalSize, Variable::size);
			wellbore_pres.open("snaps/P_dyn.dat", std::ofstream::out);
		};
		~FVMethod()
		{
			wellbore_pres.close();
		};
	};
};

#endif /* FVMETHOD_HPP_ */
