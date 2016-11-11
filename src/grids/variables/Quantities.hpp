#ifndef QUANTITIES_HPP_
#define QUANTITIES_HPP_

#include <string>

using std::string;

namespace quantities
{
	typedef double Scalar;

	constexpr Scalar MilliDarcyToM2(const Scalar perm)
	{
		return perm * 0.986923 * 1.E-15;
	};

	constexpr Scalar cPToPaSec(const Scalar visc)
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
	constexpr long double operator"" _bar(long double d) { return d; };
	constexpr long double operator"" _Pa(long double d) { return d / p_dim; };
	constexpr Scalar getPressure(const Scalar d) { return d; };

	// Distance
	constexpr long double operator"" _m(long double d) { return d / x_dim; };
	constexpr Scalar getDistance(const Scalar d) { return d * x_dim; };

	// Time
	constexpr long double operator"" _sec(long double d) { return d / t_dim; };
	constexpr long double operator"" _h(long double d) { return d; };
	constexpr Scalar getTime(const Scalar d) { return d; };

	// Temperature
	constexpr long double operator"" _C(long double d) { return d + T_dim; };
	constexpr Scalar getTemperature(const Scalar d) { return d - T_dim; };

	// Velocity
	constexpr Scalar getVelocity(const Scalar d) { return d * x_dim; };

	// Compressibility
	constexpr long double operator"" _pbar(long double d) { return d; };

	// Permeability
	constexpr long double operator"" _mD(long double d) { return MilliDarcyToM2(d) / x_dim / x_dim; };

	// Viscosity
	constexpr long double operator"" _cP(long double d) { return cPToPaSec(d) / p_dim / t_dim; };

	// Density
	constexpr long double operator"" _kgpm3(long double d) { return d / rho_dim; };
};

#endif /* QUANTITIES_HPP_ */
