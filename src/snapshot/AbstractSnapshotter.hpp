#ifndef ABSTRACTSNAPSHOTTER_HPP_
#define ABSTRACTSNAPSHOTTER_HPP_

#include <cstring>
#include <vector>

class AbstractSnapshotter
{
protected:
	bool isGhostIncluded;

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

	virtual void dump(const data::uint i) const = 0;
};

const std::string AbstractSnapshotter::PREFIX = "snaps";
const std::string AbstractSnapshotter::DOT = ".";
const std::string AbstractSnapshotter::UNDERSCORE = "_";
const std::string AbstractSnapshotter::SLASH = "/";
const std::string AbstractSnapshotter::MESH = "mesh";
const std::string AbstractSnapshotter::CORE = "core";

#endif /* ABSTRACTSNAPSHOTTER_HPP_ */
