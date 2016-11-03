#include <iostream>
#include <vector>

#include "src/models/AbstractModel.hpp"
#include "src/grids/RadialGrid.hpp"
#include "src/grids/cells/RadialCell.hpp"

using namespace std;
//using namespace data;
//using namespace units;

template<typename Variable> using Grid = grids::RadialGrid<Variable>;

int main() 
{
	typedef data::Var1phase Variable;
	typedef units::RadialCell<Variable> Cell;
	typedef Grid<Variable>::Iterator Iterator;
	typedef models::AbstractModel<Grid<Variable>> Model;

	Grid<Variable> grid;
	Grid<Variable>::Geometry geom;
	geom.r_w = 0.1;
	geom.r_e = 100.0;
	geom.hz = 10.0;
	geom.size = 20;
	geom.size_ghost = 1;	// must be greater than 0
	
	Model model;
	model.loadGrid(geom);
	model.setSnapshotter(true);
	model.snapshot(0);

	return 0;
};
