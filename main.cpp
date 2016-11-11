#include <iostream>

#include "src/models/Oil/Oil.hpp"
#include "src/grids/RadialGrid.hpp"
#include "src/grids/cells/RadialCell.hpp"

using namespace std;
using namespace quantities;

template<typename Variable> using Grid = grids::RadialGrid<Variable>;

int main() 
{
	typedef data::Var1phase Variable;
	typedef models::oil::OilModel<Grid<Variable>> Model;

	Grid<Variable>::Geometry geom;
	geom.r_w = 0.1_m;
	geom.r_e = 100.0_m;
	geom.hz = 10.0_m;
	geom.size = 20;
	geom.size_ghost = 1;	// must be greater than 0
	
	Model model;
	model.loadGrid(geom);
	model.setSnapshotter(true);
	model.snapshot(0);

	return 0;
};
