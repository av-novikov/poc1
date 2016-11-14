#ifndef OIL_HPP_
#define OIL_HPP_

#include "src/models/AbstractModel.hpp"
#include "src/models/ReservoirProperties.hpp"

namespace models
{
	namespace oil
	{
		template <class gridType>
		class OilModel : public AbstractModel<gridType>
		{
		public:
			typedef AbstractModel<gridType> Base;
			typedef gridType Grid;
			typedef typename Grid::Variable Variable;
			typedef typename Variable::Jacobian Jacobian;
			typedef typename Grid::DependentVariable DependentVariable;
			typedef typename Grid::Cell Cell;
			typedef typename Cell::Point Point;
			typedef typename Grid::Iterator Iterator;
			typedef typename Grid::RangeIterator RangeIterator;

			using Base::id;

		protected:
			using Base::grid;
			using Base::snapshotter;

			std::vector<properties::FormationProperties> props_sk;
			properties::OilProperties props;

			void setGridProps()
			{
				for (auto it : grid->getIter())
					it.prop_ptr = &props_sk[0];
			};
		public:

			inline Scalar getPermeability(const Cell& cell1, const Cell& cell2) const 
			{
				const Scalar k1 = cell1.prop_ptr->getPermeability(cell1.coords.r);
				const Scalar k2 = cell2.prop_ptr->getPermeability(cell2.coords.r);
				return	k1 * k2 * (cell1.sizes.r + cell2.sizes.r) /
						(k1 * cell2.sizes.r + k2 * cell1.sizes.r);
			};
			inline Variable& getU(const Cell& cell) const
			{
				const Scalar p = cell.u_next.p;
				Variable result;
				result.values[0] = cell.prop_ptr->getPorosity(p) * 
									cell.prop_ptr->getDensity(p);
				return result;
			};
			inline Jacobian& getU_dp(const Cell& cell) const
			{
				Jacobian result;

			};
			inline Variable& getU_prev(const Cell& cell) const
			{
				const Scalar p = cell.u_prev.p;
				Variable result;
				result.values[0] = cell.prop_ptr->getPorosity(p) *
									cell.prop_ptr->getDensity(p);
				return result;
			};
			inline Variable& getF(const Cell& cell1, const Cell& cell2) const
			{
				const Scalar hr1 = cell1.sizes.r;
				const Scalar hr2 = cell2.sizes.r;
				const Scalar p1 = cell1.u_next.p;
				const Scalar p2 = cell2.u_next.p;

				Variable result;
				result.r = getPermeability(cell1, cell2) * grid->getCommonSquare(cell1, cell2) *
						(props.getDensity(p1) * hr2 + props.getDensity(p2) * hr1) /
						(props.getVisc(p1) * hr2 + props.getVisc(p2) * hr1) *
						2.0 * (p2 - p1) / (hr1 + hr2);
				return result;
			};
			inline Variable& getQ(const Cell& cell) const
			{
				Variable result;
				return result;
			};

		};

		properties::FormationProperties getFormationProps();
		properties::OilProperties getOilProps();
	};
};

#endif /* OIL_HPP_ */
