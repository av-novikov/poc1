#ifndef RADIALGRID_HPP_
#define	RADIALGRID_HPP_

#include "src/grids/cells/RadialCell.hpp"
#include "src/grids/AbstractGrid.hpp"
#include "src/grids/Iterator.hpp"

#include <vector>

/** 
 Implementation of simple radial 1D grid
 */
namespace grids
{
	template<typename TVariable, typename TDependentVariable = data::EmptyContainer>
	class RadialGrid : public AbstractGrid<units::RadialCell<TVariable, TDependentVariable> >
	{
	public:
		typedef AbstractGrid<units::RadialCell<TVariable, TDependentVariable> > Base;
		typedef BasicIterator<RadialGrid> Iterator;
		using typename Base::Cell;
		using typename Base::Variable;
		using typename Base::DependentVariable;
		using typename Base::Indexes;

		struct Geometry
		{
			Scalar r_w;
			Scalar r_e;
			Scalar hz;
			uint size;
			uint size_ghost;
		};

		Geometry geom;

	protected:
		using Base::totalSize;
		using Base::sizes;
		using Base::sizes_ghost;
		using Base::Volume;

	// All cells
	public:
		std::vector<Cell> cells;

	// All iterators
	public:
		inline Iterator getIterator()
		{
			return Iterator(&cells[0], {geom.size_ghost, 0, 0},
										{totalSize - geom.size_ghost, 0, 0},
											sizes);
		};
		//static Iterator getIterator_ghost();

	public:
		RadialGrid() : Base() {};
		RadialGrid(const Geometry& _geom)
		{
			load(_geom);
		};
		~RadialGrid() {};

		void load(const Geometry& _geom)
		{
			geom = _geom;
			totalSize = geom.size + 2 * geom.size_ghost;
			sizes = { geom.size, 1, 1 };
			sizes_ghost = { totalSize, 1, 1 };

			cells.reserve(totalSize);
			Volume = 0.0;
			uint counter = 0;
			
			double r_prev = geom.r_w;
			double logMax = log(geom.r_e / geom.r_w);
			double logStep = logMax / (double)(sizes.r);
			double hr = r_prev * (exp(logStep) - 1.0);
			double cm = geom.r_w - ((double)(geom.size_ghost) - 0.5) * hr;

			for (uint i = 0; i < geom.size_ghost; i++)
			{
				cells.push_back( Cell(counter++, cm, hr, geom.hz) );
				cm += hr;
			}
			for (uint i = 0; i < geom.size; i++)
			{
				cm = r_prev * (1.0 + exp(logStep)) / 2.0;
				hr = r_prev * (exp(logStep) - 1.0);
				cells.push_back(Cell(counter++, cm, hr, geom.hz));

				Volume += cells[cells.size() - 1].V;
				r_prev = r_prev * exp(logStep);
			}
			for (uint i = 0; i < geom.size_ghost; i++)
			{
				cm += hr;
				cells.push_back(Cell(counter++, cm, hr, geom.hz));
			}
		};
		void snapshot(const uint i) const
		{};

	};
};

#endif /* RADIALGRID_HPP_ */
