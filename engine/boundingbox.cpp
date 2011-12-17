/****************************************************************************
 *            boundingbox.cpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#include "boundingbox.hpp"
#include "exceptions.hpp"

namespace eternal_lands
{

	BoundingBox::BoundingBox(): m_center(glm::vec3(0.0f)),
		m_half_size(glm::vec3(0.0f))
	{
	}

	BoundingBox::BoundingBox(const glm::vec3 &min, const glm::vec3 &max)
	{
		set_min_max(min, max);
	}

	BoundingBox::~BoundingBox() throw()
	{
	}

	void BoundingBox::set_min_max(const glm::vec3 &min, const glm::vec3 &max)
	{
		if (!glm::all(glm::lessThanEqual(min, max)))
		{
			EL_THROW_EXCEPTION(RangeErrorException());
		}

		set_center((min + max) * 0.5f);
		set_half_size((max - min) * 0.5f);
	}

	void BoundingBox::set_half_size(const glm::vec3 &half_size)
	{
		if (!glm::all(glm::greaterThanEqual(half_size, glm::vec3(0.0f))))
		{
			EL_THROW_EXCEPTION(RangeErrorException());
		}

		m_half_size = half_size;
	}

	void BoundingBox::merge(const BoundingBox &box)
	{
		glm::vec3 min, max;

		min = glm::min(get_min(), box.get_min());
		max = glm::max(get_max(), box.get_max());

		m_center = (min + max) * 0.5f;
		m_half_size = (max - min) * 0.5f;
	}

	float BoundingBox::overlap(const BoundingBox &box) const
	{
		glm::vec3 t, t0, t1;

		t0 = glm::abs(get_center() - box.get_center());
		t1 = get_half_size() + box.get_half_size();

		t = glm::max(t1 - t0, glm::vec3(0.0f));

		return t[0] * t[1] * t[2];
	}

	bool BoundingBox::contains(const BoundingBox &box) const
	{
		glm::vec3 dist;

		dist = glm::abs(get_center() - box.get_center()) +
			box.get_half_size();

		return glm::all(glm::lessThanEqual(dist, get_half_size()));
	}

	BoundingBox BoundingBox::transform(const glm::mat4 &matrix) const
	{
		glm::vec3 t0, t1, vec;
		Uint32 i;
		BoundingBox result;

		t0 = glm::vec3(std::numeric_limits<float>::max());
		t1 = glm::vec3(-std::numeric_limits<float>::max());

		for (i = 0; i < 8; i++)
		{
			vec = glm::vec3(matrix * glm::vec4(get_point(
				std::bitset<3>(i)), 1.0f));
			t0 = glm::min(t0, vec);
			t1 = glm::max(t1, vec);
		}

		result.set_min_max(t0, t1);

		return result;
	}

}
