/****************************************************************************
 *            plane.cpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#include "plane.hpp"

namespace eternal_lands
{

	Plane::Plane()
	{
		m_normal_and_distance = glm::vec4(0.0f);
	}

	Plane::Plane(const glm::vec3 &point, const glm::vec3 &dir)
	{
		set_normal(dir);
		recalculate_distance(point);
	}

	Plane::Plane(const glm::vec3 &dir, const float distance)
	{
		set_normal(dir);
		set_distance(distance);
	}

	Plane::Plane(const glm::vec4 &data)
	{
		set_data(data);
	}

	Plane::~Plane() throw()
	{
	}

	Plane Plane::transform(const glm::mat4 &matrix) const
	{
		Plane result;

		result.set_normal(glm::mat3(matrix) * get_normal());

		result.recalculate_distance(glm::vec3(matrix *
			glm::vec4(get_member_point(), 1.0f)));

		return result;
	}

}
