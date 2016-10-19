#include <iostream>

#include "src/models/AbstractModel.hpp"
#include "src/grids/RadialGrid.hpp"
#include "src/grids/cells/RadialCell.hpp"

using namespace std;
//using namespace data;
//using namespace unit;

template<class CellType> using Grid = grids::RadialGrid<CellType>;

int main() 
{
	typedef unit::RadialCell<data::Var1phase> Cell;
	typedef Cell::Variable Variable;
	typedef models::AbstractModel<Cell, Grid> Model;

	Model model;
	//cout << data::Pressure::name << endl;

	while (true)
	{
	}

	return 0;
};
