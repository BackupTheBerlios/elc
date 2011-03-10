/****************************************************************************
 *            frustum.cpp
 *
 * Author: 2010  Daniel Jungmann <dsj@gmx.net>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#include "frustum.hpp"

namespace eternal_lands
{

	void Frustum::build_frustum(const BoundingBox &box)
	{
		glm::vec3 point, dir;

		point = box.get_point(0);

		dir = box.get_point(1) - point;
		m_planes[pt_right] = Plane(point, dir);

		dir = box.get_point(2) - point;
		m_planes[pt_top] = Plane(point, dir);

		dir = box.get_point(4) - point;
		m_planes[pt_near] = Plane(point, dir);

		point = box.get_point(7);

		dir = box.get_point(6) - point;
		m_planes[pt_left] = Plane(point, dir);

		dir = box.get_point(5) - point;
		m_planes[pt_bottom] = Plane(point, dir);

		dir = box.get_point(3) - point;
		m_planes[pt_far] = Plane(point, dir);

		m_mask.reset();

		m_mask[pt_right] = true;
		m_mask[pt_left] = true;
		m_mask[pt_top] = true;
		m_mask[pt_bottom] = true;
		m_mask[pt_near] = true;
		m_mask[pt_far] = true;
	}

	Frustum::Frustum()
	{
		m_mask.reset();
	}

	Frustum::Frustum(const glm::mat4 &matrix)
	{
		m_planes[pt_left] = Plane(glm::vec4(matrix[0][3] + matrix[0][0],
			matrix[1][3] + matrix[1][0], matrix[2][3] + matrix[2][0],
			matrix[3][3] + matrix[3][0]));
		m_planes[pt_right] = Plane(glm::vec4(matrix[0][3] - matrix[0][0],
			matrix[1][3] - matrix[1][0], matrix[2][3] - matrix[2][0],
			matrix[3][3] - matrix[3][0]));
		m_planes[pt_top] = Plane(glm::vec4(matrix[0][3] - matrix[0][1],
			matrix[1][3] - matrix[1][1], matrix[2][3] - matrix[2][1],
			matrix[3][3] - matrix[3][1]));
		m_planes[pt_bottom] = Plane(glm::vec4(matrix[0][3] + matrix[0][1],
			matrix[1][3] + matrix[1][1], matrix[2][3] + matrix[2][1],
			matrix[3][3] + matrix[3][1]));
		m_planes[pt_near] = Plane(glm::vec4(matrix[0][3] + matrix[0][2],
			matrix[1][3] + matrix[1][2], matrix[2][3] + matrix[2][2],
			matrix[3][3] + matrix[3][2]));
		m_planes[pt_far] = Plane(glm::vec4(matrix[0][3] - matrix[0][2],
			matrix[1][3] - matrix[1][2], matrix[2][3] - matrix[2][2],
			matrix[3][3] - matrix[3][2]));

		m_mask.reset();

		m_mask[pt_right] = true;
		m_mask[pt_left] = true;
		m_mask[pt_top] = true;
		m_mask[pt_bottom] = true;
		m_mask[pt_near] = true;
		m_mask[pt_far] = true;
	}

	Frustum::Frustum(const BoundingBox &box)
	{
		build_frustum(box);
	}

	Frustum::~Frustum() throw()
	{
	}

	IntersectionType Frustum::intersect(const BoundingBox &box,
		const PlaneMask in_mask, PlaneMask &out_mask) const
	{
		Uint32 i, k;
		IntersectionType result;

		result = it_inside;

		out_mask.reset();

		assert(get_mask().to_ulong() >= in_mask.to_ulong());

		for (i = 0, k = 1; k <= in_mask.to_ulong(); i++, k += k)
		{
			if (in_mask[i])
			{
				switch (get_plane(i).intersect(box))
				{
					case it_outside:
						return it_outside;
					case it_intersect:
						out_mask[i] = true;
						result = it_intersect;
						break;
					case it_inside:
						break;
				}
			}
		}

		assert((result == it_intersect) != out_mask.none());

		return result;
	}

	bool Frustum::inside(const glm::vec3 &point, const PlaneMask in_mask)
		const
	{
		Uint32 i, k;
		IntersectionType result;

		result = it_inside;

		assert(get_mask().to_ulong() >= in_mask.to_ulong());

		for (i = 0, k = 1; k <= in_mask.to_ulong(); i++, k += k)
		{
			if (in_mask[i])
			{
				result = get_plane(i).intersect(point);

				if (result == it_outside)
				{
					return false;
				}
			}
		}

		return result != it_outside;
	}

	Frustum Frustum::transform(const glm::mat4 &world_matrix) const
	{
		Frustum frustum;
		Uint32 i, k;

		frustum.m_planes = m_planes;
		frustum.m_mask = m_mask;

		for (i = 0, k = 1; k <= get_mask().to_ulong(); i++, k += k)
		{
			if (get_mask()[i])
			{
				frustum.m_planes[i] =
					get_plane(i).transform(world_matrix);
			}
		}

		return frustum;
	}

}
