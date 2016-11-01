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
	typedef Grid<Variable>::Iterator Iterator;
	//typedef models::AbstractModel<Cell, Grid> Model;

	//Grid<Variable> grid;
	/*Grid<Variable>::Geometry geom;
	geom.r_w = 0.1;
	geom.r_e = 100.0;
	geom.hz = 10.0;
	geom.size = 20;
	geom.size_ghost = 1;	// must be greater than 0

	grid.load(geom);
	for(Iterator it = grid.getIter(); it != nullptr; ++it)
	{
		cout << "#" << it->num << endl;
		cout << "coords:\t" << it->coords;
		cout << "sizes:\t" << it->sizes;
	}*/

	while (true)
	{
	}

	return 0;
};
