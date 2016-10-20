#ifndef ABSTRACTGRID_HPP_
#define	ABSTRACTGRID_HPP_

#include "src/snapshot/AbstractSnapshotter.hpp"
#include "src/grids/variables/Variables.hpp"

namespace grids
{
	using data::Scalar;
	using data::uint;

	template <class CellType>
	class AbstractGrid
	{
	public:
		typedef CellType Cell;
		typedef typename Cell::Variable Variable;
		typedef typename Cell::DependentVariable DependentVariable;
	protected:
		uint totalSize;
		data::CylindricalSize sizes;
		data::CylindricalSize sizes_ghost;
		
		Scalar Volume;
		AbstractSnapshotter snapshotter;

	public:
		AbstractGrid() 
		{
			totalSize = 0;
			sizes = sizes_ghost = {0, 0, 0};
		};
		virtual ~AbstractGrid() {};

		virtual void snapshot(uint i) const = 0;
	};
};

#endif /* ABSTRACTGRID_HPP_ */