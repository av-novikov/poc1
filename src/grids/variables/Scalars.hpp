#ifndef SCALARS_HPP_
#define SCALARS_HPP_

#include <string>
#include "src/grids/variables/Matrix.hpp"

using std::string;

namespace data
{
	template <uint i>
	struct ScalarPhysicalVariable
	{
		typedef Scalar ValueType;
		static const string name;
		static const string dim;
	};

	typedef ScalarPhysicalVariable<0> Pressure;
	template<> const string Pressure::name = "pressure";
	template<> const string Pressure::dim = "bar";

	typedef ScalarPhysicalVariable<1> OilSaturation;
	template<> const string OilSaturation::name = "oil saturation";
	template<> const string OilSaturation::dim = "";

	typedef ScalarPhysicalVariable<2> Temperature;
	template<> const string Temperature::name = "temperature";
	template<> const string Temperature::dim = "K";

};

#endif /* SCALARS_HPP_ */
