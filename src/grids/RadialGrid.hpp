#ifndef RADIALGRID_HPP_
#define	RADIALGRID_HPP_

#include "src/grids/cells/AbstractCell.hpp"
#include "src/grids/AbstractGrid.hpp"

#include <vector>

/** 
 Implementation of simple radial 1D grid
 */
namespace grids
{
	template <class CellType>
	class RadialGrid : public AbstractGrid<CellType>
	{
	public:
		struct Geometry
		{
			Scalar r_w;
			Scalar r_e;
			Scalar hz;
			uint size;
		};
	protected:
		std::vector<CellType> cells;
	public:

		void load(const Geometry& geom)
		{

		};
		void snapshot(uint i) const
		{ };

	};
};

#endif /* RADIALGRID_HPP_ */
