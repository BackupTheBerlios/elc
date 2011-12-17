#define BOOST_TEST_MODULE rstartreenode test
#include <boost/test/unit_test.hpp>
#include "rstartreenode.hpp"

using namespace eternal_lands;

namespace
{

	class RStarTreeNodeTest: public RStarTreeNode
	{
		public:
			RStarTreeNodeTest(const Uint32 level);
			~RStarTreeNodeTest() throw();

			using RStarTreeNode::get_element;
			using RStarTreeNode::set_element;
			using RStarTreeNode::get_node;
			using RStarTreeNode::check_index;
			using RStarTreeNode::get_element_bounding_box;
			using RStarTreeNode::add_element;
			using RStarTreeNode::add_node;
			using RStarTreeNode::remove_element;
			using RStarTreeNode::intersect_node;
			using RStarTreeNode::intersect_tree;
			using RStarTreeNode::get_item_count;
			using RStarTreeNode::find_leaf;
			using RStarTreeNode::choose_sub_tree;
			using RStarTreeNode::insert;
			using RStarTreeNode::find_least_overlap;
			using RStarTreeNode::find_least_enlargement;
			using RStarTreeNode::update_enclosing_bounding_box;
			using RStarTreeNode::split;
			using RStarTreeNode::adjust_tree;
			using RStarTreeNode::reinsert_elements;
			using RStarTreeNode::find_element;
			using RStarTreeNode::get_index;
			using RStarTreeNode::enclose;
			using RStarTreeNode::insert_element;
			using RStarTreeNode::delete_element;
			using RStarTreeNode::clear;

	};

	RStarTreeNodeTest::RStarTreeNodeTest(const Uint32 level): RStarTreeNode(level)
	{
	}

	RStarTreeNodeTest::~RStarTreeNodeTest() throw()
	{
	}

}

BOOST_AUTO_TEST_CASE(rstartreenode_create_test)
{
	RStarTreeNodeTest node1(0);
	RStarTreeNodeTest node2(7);

	BOOST_CHECK_EQUAL(node1.get_count(), 0);
	BOOST_CHECK_EQUAL(node1.get_level(), 0);
	BOOST_CHECK_EQUAL(node1.get_item_count(), 0);
	BOOST_CHECK(node1.get_leaf());

	BOOST_CHECK_EQUAL(node2.get_count(), 0);
	BOOST_CHECK_EQUAL(node2.get_level(), 7);
	BOOST_CHECK_EQUAL(node2.get_item_count(), 0);
	BOOST_CHECK(!node2.get_leaf());
}

BOOST_AUTO_TEST_CASE(rstartreenode_add_test)
{
	RStarTreeNodeTest node(0);
	std::vector<BoundedObject> elements;
	BoundedObject element;
	BoundingBox box;
	Uint32 i;

	for (i = 0; i < 16; i++)
	{
		box.set_min_max(glm::vec3(i), glm::vec3(i+1));
		element.set_bounding_box(box);

		elements.push_back(element);
	}

	for (i = 0; i < 8; i++)
	{
		BOOST_CHECK(node.add_element(&elements[i]));
		BOOST_CHECK_EQUAL(node.get_count(), i + 1);
	}

	for (i = 8; i < 16; i++)
	{
		BOOST_CHECK(!node.add_element(&elements[i]));
		BOOST_CHECK_EQUAL(node.get_count(), 8);
	}
}

BOOST_AUTO_TEST_CASE(rstartreenode_get_element_test)
{
	RStarTreeNodeTest node(0);
	std::vector<BoundedObject> elements;
	BoundedObject element;
	BoundingBox box;
	Uint32 i;

	for (i = 0; i < 8; i++)
	{
		box.set_min_max(glm::vec3(i), glm::vec3(i+1));
		element.set_bounding_box(box);

		elements.push_back(element);
	}

	for (i = 0; i < 8; i++)
	{
		BOOST_CHECK(node.add_element(&elements[i]));
	}

	for (i = 0; i < 8; i++)
	{
		BOOST_CHECK_EQUAL(node.get_element(i), &elements[i]);
	}
}

BOOST_AUTO_TEST_CASE(rstartreenode_set_element_test)
{
	RStarTreeNodeTest node(0);
	std::vector<BoundedObject> elements;
	BoundedObject element;
	BoundingBox box;
	Uint32 i;

	for (i = 0; i < 16; i++)
	{
		box.set_min_max(glm::vec3(i), glm::vec3(i+1));
		element.set_bounding_box(box);

		elements.push_back(element);
	}

	for (i = 0; i < 8; i++)
	{
		BOOST_CHECK(node.add_element(&elements[i]));
	}

	for (i = 0; i < 8; i++)
	{
		BOOST_CHECK_NO_THROW(node.set_element(&elements[i + 8], i));
	}

	for (i = 0; i < 8; i++)
	{
		BOOST_CHECK_EQUAL(node.get_element(i), &elements[i + 8]);
	}
}

BOOST_AUTO_TEST_CASE(rstartreenode_remove_test)
{
	RStarTreeNodeTest node(0);
	std::vector<BoundedObject> elements;
	BoundedObject element;
	BoundedObjectPtr element_ptr;
	BoundingBox box;
	Uint32 i, j;

	for (i = 0; i < 8; i++)
	{
		box.set_min_max(glm::vec3(i), glm::vec3(i+1));
		element.set_bounding_box(box);

		elements.push_back(element);
	}

	for (i = 0; i < 8; i++)
	{
		BOOST_CHECK(node.add_element(&elements[i]));
	}

	for (i = 0; i < 8; i++)
	{
		element_ptr = node.get_element(0);

		BOOST_CHECK_NO_THROW(node.remove_element(0));

		for (j = 0; j < node.get_count(); j++)
		{
			BOOST_CHECK_NE(node.get_element(j), element_ptr);
		}

		BOOST_CHECK_EQUAL(node.get_count(), 7 - i);
	}
}

BOOST_AUTO_TEST_CASE(rstartreenode_check_index_test)
{
	RStarTreeNodeTest node(0);
	std::vector<BoundedObject> elements;
	BoundedObject element;
	BoundingBox box;
	Uint32 i, j;

	for (i = 0; i < 8; i++)
	{
		box.set_min_max(glm::vec3(i), glm::vec3(i+1));
		element.set_bounding_box(box);

		elements.push_back(element);
	}

	for (i = 0; i < 8; i++)
	{
		for (j = i; j < 16; j++)
		{
			BOOST_CHECK(!node.check_index(j));
		}

		BOOST_CHECK(node.add_element(&elements[i]));

		for (j = 0; j < (i + 1); j++)
		{
			BOOST_CHECK(node.check_index(j));
		}
	}
}

BOOST_AUTO_TEST_CASE(rstartreenode_get_element_bounding_box_test)
{
	RStarTreeNodeTest node(0);
	std::vector<BoundedObject> elements;
	BoundedObject element;
	BoundingBox box;
	Uint32 i, j;

	for (i = 0; i < 8; i++)
	{
		box.set_min_max(glm::vec3(i), glm::vec3(i+1));
		element.set_bounding_box(box);

		elements.push_back(element);
	}

	for (i = 0; i < 8; i++)
	{
		BOOST_CHECK(node.add_element(&elements[i]));
	}

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 3; j++)
		{
			BOOST_CHECK_CLOSE(node.get_element_bounding_box(i).get_center()[j],
				elements[i].get_bounding_box().get_center()[j], 0.001);
			BOOST_CHECK_CLOSE(node.get_element_bounding_box(i).get_half_size()[j],
				elements[i].get_bounding_box().get_half_size()[j], 0.001);
		}
	}
}

BOOST_AUTO_TEST_CASE(rstartreenode_update_enclosing_bounding_box_test)
{
	RStarTreeNodeTest node(0);
	std::vector<BoundedObject> elements;
	BoundedObject element;
	BoundingBox box;
	Uint32 i;

	for (i = 0; i < 8; i++)
	{
		box.set_min_max(glm::vec3(i), glm::vec3(i+1));
		element.set_bounding_box(box);

		elements.push_back(element);
	}

	for (i = 0; i < 8; i++)
	{
		BOOST_CHECK(node.add_element(&elements[i]));
	}

	BOOST_CHECK_NO_THROW(node.update_enclosing_bounding_box());

	for (i = 0; i < 8; i++)
	{
		BOOST_CHECK(node.get_bounding_box().contains(
			node.get_element_bounding_box(i)));
	}
}

BOOST_AUTO_TEST_CASE(rstartreenode_find_element_test)
{
	RStarTreeNodeTest node(0);
	std::vector<BoundedObject> elements;
	BoundedObject element;
	BoundingBox box;
	Uint32 i, j;

	for (i = 0; i < 16; i++)
	{
		box.set_min_max(glm::vec3(i), glm::vec3(i+1));
		element.set_bounding_box(box);

		elements.push_back(element);
	}

	for (i = 0; i < 8; i++)
	{
		for (j = i; j < 16; j++)
		{
			BOOST_CHECK_EQUAL(node.find_element(&elements[j]), -1);
		}

		BOOST_CHECK(node.add_element(&elements[i]));

		for (j = 0; j < (i + 1); j++)
		{
			BOOST_CHECK_EQUAL(node.find_element(&elements[j]), j);
		}
	}
}

BOOST_AUTO_TEST_CASE(rstartreenode_get_index_test)
{
	RStarTreeNodeTest node(0);
	std::vector<BoundedObject> elements;
	BoundedObject element;
	BoundingBox box;
	Uint32 i, j;

	for (i = 0; i < 16; i++)
	{
		box.set_min_max(glm::vec3(i), glm::vec3(i+1));
		element.set_bounding_box(box);

		elements.push_back(element);
	}

	for (i = 0; i < 8; i++)
	{
		for (j = i; j < 16; j++)
		{
			BOOST_CHECK_THROW(node.get_index(&elements[j]), ItemNotFoundException);
		}

		BOOST_CHECK(node.add_element(&elements[i]));

		for (j = 0; j < (i + 1); j++)
		{
			BOOST_CHECK_EQUAL(node.get_index(&elements[j]), j);
		}
	}
}

BOOST_AUTO_TEST_CASE(rstartreenode_find_leaf_test)
{
	RStarTreeNodeTest node0(0);
	RStarTreeNodeTest node1(0);
	RStarTreeNodeTest node2(1);
	RStarTreeNodePtrStack path_buffer;
	std::vector<BoundedObject> elements;
	BoundedObject element;
	BoundingBox box;
	Uint32 i;

	for (i = 0; i < 16; i++)
	{
		box.set_min_max(glm::vec3(i), glm::vec3(i+1));
		element.set_bounding_box(box);

		elements.push_back(element);
	}

	for (i = 0; i < 8; i++)
	{
		BOOST_CHECK(node0.add_element(&elements[i]));
		BOOST_CHECK(node1.add_element(&elements[i + 8]));
	}

	BOOST_CHECK_NO_THROW(node0.update_enclosing_bounding_box());
	BOOST_CHECK_NO_THROW(node1.update_enclosing_bounding_box());

	BOOST_CHECK(node2.add_element(&node0));
	BOOST_CHECK(node2.add_element(&node1));

	BOOST_CHECK_NO_THROW(node2.update_enclosing_bounding_box());

	for (i = 0; i < 8; i++)
	{
		BOOST_CHECK_EQUAL(node2.find_leaf(&elements[i], path_buffer), &node0);
		BOOST_CHECK_EQUAL(path_buffer.size(), 1);
		BOOST_CHECK_EQUAL(path_buffer.top(), &node2);
		path_buffer.pop();

		BOOST_CHECK_EQUAL(node2.find_leaf(&elements[i + 8], path_buffer), &node1);
		BOOST_CHECK_EQUAL(path_buffer.size(), 1);
		BOOST_CHECK_EQUAL(path_buffer.top(), &node2);
		path_buffer.pop();
	}
}

BOOST_AUTO_TEST_CASE(rstartreenode_find_least_overlap_test)
{
	RStarTreeNodeTest node0(0);
	RStarTreeNodeTest node1(0);
	RStarTreeNodeTest node2(1);
	RStarTreeNodePtrStack path_buffer;
	std::vector<BoundedObject> elements;
	BoundedObject element;
	BoundingBox box;
	Uint32 i;

	for (i = 0; i < 16; i++)
	{
		box.set_min_max(glm::vec3(i), glm::vec3(i+1));
		element.set_bounding_box(box);

		elements.push_back(element);
	}

	BOOST_CHECK(node0.add_element(&elements[0]));
	BOOST_CHECK(node0.add_element(&elements[7]));
	BOOST_CHECK(node1.add_element(&elements[8]));
	BOOST_CHECK(node1.add_element(&elements[15]));

	BOOST_CHECK_NO_THROW(node0.update_enclosing_bounding_box());
	BOOST_CHECK_NO_THROW(node1.update_enclosing_bounding_box());

	BOOST_CHECK(node2.add_element(&node0));
	BOOST_CHECK(node2.add_element(&node1));

	BOOST_CHECK_NO_THROW(node2.update_enclosing_bounding_box());

	for (i = 1; i < 7; i++)
	{
		BOOST_CHECK_EQUAL(node2.find_least_overlap(elements[i].get_bounding_box()), &node0);
		BOOST_CHECK_EQUAL(node2.find_least_overlap(elements[i + 8].get_bounding_box()), &node1);
	}
}

BOOST_AUTO_TEST_CASE(rstartreenode_find_least_enlargement_test)
{
	RStarTreeNodeTest node0(0);
	RStarTreeNodeTest node1(0);
	RStarTreeNodeTest node2(1);
	RStarTreeNodePtrStack path_buffer;
	std::vector<BoundedObject> elements;
	BoundedObject element;
	BoundingBox box;
	Uint32 i;

	for (i = 0; i < 16; i++)
	{
		box.set_min_max(glm::vec3(i), glm::vec3(i+1));
		element.set_bounding_box(box);

		elements.push_back(element);
	}

	BOOST_CHECK(node0.add_element(&elements[0]));
	BOOST_CHECK(node1.add_element(&elements[15]));

	BOOST_CHECK_NO_THROW(node0.update_enclosing_bounding_box());
	BOOST_CHECK_NO_THROW(node1.update_enclosing_bounding_box());

	BOOST_CHECK(node2.add_element(&node0));
	BOOST_CHECK(node2.add_element(&node1));

	BOOST_CHECK_NO_THROW(node2.update_enclosing_bounding_box());

	for (i = 1; i < 8; i++)
	{
		BOOST_CHECK_EQUAL(node2.find_least_enlargement(elements[i].get_bounding_box()), &node0);
		BOOST_CHECK_EQUAL(node2.find_least_enlargement(elements[i + 7].get_bounding_box()), &node1);
	}
}
