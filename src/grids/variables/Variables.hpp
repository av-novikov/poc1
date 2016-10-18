#ifndef VARIABLES_HPP_
#define VARIABLES_HPP_

#include <iostream>

#include "src/grids/variables/Scalars.hpp"
#include "src/grids/variables/Matrix.hpp"

namespace data {

struct Var1phaseContainer {
	union {
		Scalar values[1];
		struct {
			Pressure::ValueType p;
		};
	};

	static const std::string names[1];

	static const uint size;
};

const std::string Var1phaseContainer::names[] = {Pressure::name};
const uint Var1phaseContainer::size = 1;
typedef Vector<1, Var1phaseContainer> Var1phase;

struct Var1phaseNITContainer {
	union {
		Scalar values[2];
		struct {
			Temperature::ValueType t;
			Pressure::ValueType p;
		};
	};

	static const std::string names[2];

	static const uint size;
};

const uint Var1phaseNITContainer::size = 2;
const std::string Var1phaseNITContainer::names[] = {Pressure::name, Temperature::name};
typedef Vector<2, Var1phaseNITContainer> Var1phaseNIT;

struct EmptyContainer
{
};

};


#endif /* VARIABLES_HPP_ */
