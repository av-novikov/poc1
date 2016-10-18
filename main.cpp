#include <iostream>

#include "src/grids/cells/RadialCell.hpp"
#include "src/grids/variables/Scalars.hpp"

using namespace std;
//using namespace data;
//using namespace unit;

int main() {
	unit::RadialCell<data::Var1phaseNIT> cell(0, 1.0, 1.0, 1.0);
	cell.u_next.p = 1.0;
	cell.u_next.t = 2.0;

	cout << cell.u_next;

	//cout << data::Pressure::name << endl;

	return 0;
};
