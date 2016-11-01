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

using namespace grids;

template <typename TVariable, typename TDependentVariable, 
template <typename TVariable, typename TDependentVariable> class gridType>
class VTKSnapshotter : public AbstractSnapshotter
{
public:
	typedef gridType<TVariable, TDependentVariable> Grid;
	typedef typename Grid::Cell Cell;
	typedef TVariable Variable;
	typedef TDependentVariable DependentVariable;
	typedef typename Grid::VtkPtr VtkPtr;
	typedef typename Grid::VtkWriterPtr VtkWriterPtr;
private:
	VtkPtr getVtkPtr() const
	{
		return VtkPtr::New();
	};

	void writePoints() const;
	void writeCells() const;
protected:
	Grid* grid;
public:
	VTKSnapshotter()
	{
		isGhostIncluded = false;
		EXT = "vtp";
	};

	void setGrid(const Grid* _grid)
	{
		grid = const_cast<Grid*>(_grid);
	};

	void dump(const data::uint i) const 
	{
		std::string fileName = getFileName();
		auto vtk_grid = getVtkPtr();
		writeGeometry();
		writeVariables();

		auto writer = VtkWriterPtr::New();
		writer->SetFileName(fileName.c_str());
		writer->SetInputData(vtk_grid);
		writer->Write();
	}
};

template <typename TVariable, typename TDependentVariable>
inline void VTKSnapshotter<TVariable, TDependentVariable, 
			grids::RadialGrid<TVariable, TDependentVariable> >::writePoints() const
{
	auto points = vtkSmartPointer<vtkPoints>::New();

	for(it = grid->getPointIter(); it != nullptr; ++it)
		points->InsertNextPoint(it->coords.r - it->coords.hr / 2.0, 0.0, 0.0);
	for (it = grid->getPointIter(); it != nullptr; ++it)
		points->InsertNextPoint(it->coords.r - it->coords.hr / 2.0, 0.0, -grid->geom.h_z);

	vtk_grid->SetPoints(points);
};

template <typename TVariable, typename TDependentVariable>
inline void VTKSnapshotter<TVariable, TDependentVariable,
	grids::RadialGrid<TVariable, TDependentVariable> >::writeCells() const
{
	auto polygons = vtkSmartPointer<vtkCellArray>::New();
	auto polygon = vtkSmartPointer<vtkPolygon>::New();
	polygon->GetPointIds()->SetNumberOfIds(4);

	vtkSmartPointer<vtkDoubleArray> vars[Variable::size];
	for (grids::uint i = 0; i < Variable::size; i++)
	{
		vars[i] = vtkSmartPointer<vtkDoubleArray>::New();
		vars[i]->SetName(Variable::names[i]);
	}

	int k = 0;
	for (it = grid->getInnerIter(); it != nullptr; ++it)
	{
		polygon->GetPointIds()->SetId(0, k);
		polygon->GetPointIds()->SetId(1, k + 1);
		polygon->GetPointIds()->SetId(2, k + grid->geom.size + 1);
		polygon->GetPointIds()->SetId(3, k + grid->geom.size);
		polygons->InsertNextCell(polygon);

		for (grids::uint i = 0; i < Variable::size; i++)
			vars[i]->InsertnextValue(it->u_next.values[i]);

		k++;
	}

	vtk_grid->SetPolys(polygons);
	vtkCellData* fd = vtk_grid->GetCellData();
	for (grids::uint i = 0; i < Variable::size; i++)
		fd->AddArray(vars[i]);
};

#endif /* VTKSNAPSHOTTER_HPP_ */
