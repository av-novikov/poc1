#ifndef ABSTRACTMODEL_HPP_
#define ABSTRACTMODEL_HPP_

namespace models
{
	template<class CellType, template<class CellType> class GridType>
	class AbstractModel : public GridType<CellType> 
	{
	public:
		typedef CellType Cell;
		typedef GridType<CellType> Grid;
	public:
	};
};

#endif /* ABSTRACTMODEL_HPP_ */
