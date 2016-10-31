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
	typedef units::RadialCell<data::Var1phase> Cell;
	typedef Cell::Variable Variable;
	//typedef Grid<Variable>::Iterator Iterator;
	//typedef models::AbstractModel<Cell, Grid> Model;

	Grid<Variable> grid;
	Grid<Variable>::Geometry geom;
	geom.r_w = 0.1;
	geom.r_e = 100.0;
	geom.hz = 10.0;
	geom.size = 20;
	geom.size_ghost = 0;

	grid.load(geom);
	//Iterator it1 = grid.getIterator();
	//for(Iterator it = it1; it != nullptr; ++it)
	//for(vector<Cell>::iterator it = grid.cells.begin(); it != grid.cells.end(); ++it)
	for(int i = 0; i < 20; i++)
	{
		cout << grid.cells[i].num << endl;
	}

	while (true)
	{
	}

	return 0;
};
