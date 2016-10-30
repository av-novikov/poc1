#ifndef ABSTRACTSNAPSHOTTER_HPP_
#define ABSTRACTSNAPSHOTTER_HPP_

#include <cstring>
#include <vector>

#include "src/grids/variables/Matrix.hpp"

class AbstractSnapshotter
{
protected:
	bool isGhostIncluded;

	//virtual void writeGeometry(VtkPtr mesh) = 0;
	//virtual void writeVariables(VtkPtr mesh) = 0;
protected:
	static const std::string PREFIX;
	static const std::string DOT;
	static const std::string UNDERSCORE;
	static const std::string SLASH;

	static const std::string MESH;
	static const std::string CORE;

	std::string EXT;

	std::string getFileName(const data::uint i) const
	{
		return 	PREFIX +
				SLASH +
				MESH +
				UNDERSCORE +
				std::to_string(i) +
				EXT;
	};
public:

	/*void setGrid(GridType* _grid)
	{
		grid = _grid;
	};*/
	virtual void dump(const data::uint i) const
	{
		//auto name = getFileName(i);
		//auto mesh = GridType::getVtkGridType();
		//writeGeometry(mesh);
		//writeVariables(mesh);
	};
};

const std::string AbstractSnapshotter::PREFIX = "snaps";
const std::string AbstractSnapshotter::DOT = ".";
const std::string AbstractSnapshotter::UNDERSCORE = "_";
const std::string AbstractSnapshotter::SLASH = "/";
const std::string AbstractSnapshotter::MESH = "mesh";
const std::string AbstractSnapshotter::CORE = "core";

#endif /* ABSTRACTSNAPSHOTTER_HPP_ */
