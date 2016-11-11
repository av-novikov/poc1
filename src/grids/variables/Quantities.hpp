#ifndef QUANTITIES_HPP_
#define QUANTITIES_HPP_

#include <string>
#include "src/grids/variables/Matrix.hpp"

using std::string;

namespace quantities
{
	typedef double Scalar;

	inline Scalar MilliDarcyToM2(const Scalar perm)
	{
		return perm * 0.986923 * 1.E-15;
	};

	inline Scalar cPToPaSec(const Scalar visc)
	{
		return visc / 1000.0;
	};

	constexpr Scalar p_dim = 100000.0;	// BAR
	constexpr Scalar t_dim = 3600.0; 	// HOUR
	constexpr Scalar x_dim = 10.0;		// NEAR-WELLBORE RADIUS
	constexpr Scalar T_dim = 273.15;	// 0 degree at Celcius
	
	constexpr Scalar rho_dim = p_dim / (x_dim / t_dim * x_dim / t_dim);

	constexpr char PRESSURE[] = 			"pressure";
	constexpr char OIL_SATURATION[] = 		"oil saturation";
	constexpr char TEMPERATURE[] = 			"temperature";
	constexpr char VELOCITY[] =				"velocity";

	// Pressure
	long double operator"" _bar(long double d) { return d; };
	long double operator"" _Pa(long double d) { return d / p_dim; };
	constexpr Scalar getPressure(const Scalar d) { return d; };

	// Distance
	long double operator"" _m(long double d) { return d / x_dim; };
	constexpr Scalar getDistance(const Scalar d) { return d * x_dim; };

	// Time
	long double operator"" _sec(long double d) { return d / t_dim; };
	long double operator"" _h(long double d) { return d; };
	constexpr Scalar getTime(const Scalar d) { return d; };

	// Temperature
	long double operator"" _C(long double d) { return d + T_dim; };
	constexpr Scalar getTemperature(const Scalar d) { return d - T_dim; };

	// Velocity
	constexpr Scalar getVelocity(const Scalar d) { return d * x_dim; };

	// Compressibility
	long double operator"" _pbar(long double d) { return d; };

	// Permeability
	long double operator"" _mD(long double d) { return MilliDarcyToM2(d) / x_dim / x_dim; };

	// Viscosity
	long double operator"" _cP(long double d) { return cPToPaSec(d) / p_dim / t_dim; };

	// Density
	long double operator"" _kgpm3(long double d) { return d / rho_dim; };
};

#endif /* QUANTITIES_HPP_ */
