#ifndef RESERVOIRPROPERTIES_HPP_
#define RESERVOIRPROPERTIES_HPP_

#include <vector>

#include "src/models/AbstractModel.hpp"
#include "src/utils/Interpolate.h"

namespace models
{
	namespace properties
	{
		typedef data::Scalar Scalar;

		class FormationProperties
		{
		public:
			// Porosity at reference pressure
			Scalar m0;
			// Reference pressure
			Scalar p0;
			// Reservoir compressibility
			Scalar beta;

			Interpolate* m_table;
			// m = m0 + beta * (p - p0)
			inline Scalar getPorosity(const Scalar p) const
			{
				return m0 + beta * (p - p0);
			};

			// Reservoir permeabilities
			Scalar perm_r;
			Scalar perm_z;
			inline Scalar getPermeability(const Scalar r) const
			{
				return (r > radius_eff ? perm_r : perm_eff);
			};

			// Effective properties of near-wellbore zone
			std::vector<Scalar> perms_eff, radiuses_eff, skins_eff;
			Scalar perm_eff, radius_eff, skin_eff;

			// Depth and thickness of formation
			Scalar thickness;

			// Reservoir pressure
			Scalar p_res;
			// Initial reservoir pressure
			Scalar p_init;
			// Initial oil/water saturation
			Scalar s_init;

			// Density of formation material in STC
			Scalar rho_stc;
			// Mass heat capacity of formation
			Scalar c;
			// Lateral thermal conductivity
			Scalar lambda_r;
			// Vertical thermal conductivity
			Scalar lambda_z;
		};

		class FluidProperties
		{
		public:
			// Viscosity
			Scalar visc;
			Interpolate* visc_table;
			inline Scalar getVisc(const Scalar p) const
			{
				return visc_table->Solve(p);
			};
			inline Scalar getVisc_dp(const Scalar p) const
			{
				return visc_table->DSolve(p);
			};

			// Fluid compressibility
			Scalar beta;
			Interpolate* beta_table;

			// Fluid density in STC
			Scalar rho_stc;
			inline Scalar getDensity(const Scalar p) const
			{
				return rho_stc * (1.0 + beta * p);
			};
			inline Scalar getDensity_dp(const Scalar p) const
			{
				return rho_stc * beta;
			};

			// Relative permeability
			Interpolate* kr_table;

			// Volume factor
			Interpolate* b_table;
			inline Scalar getB(const Scalar p) const 
			{
				return b_table->Solve(p);
			};
			inline Scalar getB_dp(const Scalar p) const
			{
				return b_table->DSolve(p);
			};
			Scalar b_bore;

			// Mass heat capacity of formation
			Scalar c;
			// Thermal conductivity
			Scalar lambda;
			// Joule-Thomson coefficients
			Scalar jt;
			// Adiabatic coefficients
			Scalar ad;
		};

		class OilProperties : public FluidProperties
		{
		public:
		};

		class GasProperties : public FluidProperties
		{
		public:
		};
	};
};

#endif /* RESERVOIRPROPERTIES_HPP_ */