/***************************************************************************
 *            rstartree.cpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#include "rstartree.hpp"

namespace eternal_lands
{

	void RStarTree::delete_node(const RStarTreeNodePtr &node)
	{
		node->~RStarTreeNode();
		m_pool.free(node);
	}

	void RStarTree::set_root_node(const RStarTreeNodePtr &node)
	{
		delete_node(m_root_node);

		m_root_node = node;
	}

	RStarTreeNodePtr RStarTree::new_node(const Uint32 level)
	{
		assert(level < 32);

		return new(m_pool.malloc()) RStarTreeNode(level);
	}

	RStarTreeNodePtr RStarTree::add_new_root_node(const Uint32 level)
	{
		m_root_node = new_node(level);

		return m_root_node;
	}

	void RStarTree::clear(const RStarTreeNodePtr &node)
	{
		Uint32 i;

		if (!node->get_leaf())
		{
			for (i = 0; i < node->get_count(); i++)
			{
				clear(node->get_node(i));
			}
		}

		delete_node(node);
	}

	bool RStarTree::valid_factor(const float factor) const throw ()
	{
		return ((factor >= 0.0f) && (factor <= 1.0f));
	}

	void RStarTree::add_data(const BoundedObjectPtr element,
		const Uint32 level, _32BitSet &oft)
	{
		RStarTreeNodePtrStack path_buffer;
		RStarTreeNodePtr node;

		node = get_root_node()->choose_sub_tree(
			element->get_bounding_box(), level, path_buffer);

		node->insert_element(this, element, path_buffer, oft);
	}

	RStarTreeNodePtr RStarTree::condense_tree(
		RStarTreeNodePtrVector &reinsert,
		RStarTreeNodePtrStack &path_buffer,
		const RStarTreeNodePtr node)
	{
		RStarTreeNodePtr parent;
		Uint32 minimum_load, index;

		minimum_load = node->get_max_count() * get_fill_factor();

		if (path_buffer.empty())
		{
			if (!node->get_leaf() && (node->get_count() == 1))
			{
				return node->get_node(0);
			}
			else
			{
				return 0;
			}
		}
		else
		{
			parent = path_buffer.top();
			path_buffer.pop();

			if (node->get_count() <= minimum_load)
			{
				index = parent->get_index(node);

				parent->remove_element(index);

				reinsert.push_back(node);

				parent->update_enclosing_bounding_box();
			}
			else
			{
				node->update_enclosing_bounding_box();
			}

			return condense_tree(reinsert, path_buffer, parent);
		}
	}

	void RStarTree::reinsert_nodes(const RStarTreeNodePtrVector &reinsert)
	{
		_32BitSet oft;
		Uint32 i, count;

		BOOST_FOREACH(const RStarTreeNodePtr node, reinsert)
		{
			count = node->get_count();

			for (i = 0; i < count; i++)
			{
				oft.reset();
				add_data(node->get_element(i),
					node->get_level(), oft);

				assert(count == node->get_count());
			}

			delete_node(node);
		}
	}

	RStarTree::RStarTree(): m_pool(sizeof(RStarTreeNode))
	{
		m_split_distribution_factor = 0.4f;
		m_reinsert_factor = 0.6f;
		m_fill_factor = 0.7f;

		add_new_root_node(0);
	}

	RStarTree::~RStarTree() throw()
	{
		clear(m_root_node);
	}

	void RStarTree::set_split_distribution_factor(const float value)
	{
		if (!valid_factor(value))
		{
			EL_THROW_EXCEPTION(RangeErrorException()
				<< errinfo_float_range_min(0.0f)
				<< errinfo_float_range_max(1.0f)
				<< errinfo_float_range_index(value));
		}
		else
		{
			m_split_distribution_factor = value;
		}
	}

	void RStarTree::set_reinsert_factor(const float value)
	{
		if (!valid_factor(value))
		{
			EL_THROW_EXCEPTION(RangeErrorException()
				<< errinfo_float_range_min(0.0f)
				<< errinfo_float_range_max(1.0f)
				<< errinfo_float_range_index(value));
		}
		else
		{
			m_reinsert_factor = value;
		}
	}

	void RStarTree::set_fill_factor(const float value)
	{
		if (!valid_factor(value))
		{
			EL_THROW_EXCEPTION(RangeErrorException()
				<< errinfo_float_range_min(0.0f)
				<< errinfo_float_range_max(1.0f)
				<< errinfo_float_range_index(value));
		}
		else
		{
			m_fill_factor = value;
		}
	}

	void RStarTree::add(const BoundedObjectPtr element)
	{
		RStarTreeNodePtrStack path_buffer;
		RStarTreeNodePtr node;
		_32BitSet oft;

		if (element == 0)
		{
			EL_THROW_EXCEPTION(NullPtrException());
		}

		if (!get_root_node()->insert(element))
		{
			oft.reset();

			node = get_root_node()->choose_sub_tree(
				element->get_bounding_box(), 0, path_buffer);

			assert(node);

			node->insert_element(this, element, path_buffer, oft);
		}
		else
		{
			get_root_node()->update_enclosing_bounding_box();
		}
	}

	void RStarTree::remove(const BoundedObjectPtr element)
	{
		RStarTreeNodePtrStack path_buffer;
		RStarTreeNodePtrVector reinsert;
		RStarTreeNodePtr node;

		if (element == 0)
		{
			EL_THROW_EXCEPTION(NullPtrException());
		}

		node = get_root_node()->find_leaf(element, path_buffer);

		if (node == 0)
		{
			EL_THROW_EXCEPTION(ItemNotFoundException());
		}

		node->delete_element(element);

		node = condense_tree(reinsert, path_buffer, node);

		if (node)
		{
			set_root_node(node);
		}

		reinsert_nodes(reinsert);

		if (get_root_node()->get_count() > 0)
		{
			get_root_node()->update_enclosing_bounding_box();
		}
		else
		{
			get_root_node()->set_bounding_box(BoundingBox(
				glm::vec3(0.0f), glm::vec3(0.0f)));
		}
	}

	Uint32 RStarTree::optimize(const Uint32 count)
	{
		Uint32 minimum_load, i;

		minimum_load = get_root_node()->get_max_count() * m_fill_factor;

		for (i = 0; i < count; i++)
		{
			RStarTreeNodePtrStack path_buffer;
			RStarTreeNodePtrVector reinsert;
			RStarTreeNodePtr node;

			node = get_root_node()->find_small_leaf(minimum_load,
				path_buffer);

			if (node == 0)
			{
				return i;
			}

			node = condense_tree(reinsert, path_buffer, node);

			if (node)
			{
				set_root_node(node);
			}
			else
			{
				get_root_node()->update_enclosing_bounding_box();
			}

			reinsert_nodes(reinsert);
		}

		return count;
	}

	void RStarTree::intersect(const Frustum &frustum,
		BoundedObjectPtrVector &visitor) const
	{
		get_root_node()->intersect_tree(frustum, frustum.get_mask(),
			visitor);
	}

	void RStarTree::clear()
	{
		clear(m_root_node);

		add_new_root_node(0);
	}

	Uint32 RStarTree::get_max_elements_per_node() throw()
	{
		return RStarTreeNode::get_max_count();
	}

	const BoundingBox &RStarTree::get_bounding_box() const
	{
		return get_root_node()->get_bounding_box();
	}

	Uint32 RStarTree::get_nodes_count() const throw()
	{
		return get_root_node()->get_sub_nodes_count() + 1;
	}

	bool RStarTree::get_empty() const
	{
		return get_root_node()->get_count() == 0;
	}

	Uint32 RStarTree::get_memory_usage() const throw()
	{
		return sizeof(RStarTree) + get_nodes_count() *
			sizeof(RStarTreeNode);
	}

	bool RStarTree::check_tree() const
	{
		return get_root_node()->check_nodes();
	}

}
