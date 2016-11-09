#ifndef SCALARS_HPP_
#define SCALARS_HPP_

#include <string>
#include "src/grids/variables/Matrix.hpp"

using std::string;

namespace quantities
{
	typedef double Scalar;

	constexpr Scalar p_dim = 100000.0;	// BAR
	constexpr Scalar t_dim = 3600.0; 	// HOUR
	constexpr Scalar x_dim = 10.0;		// NEAR-WELLBORE RADIUS
	constexpr Scalar T_dim = 273.15;	// 0 degree at Celcius

	constexpr char PRESSURE[] = 			"pressure";
	constexpr char OIL_SATURATION[] = 		"oil saturation";
	constexpr char TEMPERATURE[] = 			"temperature";

	// Pressure
	long double operator"" _bar(long double d) { return d; };
	long double operator"" _Pa(long double d) { return d / p_dim; };
	constexpr Scalar getPressure(const Scalar d) { return d; };

	// Distance
	long double operator"" _m(long double d) { return d / x_dim; };
	constexpr Scalar getDistance(const Scalar d) { return d * x_dim; };

	// Time
	long double operator"" _sec(long double d) { return d / t_dim; };
	constexpr Scalar getTime(const Scalar d) { return d; };

	// Temperature
	long double operator"" _C(long double d) { return d + T_dim; };
	constexpr Scalar getTemperature(const Scalar d) { return d - T_dim; };
};

#endif /* SCALARS_HPP_ */
