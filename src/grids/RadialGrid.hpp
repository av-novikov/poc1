#ifndef RADIALGRID_HPP_
#define	RADIALGRID_HPP_

#include "src/grids/cells/RadialCell.hpp"
#include "src/grids/AbstractGrid.hpp"
#include "src/grids/Iterator.hpp"
#include "src/utils/utils.hpp"

#include <vtkXMLPolyDataWriter.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>

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
		using typename Base::Cell;
		using typename Base::Point;
		using typename Base::TPoint;
		using typename Base::Variable;
		using typename Base::DependentVariable;
		using typename Base::Indexes;
		typedef typename std::vector<Cell>::iterator Iterator;
		typedef Range<Iterator> RangeIterator;
		typedef vtkSmartPointer<vtkPolyData> VtkGridPtr;
		typedef vtkSmartPointer<vtkXMLPolyDataWriter> VtkWriterPtr;
		typedef struct 
		{
			Scalar r_w;
			Scalar r_e;
			Scalar hz;
			uint size;
			uint size_ghost;
		} Geometry;
		Geometry geom;

		Indexes left;
		Indexes right;

	protected:
		using Base::totalSize;
		using Base::Volume;
		using Base::cells;

	// All iterators
	public:
		inline RangeIterator getInnerIter()
		{
			return make_range(cells, left.r, right.r);
		};
		inline RangeIterator getPointIter()
		{
			return make_range(cells, left.r, right.r + 1);
		};
		inline RangeIterator getIter()
		{
			return make_range(cells, 0, totalSize);
		};
		inline std::initializer_list<Iterator> getNeighbours(const Iterator& it)
		{
			if (it == cells.begin())
				return { it + 1 };
			else if (it == cells.end() - 1)
				return { it - 2 };
			else
				return { it - 1, it + 1 };
		};
		inline std::initializer_list<Iterator> getNeighboursPlus(const Iterator& it)
		{
			if (it == cells.begin())
				return { it, it + 1 };
			else if (it == cells.end() - 1)
				return { it - 2, it - 1 };
			else
				return { it - 1, it, it + 1 };
		};
		inline Scalar getCommonSquare(const Cell& cell1, const Cell& cell2) const
		{
			return 2.0 * M_PI * (cell1.r + sign(cell2.num - cell1.num) * cell1.hr / 2.0) * geom.hz;
		};
		
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
			left = { geom.size_ghost };
			right = { totalSize - geom.size_ghost };

			cells.reserve(totalSize);
			Volume = 0.0;
			uint counter = 0;
			
			double r_prev = geom.r_w;
			double logMax = log(geom.r_e / geom.r_w);
			double logStep = logMax / (double)(geom.size);
			double hr = r_prev * (exp(logStep) - 1.0);
			double cm = geom.r_w - ((double)(geom.size_ghost) - 0.5) * hr;

			for (uint i = 0; i < geom.size_ghost; i++)
			{
				cells.emplace_back( counter++, cm, hr, geom.hz );
				cm += hr;
			}
			for (uint i = 0; i < geom.size; i++)
			{
				cm = r_prev * (1.0 + exp(logStep)) / 2.0;
				hr = r_prev * (exp(logStep) - 1.0);
				cells.emplace_back( counter++, cm, hr, geom.hz );

				Volume += cells[cells.size() - 1].V;
				r_prev = r_prev * exp(logStep);
			}
			for (uint i = 0; i < geom.size_ghost; i++)
			{
				cm += hr;
				cells.emplace_back( counter++, cm, hr, geom.hz );
			}
		};
	};
};

#endif /* RADIALGRID_HPP_ */
