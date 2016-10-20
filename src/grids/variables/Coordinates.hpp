#ifndef COORDINATES_HPP_
#define COORDINATES_HPP_

#include "src/grids/variables/Matrix.hpp"

namespace data
{
	struct Point1dContainer
	{
		typedef Scalar DataType;

		union {
			DataType values[1];
			struct {
				DataType r;
			};
		};
	};

	typedef Vector<1, Point1dContainer> Point1d;

	struct SizeContainer
	{
		typedef uint DataType;

		union {
			DataType values[3];
			struct {
				DataType x;
				DataType y;
				DataType z;
			};
		};
	};

	typedef Vector<3, SizeContainer> Size;

	struct CylindricalSizeContainer
	{
		typedef uint DataType;

		union {
			DataType values[3];
			struct {
				DataType r;
				DataType phi;
				DataType z;
			};
		};
	};

	typedef Vector<3, CylindricalSizeContainer> CylindricalSize;
};

#endif /* COORDINATES_HPP_ */
