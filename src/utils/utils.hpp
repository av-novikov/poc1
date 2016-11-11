#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <algorithm>
#include <fstream>
#include <utility>
#include <string>

#include "src/utils/Interpolate.h"

struct sort_pair_first {
	bool operator() (const std::pair<double, double> &left, const std::pair<double, double> &right)
	{
		return left.first < right.first;
	}
};

struct sort_pair_second {
	bool operator() (const std::pair<double, double> &left, const std::pair<double, double> &right)
	{
		return left.second < right.second;
	}
};

inline void setDataFromFile(std::vector< std::pair<double, double> >& vec, std::string fileName)
{
	std::ifstream file;
	file.open(fileName.c_str(), ifstream::in);

	double temp1, temp2;
	while (!file.eof())
	{
		file >> temp1;
		if (file.eof())
			break;
		file >> temp2;
		vec.push_back(std::make_pair(temp1, temp2));
	}

	file.close();
};

inline Interpolate* setDataset(std::vector< std::pair<double, double> >& vec, const double xDim, const double yDim)
{
	std::sort(vec.begin(), vec.end(), sort_pair_first());

	const int N = vec.size();
	double* x = new double[N];
	double* y = new double[N];

	for (int i = 0; i < N; i++)
	{
		x[i] = vec[i].first / xDim;
		y[i] = vec[i].second / yDim;
	}

	return new Interpolate(x, y, N);
};

inline bool IsNan(double a)
{
	if (a != a)  return true;
	return false;
};

inline double sign(int a)
{
	if (a > 0) return 1.0;
	else if (a < 0) return -1.0;
	else return 0.0;
};

#endif /* UTILS_HPP_ */
