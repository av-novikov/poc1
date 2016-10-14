#include <iostream>

#include "grids/cells/AbstractCell.hpp"

using namespace std;
//using namespace data;
//using namespace unit;

int main()
{
	unit::AbstractCell<data::Var1phaseNIT> cell;
	cell.u_next.p = 1.0; cell.u_next.t = 2.0;

	cout << cell.u_next << endl;

	return 0;
};