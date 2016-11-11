#include "src/models/Oil/Oil.hpp"
#include "src/grids/variables/Quantities.hpp"

using namespace models::properties;
using namespace quantities;

FormationProperties getFormationProps()
{
	FormationProperties props;
	props.m0 = 0.1;
	props.p0 = 200.0_bar;
	props.beta = 1.E-4_pbar;
	props.perm_r = props.perm_z = 20.0_mD;

	props.thickness = 10.0_m;
	
	props.p_res = props.p_init = 200.0_bar;
	
	props.rho_stc = 2000.0_kgpm3;

	return props;
};

OilProperties getOilProps()
{
	OilProperties props;
	
	props.beta = 1.E-4_pbar;
	props.visc = 1.0_cP;
	props.b_bore = 1.0;
	props.rho_stc = 800.0_kgpm3;

	return props;
};