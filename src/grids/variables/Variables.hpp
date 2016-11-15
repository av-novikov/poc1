#ifndef VARIABLES_HPP_
#define VARIABLES_HPP_

#include <iostream>
#include <functional>

#include "src/grids/variables/Quantities.hpp"
#include "src/grids/variables/Matrix.hpp"

namespace data {

using namespace quantities;
typedef std::function<const Scalar(const Scalar)> DimensionFoo;

/******************************** Var1phase ************************************/

struct Var1phaseContainer {
	typedef Scalar DataType;

	union {
		DataType values[1];
		struct {
			DataType p;
		};
	};

	static const uint size;
	static const std::string names[1];
	static const DimensionFoo getDimensioned [1];
};

const uint Var1phaseContainer::size = 1;
const std::string Var1phaseContainer::names[] = { PRESSURE };
const DimensionFoo Var1phaseContainer::getDimensioned[] = {	getPressure };
typedef Vector<1, Var1phaseContainer> Var1phase;

/********************************* Var1phaseNIT ************************************/

struct Var1phaseNITContainer {
	typedef Scalar DataType;

	union {
		DataType values[2];
		struct {
			DataType t;
			DataType p;
		};
	};

	static const uint size;
	static const std::string names[2];
	static const DimensionFoo getDimensioned [2];
};

const uint Var1phaseNITContainer::size = 2;
const std::string Var1phaseNITContainer::names[] = {PRESSURE, TEMPERATURE};
const DimensionFoo Var1phaseNITContainer::getDimensioned[] = { getTemperature, getPressure };
typedef Vector<2, Var1phaseNITContainer> Var1phaseNIT;

/********************************* EmptyContainer ************************************/

struct EmptyContainer
{
	static const uint size;
	typedef Scalar DataType;
};

const uint EmptyContainer::size = 0;

/********************************* VelocityContainer ************************************/

struct VelocityContainer {
	typedef Scalar DataType;

	union {
		DataType values[1];
		struct {
			DataType w;
		};
	};

	static const uint size;
	static const std::string names[1];
	static const DimensionFoo getDimensioned[1];
};

const uint VelocityContainer::size = 2;
const std::string VelocityContainer::names[] = { VELOCITY };
const DimensionFoo VelocityContainer::getDimensioned[] = { getVelocity };
typedef Vector<1, VelocityContainer> Velocity;

};

#endif /* VARIABLES_HPP_ */
