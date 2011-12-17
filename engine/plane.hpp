/****************************************************************************
 *            plane.hpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#ifndef	UUID_2ffdda7b_fa7c_49d2_85d8_d5641f070cc4
#define	UUID_2ffdda7b_fa7c_49d2_85d8_d5641f070cc4

#ifndef	__cplusplus
#error	"Including C++ header in C translation unit!"
#endif	/* __cplusplus */

#include "prerequisites.hpp"
#include "boundingbox.hpp"

/**
 * @file
 * @brief The @c class Plane.
 * This file contains the @c class Plane.
 */
namespace eternal_lands
{

	/**
	 * Different types of intersection.
	 * @{
	 */
	enum IntersectionType
	{
		it_inside = 0,
		it_intersect = 1,
		it_outside = 2
	};
	/**
	 * @}
	 */

	/**
	 * @brief Simple plane.
	 *
	 * Simple plane.
	 */
	class Plane
	{
		private:
			glm::vec4 m_normal_and_distance;

			void set_distance(const float distance)
			{
				m_normal_and_distance.w = distance;
			}

			void recalculate_distance(const glm::vec3 &point)
			{
				set_distance(-glm::dot(point, get_normal()));
			}

			void set_normal(const glm::vec3 &normal)
			{
				glm::vec3 tmp;

				tmp = glm::normalize(normal);

				m_normal_and_distance = glm::vec4(tmp, get_distance());
			}

			void set_data(const glm::vec4 &data)
			{
				glm::vec3 normal;

				normal = glm::vec3(data);

				set_normal(normal);

				set_distance(data.w / glm::length(normal));
			}

		public:
			/**
			 * @brief Default constructor.
			 *
			 * Default constructor. Sets all values to zero
			 */
			Plane();
			Plane(const glm::vec3 &point, const glm::vec3 &dir);
			Plane(const glm::vec3 &dir, const float distance);
			Plane(const glm::vec4 &data);

			/**
			 * Default destructor.
			 */
			~Plane() throw();

			inline const glm::vec4 &get_data() const
			{
				return m_normal_and_distance;
			}

			inline glm::vec3 get_normal() const
			{
				return glm::vec3(m_normal_and_distance);
			}

			inline glm::vec3 get_abs_normal() const
			{
				return glm::abs(get_normal());
			}

			inline float get_distance() const
			{
				return m_normal_and_distance.w;
			}

			/**
			 * Gets a member point of the plane.
			 */
			inline glm::vec3 get_member_point() const
			{
				return get_normal() * -get_distance();
			}

			inline float get_distance(const glm::vec3 &point) const
			{
				return glm::dot(get_normal(), point) + get_distance();
			}

			inline IntersectionType intersect(const glm::vec3 &point) const
			{
				float dist;

				dist = get_distance(point);

				if (dist < 0.0f)
				{
					return it_outside;
				}
				else
				{
					if (dist > 0.0f)
					{
						return it_inside;
					}
					else
					{
						return it_intersect;
					}
				}
			}

			inline IntersectionType intersect(const BoundingBox &box) const
			{
				float dist, size;

				dist = get_distance(box.get_center());

				size = glm::dot(get_abs_normal(), box.get_half_size());

				if (dist < -size)
				{
					return it_outside;
				}
				else
				{
					if (dist > size)
					{
						return it_inside;
					}
					else
					{
						return it_intersect;
					}
				}
			}

			/**
			 * @brief Gets a transformed plane.
			 *
			 * Returns the transformed plane using the given matrix.
			 * @param matrix The transform matrix.
			 * @return The transformed plane.
			 */
			Plane transform(const glm::mat4 &matrix) const;

	};

}

#endif	/* UUID_2ffdda7b_fa7c_49d2_85d8_d5641f070cc4 */
