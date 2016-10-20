#ifndef ABSTRACTMODEL_HPP_
#define ABSTRACTMODEL_HPP_

namespace models
{
	template<class CellType, template<class CellType> class GridType>
	class AbstractModel : public GridType<CellType> 
	{
	public:

	public:
	};
};

#endif /* ABSTRACTMODEL_HPP_ */
