#define BOOST_TEST_MODULE rstartree test
#include <boost/test/unit_test.hpp>
#include "rstartree.hpp"
#include <iostream>

using namespace eternal_lands;

namespace
{

	class RStarTreeTest: public RStarTree
	{
		public:
			RStarTreeTest();
			~RStarTreeTest() throw();

			using RStarTree::valid_factor;
			using RStarTree::delete_node;
			using RStarTree::set_root_node;
			using RStarTree::new_node;
			using RStarTree::add_new_root_node;
			using RStarTree::get_root_node;
			using RStarTree::add_data;
			using RStarTree::condense_tree;
			using RStarTree::reinsert_nodes;
			using RStarTree::clear;

	};

	RStarTreeTest::RStarTreeTest()
	{
	}

	RStarTreeTest::~RStarTreeTest() throw()
	{
	}

}

BOOST_AUTO_TEST_CASE(rstartree_test)
{
	RStarTreeTest tree;
}

BOOST_AUTO_TEST_CASE(rstartree_add_test)
{
	RStarTreeTest tree;
	std::vector<BoundedObject> elements;
	BoundedObject element;
	BoundingBox box;
	Uint32 i;

	for (i = 0; i < 1024; i++)
	{
		box.set_min_max(glm::vec3(i), glm::vec3(i+1));
		element.set_bounding_box(box);

		elements.push_back(element);
	}

	for (i = 0; i < 1024; i++)
	{
		BOOST_CHECK_NO_THROW(tree.add(&elements[i]));

		BOOST_CHECK_CLOSE(tree.get_bounding_box().get_center()[0], (i + 1) * 0.5, 0.1);
		BOOST_CHECK_CLOSE(tree.get_bounding_box().get_center()[1], (i + 1) * 0.5, 0.1);
		BOOST_CHECK_CLOSE(tree.get_bounding_box().get_center()[2], (i + 1) * 0.5, 0.1);
		BOOST_CHECK_CLOSE(tree.get_bounding_box().get_half_size()[0], (i + 1) * 0.5, 0.1);
		BOOST_CHECK_CLOSE(tree.get_bounding_box().get_half_size()[1], (i + 1) * 0.5, 0.1);
		BOOST_CHECK_CLOSE(tree.get_bounding_box().get_half_size()[2], (i + 1) * 0.5, 0.1);

		BOOST_CHECK(tree.check_tree());
	}
}

BOOST_AUTO_TEST_CASE(rstartree_remove_test)
{
	RStarTree tree;
	std::vector<BoundedObject> elements;
	BoundedObject element;
	BoundingBox box;
	Uint32 i;

	for (i = 0; i < 1024; i++)
	{
		box.set_min_max(glm::vec3(i), glm::vec3(i+1));
		element.set_bounding_box(box);

		elements.push_back(element);
	}

	for (i = 0; i < 1024; i++)
	{
		BOOST_CHECK_NO_THROW(tree.add(&elements[i]));
	}

	for (i = 0; i < 1024; i++)
	{
		BOOST_CHECK_NO_THROW(tree.remove(&elements[i]));	

		BOOST_CHECK(tree.check_tree());
	}
}

BOOST_AUTO_TEST_CASE(rstartree_intersect_test)
{
	RStarTree tree;
	std::vector<BoundedObject> elements;
	BoundedObject element;
	BoundingBox box;
	Uint32 i;

	for (i = 0; i < 65536; i++)
	{
		box.set_min_max(glm::vec3(i), glm::vec3(i+1));
		element.set_bounding_box(box);

		elements.push_back(element);
	}

	for (i = 0; i < 65536; i++)
	{
		BOOST_CHECK_NO_THROW(tree.add(&elements[i]));
	}
}
