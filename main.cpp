#include <iostream>

#include "src/models/AbstractModel.hpp"
#include "src/grids/RadialGrid.hpp"
#include "src/grids/cells/RadialCell.hpp"

using namespace std;
//using namespace data;
//using namespace units;

template<typename Variable> using Grid = grids::RadialGrid<Variable>;

int main() 
{
	typedef units::RadialCell<data::Var1phase> Cell;
	typedef Cell::Variable Variable;
	//typedef models::AbstractModel<Cell, Grid> Model;


	Cell a;
	Grid<Variable> grid;
	Grid<Variable>::Geometry geom;
	geom.r_w = 0.1;
	geom.r_e = 100.0;
	geom.hz = 10.0;
	geom.size = 20;
	geom.size_ghost = 0;


	grid.load(geom);
	//Model model;


	while (true)
	{
	}

	return 0;
};
