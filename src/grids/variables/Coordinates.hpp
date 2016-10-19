#ifndef COORDINATES_HPP_
#define COORDINATES_HPP_

#include "src/grids/variables/Matrix.hpp"

namespace data
{
	struct Point1dContainer
	{
		union {
			Scalar values[1];
			struct {
				Scalar r;
			};
		};


	};

	typedef Vector<1, Point1dContainer> Point1d;
};

#endif /* COORDINATES_HPP_ */
