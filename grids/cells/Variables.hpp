#ifndef VARIABLES_HPP_
#define VARIABLES_HPP_

#include "grids/Matrix.hpp"

namespace data
{
	struct Var1phaseContainer
	{
		union {
			Scalar values[1];
			struct
			{
				Scalar p;
			};
		};
	};

	typedef Vector<1, Var1phaseContainer> Var1phase;

	struct Var1phaseNITContainer
	{
		union {
			Scalar values[2];
			struct
			{
				Scalar t;
				Scalar p;
			};
		};
	};

	typedef Vector<2, Var1phaseNITContainer> Var1phaseNIT;

	struct EmptyContainer
	{
	};
};

#endif /* VARIABLES_HPP_ */
