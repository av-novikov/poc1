#ifndef VTKSNAPSHOTTER_HPP_
#define VTKSNAPSHOTTER_HPP_

#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkDoubleArray.h>
#include <vtkIntArray.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkPolygon.h>

#include "src/snapshot/AbstractSnapshotter.hpp"
#include "src/grids/RadialGrid.hpp"

template <class CellType>
class VTKSnapshotter //: public AbstractSnapshotter<grids::RadialGrid<CellType> >
{
public:
/*	VTKSnapshotter()
	{
		isGhostIncluded = false;
		EXT = "vtp";
	};*/


};

#endif /* VTKSNAPSHOTTER_HPP_ */
