/****************************************************************************
 *            frustum.hpp
 *
 * Author: 2010  Daniel Jungmann <dsj@gmx.net>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#ifndef	UUID_0fd3a14d_9ccd_4936_97eb_8dabed20ec21
#define	UUID_0fd3a14d_9ccd_4936_97eb_8dabed20ec21

#ifndef	__cplusplus
#error	"Including C++ header in C translation unit!"
#endif	/* __cplusplus */

#include "prerequisites.hpp"
#include "plane.hpp"

/**
 * @file
 * @brief The @c class Frustum.
 * This file contains the @c class Frustum.
 */
namespace eternal_lands
{

	/**
	 * Different types of planes used for frustums.
	 * @{
	 */
	enum PlaneType
	{
		pt_right = 0,
		pt_left = 1,
		pt_top = 2,
		pt_bottom = 3,
		pt_near = 4,
		pt_far = 5,
		pt_extra0 = 6,
		pt_extra1 = 7
	};
	/**
	 * @}
	 */

	typedef std::bitset<8> PlaneMask;

	class Frustum
	{
		private:
			boost::array<Plane, 8> m_planes;
			PlaneMask m_mask;

			void build_frustum(const BoundingBox &box);

		public:
			Frustum();
			Frustum(const glm::mat4 &matrix);
			Frustum(const BoundingBox &box);
			~Frustum() throw();

			inline const PlaneMask &get_mask() const
			{
				return m_mask;
			}

			inline const Plane &get_plane(const Uint32 index) const
			{
				return m_planes[index];
			}

			inline IntersectionType intersect(const BoundingBox &box) const
			{
				PlaneMask out_mask;

				return intersect(box, get_mask(), out_mask);
			}

			inline IntersectionType intersect(const BoundingBox &box,
				const PlaneMask in_mask) const
			{
				PlaneMask out_mask;

				return intersect(box, in_mask, out_mask);
			}

			IntersectionType intersect(const BoundingBox &box,
				const PlaneMask in_mask, PlaneMask &out_mask)
				const;

			bool inside(const glm::vec3 &point,
				const PlaneMask in_mask) const;

			Frustum transform(const glm::mat4 &world_matrix) const;

	};

}

#endif	/* UUID_0fd3a14d_9ccd_4936_97eb_8dabed20ec21 */
