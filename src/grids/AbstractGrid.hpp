#ifndef ABSTRACTGRID_HPP_
#define	ABSTRACTGRID_HPP_

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

		uint totalSize;
		Scalar Volume;

	public:
		AbstractGrid() 
		{
			totalSize = 0;
			Volume = 0.0;
		};

		virtual ~AbstractGrid() {};
	};
};

#endif /* ABSTRACTGRID_HPP_ */
