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

#include <type_traits>

#include "src/snapshot/AbstractSnapshotter.hpp"
#include "src/grids/RadialGrid.hpp"

template<class gridType>
class VTKSnapshotter : public AbstractSnapshotter<gridType>
{
public:
	typedef AbstractSnapshotter<gridType> Base;
	typedef gridType Grid;
	typedef typename Grid::Variable Variable;
	typedef typename Grid::DependentVariable DependentVariable;
	typedef typename Grid::Cell Cell;
	typedef typename Grid::VtkGridPtr VtkGridPtr;
	typedef typename Grid::VtkWriterPtr VtkWriterPtr;
protected:
	using Base::grid;
private:

	// Except RadialGrid
	template <typename TVariable, typename TDependentVariable = data::EmptyContainer>
	void writePoints(VtkGridPtr vtk_grid, typename std::enable_if<!std::is_same<gridType, grids::RadialGrid<TVariable, 
						TDependentVariable>>::value>::type* = 0) const {};
	template <typename TVariable, typename TDependentVariable = data::EmptyContainer>
	void writeCells(VtkGridPtr vtk_grid, typename std::enable_if<!std::is_same<gridType, grids::RadialGrid<TVariable,
						TDependentVariable>>::value>::type* = 0) const {};

	// RadialGrid
	template <typename TVariable, typename TDependentVariable>
	inline void writePoints(VtkGridPtr vtk_grid, typename std::enable_if<std::is_same<gridType, grids::RadialGrid<TVariable, TDependentVariable>>::value, gridType>::type* = 0) const
	{
		auto points = vtkSmartPointer<vtkPoints>::New();

		for (auto it = grid->getPointIter(); it != nullptr; ++it)
			points->InsertNextPoint(it->coords.r - it->sizes.r / 2.0, 0.0, 0.0);
		for (auto it = grid->getPointIter(); it != nullptr; ++it)
			points->InsertNextPoint(it->coords.r - it->sizes.r / 2.0, 0.0, -grid->geom.hz);

		vtk_grid->SetPoints(points);
	};
	template <typename TVariable, typename TDependentVariable>
	inline void writeCells(VtkGridPtr vtk_grid, typename std::enable_if<std::is_same<gridType, grids::RadialGrid<TVariable, TDependentVariable>>::value, gridType>::type* = 0) const
	{
		auto polygons = vtkSmartPointer<vtkCellArray>::New();
		auto polygon = vtkSmartPointer<vtkPolygon>::New();
		polygon->GetPointIds()->SetNumberOfIds(4);

		vtkSmartPointer<vtkDoubleArray> vars[Variable::size];
		for (grids::uint i = 0; i < Variable::size; i++)
		{
			vars[i] = vtkSmartPointer<vtkDoubleArray>::New();
			vars[i]->SetName(Variable::names[i].c_str());
		}

		int k = 0;
		for (auto it = grid->getInnerIter(); it != nullptr; ++it)
		{
			polygon->GetPointIds()->SetId(0, k);
			polygon->GetPointIds()->SetId(1, k + 1);
			polygon->GetPointIds()->SetId(2, k + grid->geom.size + 2);
			polygon->GetPointIds()->SetId(3, k + grid->geom.size + 1);
			polygons->InsertNextCell(polygon);

			for (grids::uint i = 0; i < Variable::size; i++)
				vars[i]->InsertNextValue(it->u_next.values[i]);

			k++;
		}

		vtk_grid->SetPolys(polygons);
		vtkCellData* fd = vtk_grid->GetCellData();
		for (grids::uint i = 0; i < Variable::size; i++)
			fd->AddArray(vars[i]);
	};
public:
	VTKSnapshotter()
	{
		isGhostIncluded = false;
		EXT = "vtp";
		grid = nullptr;
	};

	void dump(const uint i) const
	{
		assert(grid != nullptr);

		std::string fileName = getFileName(i);
		auto vtk_grid = VtkGridPtr::New();
		writePoints<Variable, DependentVariable>(vtk_grid);
		writeCells<Variable, DependentVariable>(vtk_grid);

		auto writer = VtkWriterPtr::New();
		writer->SetFileName(fileName.c_str());
		writer->SetInputData(vtk_grid);
		writer->Write();
	};
};

#endif /* VTKSNAPSHOTTER_HPP_ */
