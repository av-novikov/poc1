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
	typedef units::RadialCell<data::Var1phase> Cell;
	typedef Cell::Variable Variable;
	typedef models::AbstractModel<Cell, Grid> Model;
	Cell a;

	Model model;
	//cout << data::Pressure::name << endl;

	cout << sizeof(units::RadialCell<data::Var1phase>) << endl;

	while (true)
	{
	}

	return 0;
};
