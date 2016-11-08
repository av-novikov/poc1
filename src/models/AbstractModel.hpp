#ifndef ABSTRACTMODEL_HPP_
#define ABSTRACTMODEL_HPP_

#include <new>
#include <string>
#include <cassert>

#include "src/snapshot/VTKSnapshotter.hpp"

namespace models
{
	typedef data::uint uint;
	typedef data::Scalar Scalar;

	template<class gridType>
	class AbstractModel
	{
	public:
		typedef gridType Grid;
		typedef typename Grid::Variable Variable;
		typedef	typename Grid::DependentVariable DependentVariable;
		typedef typename Grid::Cell Cell;
		typedef typename Cell::Point Point;
		template<typename DataType> using TPoint = typename Cell::template TPoint<DataType>;
		typedef typename data::Flux<Variable, TPoint> Flux;
		typedef typename Grid::Iterator Iterator;
		typedef typename Grid::RangeIterator RangeIterator;

		std::string id;
	protected:
		Grid* grid;
		AbstractSnapshotter<Grid>* snapshotter;

	public:
		AbstractModel()
		{
			id = "abstract";
			grid = nullptr;
			snapshotter = nullptr;
		};

		inline void setSnapshotter(const bool isVTK)
		{
			if(isVTK)
				snapshotter = new VTKSnapshotter<Grid>;

			snapshotter->setGrid(grid);
		};

		inline void loadGrid(const typename Grid::Geometry& geom)
		{
			grid = new Grid;
			grid->load(geom);

			if(snapshotter != nullptr)
				snapshotter->setGrid(grid);
		};
		inline void snapshot(uint i)
		{
			assert(snapshotter != nullptr);
			assert(grid != nullptr);

			snapshotter->dump(i);
		};

		//virtual Variable& getU(const Cell& cell) const = 0;
		//virtual Flux& getF(const Cell& cell) const = 0;
		//virtual  Variable& getQ(const Cell& cell) const = 0;
	};
};

#endif /* ABSTRACTMODEL_HPP_ */
