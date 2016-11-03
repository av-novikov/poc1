#ifndef ABSTRACTSNAPSHOTTER_HPP_
#define ABSTRACTSNAPSHOTTER_HPP_

#include <cstring>
#include <cassert>
#include <vector>

template <class gridType>
class AbstractSnapshotter
{
public:
	typedef gridType Grid;
	typedef unsigned int uint;
	typedef double Scalar;

protected:
	bool isGhostIncluded;
	Grid* grid;
protected:
	static const std::string PREFIX;
	static const std::string DOT;
	static const std::string UNDERSCORE;
	static const std::string SLASH;

	static const std::string MESH;
	static const std::string CORE;

	std::string EXT;

	std::string getFileName(const uint i) const
	{
		return 	PREFIX +
				SLASH +
				MESH +
				UNDERSCORE +
				std::to_string(i) +
				DOT + 
				EXT;
	};
public:

	void setGrid(const Grid* _grid)
	{
		assert(_grid != nullptr);
		grid = const_cast<Grid*>(_grid);
	};

	virtual void dump(const uint i) const = 0;
};

template <class gridType>
const std::string AbstractSnapshotter<gridType>::PREFIX = "snaps";
template <class gridType>
const std::string AbstractSnapshotter<gridType>::DOT = ".";
template <class gridType>
const std::string AbstractSnapshotter<gridType>::UNDERSCORE = "_";
template <class gridType>
const std::string AbstractSnapshotter<gridType>::SLASH = "/";
template <class gridType>
const std::string AbstractSnapshotter<gridType>::MESH = "mesh";
template <class gridType>
const std::string AbstractSnapshotter<gridType>::CORE = "core";

#endif /* ABSTRACTSNAPSHOTTER_HPP_ */
