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
	protected:
		uint size;
		Scalar V;
		AbstractSnapshotter snapshotter;

	public:
		AbstractGrid() {};
		virtual ~AbstractGrid() {};

		virtual void snapshot(uint i) const = 0;
	};
};

#endif /* ABSTRACTGRID_HPP_ */