#define BOOST_TEST_MODULE plane test
#include <boost/test/unit_test.hpp>
#include "plane.hpp"

using namespace eternal_lands;

BOOST_AUTO_TEST_CASE(plane_creation_test)
{
	Plane plane0;
	Plane plane1(glm::vec3(-1.0f, -1.0f, 0.0f), 2.0f);

	BOOST_CHECK_CLOSE(plane0.get_data()[0], 0.0, 0.1);
	BOOST_CHECK_CLOSE(plane0.get_data()[1], 0.0, 0.1);
	BOOST_CHECK_CLOSE(plane0.get_data()[2], 0.0, 0.1);
	BOOST_CHECK_CLOSE(plane0.get_data()[3], 0.0, 0.1);

	BOOST_CHECK_CLOSE(plane1.get_normal()[0], -std::sqrt(0.5f), 0.1);
	BOOST_CHECK_CLOSE(plane1.get_normal()[1], -std::sqrt(0.5f), 0.1);
	BOOST_CHECK_CLOSE(plane1.get_normal()[2], 0.0, 0.1);
	BOOST_CHECK_CLOSE(plane1.get_distance(), 2.0, 0.1);
	BOOST_CHECK_CLOSE(plane1.get_abs_normal()[0], std::sqrt(0.5f), 0.1);
	BOOST_CHECK_CLOSE(plane1.get_abs_normal()[1], std::sqrt(0.5f), 0.1);
	BOOST_CHECK_CLOSE(plane1.get_abs_normal()[2], 0.0, 0.1);
}

BOOST_AUTO_TEST_CASE(plane_member_point_test)
{
	Plane plane(glm::vec3(-1.0f, -1.0f, 0.0f), 2.0f);

	BOOST_CHECK_CLOSE(plane.get_member_point()[0], 2.0f * std::sqrt(0.5f), 0.1);
	BOOST_CHECK_CLOSE(plane.get_member_point()[1], 2.0f * std::sqrt(0.5f), 0.1);
	BOOST_CHECK_CLOSE(plane.get_member_point()[2], 0.0, 0.1);
}

BOOST_AUTO_TEST_CASE(plane_distance_test)
{
	Plane plane(glm::vec3(-1.0f, 1.0f, 2.0f), 2.0f);

	BOOST_CHECK_CLOSE(plane.get_distance(glm::vec3(1.0f)), 2.816f, 0.1);
}

BOOST_AUTO_TEST_CASE(plane_intersect_point_test)
{
	Plane plane(glm::vec3(-1.0f, 1.0f, 2.0f), 2.0f);

	BOOST_CHECK_EQUAL(plane.intersect(glm::vec3(1.0f)), it_inside);
	BOOST_CHECK_EQUAL(plane.intersect(glm::vec3(0.0f, -5.0f, 0.0f)), it_outside);
}

BOOST_AUTO_TEST_CASE(plane_intersect_box_test)
{
	Plane plane(glm::vec3(-1.0f, 1.0f, 2.0f), 2.0f);
	BoundingBox box1(glm::vec3(1.0f), glm::vec3(2.0f));
	BoundingBox box2(glm::vec3(-2.0f), glm::vec3(2.0f));
	BoundingBox box3(glm::vec3(-4.0f), glm::vec3(-3.0f));

	BOOST_CHECK_EQUAL(plane.intersect(box1), it_inside);
	BOOST_CHECK_EQUAL(plane.intersect(box2), it_intersect);
	BOOST_CHECK_EQUAL(plane.intersect(box3), it_outside);
}

BOOST_AUTO_TEST_CASE(plane_transform_test)
{
	Plane plane1(glm::vec3(-1.0f, 1.0f, 2.0f), 2.0f);
	Plane plane2;

	glm::mat4 matrix;

	matrix = glm::rotate(30.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	matrix = glm::rotate(matrix, 70.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	matrix = glm::rotate(matrix, 120.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	matrix = glm::scale(matrix, glm::vec3(0.5f, 0.25f, 2.0f));
	matrix[3] = glm::vec4(5.0f, 8.0f, 10.0f, 1.0f);

	plane2 = plane1.transform(matrix);

	BOOST_CHECK_CLOSE(plane1.get_normal()[0], -0.408, 0.1);
	BOOST_CHECK_CLOSE(plane1.get_normal()[1], 0.408, 0.1);
	BOOST_CHECK_CLOSE(plane1.get_normal()[2], 0.816, 0.1);
	BOOST_CHECK_CLOSE(plane1.get_distance(), 2.0, 0.1);
	BOOST_CHECK_CLOSE(plane2.get_normal()[0], 0.603, 0.1);
	BOOST_CHECK_CLOSE(plane2.get_normal()[1], 0.7938, 0.1);
	BOOST_CHECK_CLOSE(plane2.get_normal()[2], -0.07453, 0.1);
	BOOST_CHECK_CLOSE(plane2.get_distance(), -5.325, 0.1);
}
