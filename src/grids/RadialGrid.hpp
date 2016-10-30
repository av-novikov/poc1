#ifndef RADIALGRID_HPP_
#define	RADIALGRID_HPP_

#include <vtkSmartPointer.h>
#include <vtkPolyData.h>

#include <vector>

#include "src/grids/cells/AbstractCell.hpp"
#include "src/grids/AbstractGrid.hpp"

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
	public:

		void load(const Geometry& geom)
		{

		};
		void snapshot(uint i) const
		{ };
	};
};

#endif /* RADIALGRID_HPP_ */
