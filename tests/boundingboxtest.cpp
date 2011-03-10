#define BOOST_TEST_MODULE boundingbox test
#include <boost/test/unit_test.hpp>
#include "boundingbox.hpp"
#include "exceptions.hpp"

using namespace eternal_lands;

BOOST_AUTO_TEST_CASE(boundingbox_creation_test)
{
	BoundingBox box(glm::vec3(1, 2, 4), glm::vec3(6, 3, 16));

	BOOST_CHECK_CLOSE(box.get_min()[0], 1.0, 0.0001);
	BOOST_CHECK_CLOSE(box.get_min()[1], 2.0, 0.0001);
	BOOST_CHECK_CLOSE(box.get_min()[2], 4.0, 0.0001);
	BOOST_CHECK_CLOSE(box.get_max()[0], 6.0, 0.0001);
	BOOST_CHECK_CLOSE(box.get_max()[1], 3.0, 0.0001);
	BOOST_CHECK_CLOSE(box.get_max()[2], 16.0, 0.0001);

	BOOST_CHECK_CLOSE(box.get_half_size()[0], 2.5, 0.0001);
	BOOST_CHECK_CLOSE(box.get_half_size()[1], 0.5, 0.0001);
	BOOST_CHECK_CLOSE(box.get_half_size()[2], 6.0, 0.0001);
	BOOST_CHECK_CLOSE(box.get_center()[0], 3.5, 0.0001);
	BOOST_CHECK_CLOSE(box.get_center()[1], 2.5, 0.0001);
	BOOST_CHECK_CLOSE(box.get_center()[2], 10.0, 0.0001);
}

BOOST_AUTO_TEST_CASE(boundingbox_volume_test)
{
	BoundingBox box(glm::vec3(1, 2, 4), glm::vec3(6, 3, 16));

	BOOST_CHECK_CLOSE(box.get_volume(), 60, 0.001);
}

BOOST_AUTO_TEST_CASE(boundingbox_margin_test)
{
	BoundingBox box(glm::vec3(1, 2, 4), glm::vec3(6, 3, 16));

	BOOST_CHECK_CLOSE(box.get_margin(), 18.0, 0.001);
}

BOOST_AUTO_TEST_CASE(boundingbox_merge_test)
{
	BoundingBox box1(glm::vec3(1, 2, 4), glm::vec3(6, 3, 16));
	BoundingBox box2(glm::vec3(5, 2, 1), glm::vec3(16, 13, 5));
	BoundingBox box3(glm::vec3(-6, -3, -16), glm::vec3(-1, -2, -4));
	BoundingBox box4(glm::vec3(-16, -13, -5), glm::vec3(-5, -2, -1));

	box2.merge(box1);

	BOOST_CHECK_CLOSE(box2.get_min()[0], 1.0, 0.0001);
	BOOST_CHECK_CLOSE(box2.get_min()[1], 2.0, 0.0001);
	BOOST_CHECK_CLOSE(box2.get_min()[2], 1.0, 0.0001);
	BOOST_CHECK_CLOSE(box2.get_max()[0], 16.0, 0.0001);
	BOOST_CHECK_CLOSE(box2.get_max()[1], 13.0, 0.0001);
	BOOST_CHECK_CLOSE(box2.get_max()[2], 16.0, 0.0001);

	BOOST_CHECK_CLOSE(box2.get_half_size()[0], 7.5, 0.0001);
	BOOST_CHECK_CLOSE(box2.get_half_size()[1], 5.5, 0.0001);
	BOOST_CHECK_CLOSE(box2.get_half_size()[2], 7.5, 0.0001);
	BOOST_CHECK_CLOSE(box2.get_center()[0], 8.5, 0.0001);
	BOOST_CHECK_CLOSE(box2.get_center()[1], 7.5, 0.0001);
	BOOST_CHECK_CLOSE(box2.get_center()[2], 8.5, 0.0001);

	box1.merge(box2);

	BOOST_CHECK_CLOSE(box1.get_min()[0], 1.0, 0.0001);
	BOOST_CHECK_CLOSE(box1.get_min()[1], 2.0, 0.0001);
	BOOST_CHECK_CLOSE(box1.get_min()[2], 1.0, 0.0001);
	BOOST_CHECK_CLOSE(box1.get_max()[0], 16.0, 0.0001);
	BOOST_CHECK_CLOSE(box1.get_max()[1], 13.0, 0.0001);
	BOOST_CHECK_CLOSE(box1.get_max()[2], 16.0, 0.0001);

	box4.merge(box3);

	BOOST_CHECK_CLOSE(box4.get_min()[0], -16.0, 0.0001);
	BOOST_CHECK_CLOSE(box4.get_min()[1], -13.0, 0.0001);
	BOOST_CHECK_CLOSE(box4.get_min()[2], -16.0, 0.0001);
	BOOST_CHECK_CLOSE(box4.get_max()[0], -1.0, 0.0001);
	BOOST_CHECK_CLOSE(box4.get_max()[1], -2.0, 0.0001);
	BOOST_CHECK_CLOSE(box4.get_max()[2], -1.0, 0.0001);

	BOOST_CHECK_CLOSE(box4.get_half_size()[0], 7.5, 0.0001);
	BOOST_CHECK_CLOSE(box4.get_half_size()[1], 5.5, 0.0001);
	BOOST_CHECK_CLOSE(box4.get_half_size()[2], 7.5, 0.0001);
	BOOST_CHECK_CLOSE(box4.get_center()[0], -8.5, 0.0001);
	BOOST_CHECK_CLOSE(box4.get_center()[1], -7.5, 0.0001);
	BOOST_CHECK_CLOSE(box4.get_center()[2], -8.5, 0.0001);

	box3.merge(box4);

	BOOST_CHECK_CLOSE(box3.get_min()[0], -16.0, 0.0001);
	BOOST_CHECK_CLOSE(box3.get_min()[1], -13.0, 0.0001);
	BOOST_CHECK_CLOSE(box3.get_min()[2], -16.0, 0.0001);
	BOOST_CHECK_CLOSE(box3.get_max()[0], -1.0, 0.0001);
	BOOST_CHECK_CLOSE(box3.get_max()[1], -2.0, 0.0001);
	BOOST_CHECK_CLOSE(box3.get_max()[2], -1.0, 0.0001);
}

BOOST_AUTO_TEST_CASE(boundingbox_overlap_test)
{
	BoundingBox box1(glm::vec3(1, 2, 4), glm::vec3(6, 3, 16));
	BoundingBox box2(glm::vec3(5, 2, 1), glm::vec3(16, 13, 5));
	BoundingBox box3(glm::vec3(7, 2, 17), glm::vec3(17, 13, 25));
	BoundingBox box4(glm::vec3(-1, -2, -4), glm::vec3(6, 3, 16));

	BOOST_CHECK_CLOSE(box1.overlap(box2), 1.0, 0.001);
	BOOST_CHECK_CLOSE(box2.overlap(box1), 1.0, 0.001);

	BOOST_CHECK_CLOSE(box1.overlap(box3), 0.0, 0.001);
	BOOST_CHECK_CLOSE(box2.overlap(box3), 0.0, 0.001);
	BOOST_CHECK_CLOSE(box3.overlap(box1), 0.0, 0.001);
	BOOST_CHECK_CLOSE(box3.overlap(box2), 0.0, 0.001);

	BOOST_CHECK_CLOSE(box1.overlap(box4), 60.0, 0.001);
	BOOST_CHECK_CLOSE(box2.overlap(box4), 9.0, 0.001);
	BOOST_CHECK_CLOSE(box3.overlap(box4), 0.0, 0.001);
	BOOST_CHECK_CLOSE(box4.overlap(box1), 60.0, 0.001);
	BOOST_CHECK_CLOSE(box4.overlap(box2), 9.0, 0.001);
	BOOST_CHECK_CLOSE(box4.overlap(box3), 0.0, 0.001);
}

BOOST_AUTO_TEST_CASE(boundingbox_contains_test)
{
	BoundingBox box1(glm::vec3(1, 2, 4), glm::vec3(6, 7, 16));
	BoundingBox box2(glm::vec3(2, 3, 5), glm::vec3(5, 6, 15));

	BOOST_CHECK(box1.contains(box2));
}

BOOST_AUTO_TEST_CASE(boundingbox_min_max_test)
{
	BoundingBox box;

	BOOST_CHECK_THROW(box.set_min_max(glm::vec3(2.0f), glm::vec3(1.0f)),
		RangeErrorException);

	BOOST_CHECK_THROW(box.set_min_max(glm::vec3(3.0f, 1.0f, 1.0f),
		glm::vec3(2.0f, 2.0f, 2.0f)), RangeErrorException);

	BOOST_CHECK_THROW(box.set_min_max(glm::vec3(1.0f, 3.0f, 1.0f),
		glm::vec3(2.0f, 2.0f, 2.0f)), RangeErrorException);

	BOOST_CHECK_THROW(box.set_min_max(glm::vec3(1.0f, 1.0f, 3.0f),
		glm::vec3(2.0f, 2.0f, 2.0f)), RangeErrorException);

	BOOST_CHECK_THROW(box.set_min_max(glm::vec3(1.0f, 3.0f, 3.0f),
		glm::vec3(2.0f, 2.0f, 2.0f)), RangeErrorException);

	BOOST_CHECK_THROW(box.set_min_max(glm::vec3(3.0f, 1.0f, 3.0f),
		glm::vec3(2.0f, 2.0f, 2.0f)), RangeErrorException);

	BOOST_CHECK_THROW(box.set_min_max(glm::vec3(3.0f, 3.0f, 1.0f),
		glm::vec3(2.0f, 2.0f, 2.0f)), RangeErrorException);
}

BOOST_AUTO_TEST_CASE(boundingbox_half_size_test)
{
	BoundingBox box;

	box.set_half_size(glm::vec3(1, 2, 4));

	BOOST_CHECK_CLOSE(box.get_half_size()[0], 1.0, 0.0001);
	BOOST_CHECK_CLOSE(box.get_half_size()[1], 2.0, 0.0001);
	BOOST_CHECK_CLOSE(box.get_half_size()[2], 4.0, 0.0001);

	BOOST_CHECK_THROW(box.set_half_size(glm::vec3(-1.0f)),
		RangeErrorException);

	BOOST_CHECK_THROW(box.set_half_size(glm::vec3(-1.0f, 1.0f, 1.0f)),
		RangeErrorException);

	BOOST_CHECK_THROW(box.set_half_size(glm::vec3(1.0f, -1.0f, 1.0f)),
		RangeErrorException);

	BOOST_CHECK_THROW(box.set_half_size(glm::vec3(1.0f, 1.0f, -1.0f)),
		RangeErrorException);

	BOOST_CHECK_THROW(box.set_half_size(glm::vec3(1.0f, -1.0f, -1.0f)),
		RangeErrorException);

	BOOST_CHECK_THROW(box.set_half_size(glm::vec3(-1.0f, 1.0f, -1.0f)),
		RangeErrorException);

	BOOST_CHECK_THROW(box.set_half_size(glm::vec3(-1.0f, -1.0f, 1.0f)),
		RangeErrorException);
}

BOOST_AUTO_TEST_CASE(boundingbox_scale_test)
{
	BoundingBox box(glm::vec3(1, 2, 4), glm::vec3(6, 7, 16));
	
	box.scale(2.0f);
	
	BOOST_CHECK_CLOSE(box.get_half_size()[0], 5.0, 0.0001);
	BOOST_CHECK_CLOSE(box.get_half_size()[1], 5.0, 0.0001);
	BOOST_CHECK_CLOSE(box.get_half_size()[2], 12.0, 0.0001);
	BOOST_CHECK_CLOSE(box.get_center()[0], 3.5, 0.0001);
	BOOST_CHECK_CLOSE(box.get_center()[1], 4.5, 0.0001);
	BOOST_CHECK_CLOSE(box.get_center()[2], 10.0, 0.0001);
}

BOOST_AUTO_TEST_CASE(boundingbox_transform_test)
{
	BoundingBox box1(glm::vec3(1, 2, 4), glm::vec3(6, 7, 16));
	BoundingBox box2;
	glm::mat4 matrix;

	matrix = glm::rotate(30.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	matrix = glm::rotate(matrix, 70.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	matrix = glm::rotate(matrix, 120.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	matrix = glm::scale(matrix, glm::vec3(0.5f, 0.25f, 2.0f));
	matrix[3] = glm::vec4(5.0f, 8.0f, 10.0f, 1.0f);

	box2 = box1.transform(matrix);

	BOOST_CHECK_CLOSE(box1.get_half_size()[0], 2.5, 0.0001);
	BOOST_CHECK_CLOSE(box1.get_half_size()[1], 2.5, 0.0001);
	BOOST_CHECK_CLOSE(box1.get_half_size()[2], 6.0, 0.0001);
	BOOST_CHECK_CLOSE(box1.get_center()[0], 3.5, 0.0001);
	BOOST_CHECK_CLOSE(box1.get_center()[1], 4.5, 0.0001);
	BOOST_CHECK_CLOSE(box1.get_center()[2], 10.0, 0.0001);

	BOOST_CHECK_CLOSE(box2.get_half_size()[0], 7.337, 0.1);
	BOOST_CHECK_CLOSE(box2.get_half_size()[1], 10.83, 0.1);
	BOOST_CHECK_CLOSE(box2.get_half_size()[2], 3.009, 0.1);
	BOOST_CHECK_CLOSE(box2.get_center()[0], 13.64, 0.1);
	BOOST_CHECK_CLOSE(box2.get_center()[1], 25.93, 0.1);
	BOOST_CHECK_CLOSE(box2.get_center()[2], 7.118, 0.1);
}
