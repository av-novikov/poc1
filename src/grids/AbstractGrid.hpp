#ifndef ABSTRACTGRID_HPP_
#define	ABSTRACTGRID_HPP_

#include "src/snapshot/VTKSnapshotter.hpp"
#include "src/grids/variables/Variables.hpp"

namespace grids
{
	using data::Scalar;
	using data::uint;

	template <class CellType>
	class AbstractGrid
	{
	protected:
		uint size;
		Scalar V;
		AbstractSnapshotter* snapshotter;

	protected:
		std::vector<CellType> cells;
	public:

		AbstractGrid() {};
		virtual ~AbstractGrid() {};

		virtual void snapshot(uint i) const = 0;
	};
};

#endif /* ABSTRACTGRID_HPP_ */
