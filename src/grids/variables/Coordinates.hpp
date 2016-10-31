#ifndef COORDINATES_HPP_
#define COORDINATES_HPP_

#include "src/grids/variables/Matrix.hpp"

namespace data
{
	// Sizes
	/*-------------------------------------------------------------------*/

	struct Size1dContainer
	{
		typedef uint DataType;

		union {
			DataType values[1];
			struct {
				DataType r;
			};
		};

		static const uint size;
	};

	const uint Size1dContainer::size = 1;
	typedef Vector<1, Size1dContainer> Size1d;

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

		static const uint size;
	};

	const uint SizeContainer::size = 3;
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

		static const uint size;
	};

	const uint CylindricalSizeContainer::size = 3;
	typedef Vector<3, CylindricalSizeContainer> CylindricalSize;

	// Points
	/*-------------------------------------------------------------------*/

	struct Point1dContainer
	{
		typedef Scalar DataType;
		typedef Size1d IndexesType;

		union {
			DataType values[1];
			struct {
				DataType r;
			};
		};
		static const uint size;
	};

	const uint Point1dContainer::size = 1;
	typedef Vector<1, Point1dContainer> Point1d;

};

#endif /* COORDINATES_HPP_ */
