/****************************************************************************
 *            rstartreenode.cpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#include "rstartreenode.hpp"
#include "rstartree.hpp"

namespace eternal_lands
{

	namespace
	{

		ARRAY(BoundedObjectPtr, 9);

		class BoundedObjectSplitCmp
		{
			private:
				const Uint32 m_index;

			public:
				BoundedObjectSplitCmp(const Uint32 index);

				bool operator()(const BoundedObjectPtr split_1,
					const BoundedObjectPtr split_2)
					const throw ();

		};

		BoundedObjectSplitCmp::BoundedObjectSplitCmp(const Uint32 index):
			m_index(index)
		{
		}

		bool BoundedObjectSplitCmp::operator()(
			const BoundedObjectPtr split_1,
			const BoundedObjectPtr split_2) const throw ()
		{
			Uint32 idx;

			idx = m_index % 3;

			if (m_index < 3)
			{
				return split_1->get_bounding_box().get_min()[idx] >
					split_2->get_bounding_box().get_min()[idx];
			}
			else
			{
				return split_1->get_bounding_box().get_max()[idx] >
					split_2->get_bounding_box().get_max()[idx];
			}
		}

		float split_margin(BoundedObjectPtrArray9 &split_data,
			const Sint32 min_index, const Sint32 max_index,
			const Uint32 index)
		{
			BoundingBox bounding_box;
			Sint32 i, size;
			float margin_value;

			std::sort(split_data.begin(), split_data.end(),
				BoundedObjectSplitCmp(index));

			size = split_data.size();

			margin_value = 0.0f;

			bounding_box = split_data[0]->get_bounding_box();

			for (i = 1; i < min_index; i++)
			{
				bounding_box.merge(
					split_data[i]->get_bounding_box());
			}

			for (i = min_index; i < max_index; i++)
			{
				margin_value += bounding_box.get_margin();

				bounding_box.merge(
					split_data[i]->get_bounding_box());
			}

			bounding_box = split_data[size - 1]->get_bounding_box();

			for (i = max_index; i < (size - 1); i++)
			{
				bounding_box.merge(
					split_data[i]->get_bounding_box());
			}

			for (i = max_index - 1; i > (min_index - 1); i--)
			{
				bounding_box.merge(
					split_data[i]->get_bounding_box());

				margin_value += bounding_box.get_margin();
			}

			return margin_value;
		}

		Sint32 split_array9(BoundedObjectPtrArray9 &split_data,
			const Uint32 min_size)
		{
			FloatArray6 margin;
			BoundingBox bounding_box_min, bounding_box_max;
			BoundingBox bounding_box;
			float overlap_tmp, min_overlap, dist, min_dist;
			Sint32 size, split_point, min_index, max_index, index;
			Sint32 i, j;
			Uint32 k;

			size = split_data.size();

			min_index = min_size;
			max_index = size - min_index;

			if ((max_index < min_index) || (min_index < 1) ||
				(max_index >= (size - 1)))
			{
				return -1;
			}

			if (max_index == min_index)
			{
				return min_index;
			}

			min_dist = std::numeric_limits<float>::max();
			min_overlap = std::numeric_limits<float>::max();
			split_point = -1;

			for (k = 0; k < margin.size(); k++)
			{
				margin[k] = split_margin(split_data, min_index,
					max_index, k);
			}

			index = 0;

			for (k = 1; k < margin.size(); k++)
			{
				if (margin[k] < margin[index])
				{
					index = k;
				}
			}

			std::sort(split_data.begin(), split_data.end(),
				BoundedObjectSplitCmp(index));

			bounding_box_min = split_data[0]->get_bounding_box();

			for (i = 1; i < min_index; i++)
			{
				bounding_box_min.merge(
					split_data[i]->get_bounding_box());
			}

			bounding_box_max =
				split_data[size - 1]->get_bounding_box();

			for (i = max_index; i < (size - 1); i++)
			{
				bounding_box_max.merge(
					split_data[i]->get_bounding_box());
			}

			for (i = min_index; i < max_index; i++)
			{
				bounding_box = bounding_box_max;

				for (j = i; j < max_index; j++)
				{
					bounding_box.merge(
						split_data[j]->get_bounding_box());
				}

				overlap_tmp = bounding_box.overlap(
					bounding_box_min);

				dist = std::abs((size - 1 ) * 0.5f - i);

				if ((overlap_tmp < min_overlap) ||
					((overlap_tmp == min_overlap) &&
					(dist < min_dist)))
				{
					min_overlap = overlap_tmp;
					split_point = i;
					min_dist = dist;
				}

				bounding_box_min.merge(
					split_data[i]->get_bounding_box());
			}

			return split_point;
		}

	}

	const BoundingBox &RStarTreeNode::get_element_bounding_box(
		const Uint32 index) const
	{
		assert(check_index(index));

		return m_elements[index]->get_bounding_box();
	}


	bool RStarTreeNode::add_element(const BoundedObjectPtr element)
	{
		Uint32 index;

		assert(element);

		if (get_count() < get_max_count())
		{
			index = get_count();

			m_count++;

			assert(get_count() <= get_max_count());

			set_element(element, index);

			return true;
		}
		else
		{
			return false;
		}
	}

	void RStarTreeNode::add_node(BoundedObjectPtrVector &visitor) const
	{
		Uint32 i;

		if (get_leaf())
		{
			for (i = 0; i < get_count(); i++)
			{
				visitor.push_back(get_element(i));
			}
		}
		else
		{
			for (i = 0; i < get_count(); i++)
			{
				get_node(i)->add_node(visitor);
			}
		}
	}

	void RStarTreeNode::remove_element(const Uint32 index)
	{
		Uint32 end;

		assert(check_index(index));

		end = get_count() - 1;

		if ((index != (get_count() - 1)) && (get_count() > 1))
		{
			set_element(get_element(end), index);
		}

		m_count--;
	}

	void RStarTreeNode::intersect_node(const Frustum &frustum,
		const PlaneMask in_mask, BoundedObjectPtrVector &visitor) const
	{
		Uint32 i;
		PlaneMask out_mask;

		assert(get_leaf());

		for (i = 0; i < get_count(); i++)
		{
			if (frustum.intersect(get_element_bounding_box(i), in_mask,
				out_mask) != it_outside)
			{
				visitor.push_back(get_element(i));
			}
		}
	}

	void RStarTreeNode::intersect_tree(const Frustum &frustum,
		const PlaneMask mask, BoundedObjectPtrVector &visitor) const
	{
		Uint32 i;
		PlaneMask out_mask;
		IntersectionType result;

		if (get_leaf())
		{
			intersect_node(frustum, mask, visitor);
		}
		else
		{
			for (i = 0; i < get_count(); i++)
			{
				result = frustum.intersect(get_element_bounding_box(i),
					mask, out_mask);
				switch (result)
				{
					case it_inside:
					{
						get_node(i)->add_node(visitor);
						break;
					}
					case it_intersect:
					{
						get_node(i)->intersect_tree(
							frustum, out_mask,
							visitor);
						break;
					}
					case it_outside:
					{
						break;
					}
				}
			}
		}
	}

	Uint32 RStarTreeNode::get_item_count() const
	{
		Uint32 i, count;

		if (get_leaf())
		{
			return get_count();
		}
		else
		{
			count = 0;

			for (i = 0; i < get_count(); i++)
			{
				count += get_node(i)->get_item_count();
			}

			return count;
		}
	}

	RStarTreeNodePtr RStarTreeNode::find_leaf(
		const BoundedObjectPtr element,
		RStarTreeNodePtrStack &path_buffer)
	{
		RStarTreeNodePtr found;
		Uint32 i;

		if (get_leaf())
		{
			if (find_element(element) != -1)
			{
				return this;
			}
			else
			{
				return 0;
			}
		}

		path_buffer.push(this);

		for (i = 0; i < get_count(); i++)
		{
			if (get_element_bounding_box(i).contains(
				element->get_bounding_box()))
			{
				found = get_node(i)->find_leaf(element, path_buffer);

				if (found != 0)
				{
					return found;
				}
			}
		}

		path_buffer.pop();

		return 0;
	}

	RStarTreeNodePtr RStarTreeNode::choose_sub_tree(
		const BoundingBox &bounding_box, const Uint32 insertion_level,
		RStarTreeNodePtrStack &path_buffer)
	{
		RStarTreeNodePtr node;

		if (get_leaf())
		{
			return this;
		}
		else
		{
			if (insertion_level == get_level())
			{
				return this;
			}

			path_buffer.push(this);

			if (get_level() == 1)
			{
				node = find_least_overlap(bounding_box);
			}
			else
			{
				node = find_least_enlargement(bounding_box);
			}

			assert(node);

			return node->choose_sub_tree(bounding_box,
				insertion_level, path_buffer);
		}
	}

	bool RStarTreeNode::insert(const BoundedObjectPtr element)
	{
		Uint32 i;

		if (get_leaf())
		{
			return add_element(element);
		}
		else
		{
			for (i = 0; i < get_count(); i++)
			{
				if (get_element_bounding_box(i).contains(
					element->get_bounding_box()))
				{
					if (get_node(i)->insert(element))
					{
						return true;
					}
				}
			}

			return false;
		}
	}

	RStarTreeNodePtr RStarTreeNode::find_least_overlap(
		const BoundingBox &bounding_box) const
	{
		BoundingBox tmp_bounding_box;
		float overlap, min_overlap;
		Uint32 i, j, index;

		assert(!get_leaf());
		assert(get_count() > 0);

		min_overlap = std::numeric_limits<float>::max();

		index = std::numeric_limits<Uint32>::max();

		for (i = 0; i < get_count(); i++)
		{
			tmp_bounding_box = enclose(bounding_box,
				get_element_bounding_box(i));

			overlap = 0.0f;

			for (j = 0; j < get_count(); j++)
			{
				if (i != j)
				{
					overlap += tmp_bounding_box.overlap(
						get_element_bounding_box(j));
				}
			}

			if (overlap < min_overlap)
			{
				if (overlap <= 0.0f)
				{
					return get_node(i);
				}

				min_overlap = overlap;
				index = i;
			}
		}

		assert(index < get_count());

		return get_node(index);
	}

	RStarTreeNodePtr RStarTreeNode::find_least_enlargement(
		const BoundingBox &bounding_box) const
	{
		float enlargement, min_enlargement, v;
		Uint32 i, index;

		assert(!get_leaf());
		assert(get_count() > 0);

		min_enlargement = std::numeric_limits<float>::max();

		index = std::numeric_limits<Uint32>::max();

		for (i = 0; i < get_count(); i++)
		{
			v = get_element_bounding_box(i).get_volume();
			enlargement = enclose(bounding_box,
				get_element_bounding_box(i)).get_volume() - v;

			if (enlargement < min_enlargement)
			{
				if (enlargement <= 0.0f)
				{
					return get_node(i);
				}
				min_enlargement = enlargement;
				index = i;
			}
		}

		return get_node(index);
	}

	void RStarTreeNode::update_enclosing_bounding_box()
	{
		BoundingBox bounding_box;
		Uint32 i;

		assert(get_count() > 0);

		bounding_box = get_element_bounding_box(0);

		for (i = 1; i < get_count(); i++)
		{
			bounding_box.merge(get_element_bounding_box(i));
		}

		bounding_box.scale(1.00001f);

		set_bounding_box(bounding_box);
	}

	void RStarTreeNode::split(RStarTreePtr tree,
		const BoundedObjectPtr element, RStarTreeNodePtr new_node)
	{
		BoundedObjectPtrArray9 split_data;
		Sint32 i, node_spf, new_size, split_point;
		Uint32 j;

		assert(get_count() == get_max_count());
		assert(new_node);
		assert(element);
		assert(tree);

		new_size = get_max_count() + 1;

		node_spf = boost::numeric_cast<Sint32>(new_size *
			tree->m_split_distribution_factor);

		for (j = 0; j < get_max_count(); j++)
		{
			split_data[j] = get_element(j);
		}

		split_data[get_max_count()] = element;

		split_point = split_array9(split_data, node_spf);

		assert(split_point > 0);
		assert(split_point < static_cast<Sint32>(get_max_count()));

		clear();

		for (i = 0; i < split_point; i++)
		{
			new_node->add_element(split_data[i]);
		}

		for (i = split_point; i < new_size; i++)
		{
			add_element(split_data[i]);
		}

		update_enclosing_bounding_box();
		new_node->update_enclosing_bounding_box();

		assert(new_node->get_count() > 0);

		assert(get_count() > 0);
	}

	bool RStarTreeNode::insert_element(RStarTreePtr tree,
		const BoundedObjectPtr element,
		RStarTreeNodePtrStack &path_buffer, _32BitSet &oft)
	{
		RStarTreeNodePtr node;
		RStarTreeNodePtr new_node;
		BoundedObjectPtrVector reinsert;
		Uint32 i;

		assert(tree);

		if (get_count() < get_max_count())
		{
			add_element(element);

			if (!path_buffer.empty())
			{
				adjust_tree(path_buffer);

				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			assert(get_level() < oft.size());

			if (!path_buffer.empty() && !oft[get_level()])
			{
				oft[get_level()] = true;

				reinsert_elements(tree, element, reinsert);

				adjust_tree(path_buffer);

				for (i = 0; i < reinsert.size(); i++)
				{
					tree->add_data(reinsert[i],
						get_level(), oft);
				}

				return true;
			}
			else
			{
				new_node = tree->new_node(get_level());

				split(tree, element, new_node);

				assert(new_node);
				assert(new_node->get_count() > 0);
				assert(get_count() > 0);

				if (path_buffer.empty())
				{
					node = tree->add_new_root_node(
						get_level() + 1);

					assert(node);

					node->add_element(this);
					node->add_element(new_node);

					node->update_enclosing_bounding_box();

					assert(node->get_count() > 0);
				}
				else
				{
					node = path_buffer.top();

					path_buffer.pop();

					assert(node);

					node->adjust_tree(tree, new_node, path_buffer, oft);

					assert(node->get_count() > 0);
				}

				assert(new_node->get_count() > 0);

				return true;
			}
		}
	}

	RStarTreeNodePtr RStarTreeNode::find_small_leaf(
		const Uint32 minimum_load, RStarTreeNodePtrStack &path_buffer)
	{
		RStarTreeNodePtr found;
		Uint32 i;

		if (get_leaf())
		{
			if (get_count() < minimum_load)
			{
				return this;
			}
			else
			{
				return 0;
			}
		}

		path_buffer.push(this);

		for (i = 0; i < get_count(); i++)
		{
			found = get_node(i)->find_small_leaf(minimum_load,
				path_buffer);

			if (found)
			{
				return found;
			}
		}

		path_buffer.pop();

		return 0;
	}

	void RStarTreeNode::adjust_tree(RStarTreeNodePtrStack &path_buffer)
	{
		RStarTreeNodePtr parent;

		update_enclosing_bounding_box();

		if (!path_buffer.empty())
		{
			parent = path_buffer.top();

			path_buffer.pop();

			assert(parent);

			parent->adjust_tree(path_buffer);
		}
	}

	void RStarTreeNode::adjust_tree(RStarTreePtr tree,
		RStarTreeNodePtr node, RStarTreeNodePtrStack &path_buffer, _32BitSet &oft)
	{
		bool adjust;

		adjust = insert_element(tree, node, path_buffer, oft);

		if (!adjust)
		{
			adjust_tree(path_buffer);
		}
	}

	void RStarTreeNode::reinsert_elements(RStarTreePtr tree,
		const BoundedObjectPtr element,
		BoundedObjectPtrVector &reinsert)
	{
		Uint32 i, reinsert_count;

		assert(get_count() == get_max_count());

		reinsert_count = static_cast<Sint32>(get_max_count() *
			tree->get_reinsert_factor());

		assert(reinsert_count < get_count());

		reinsert.reserve(reinsert_count + 1);

		for (i = 0; i < reinsert_count; i++)
		{
			reinsert.push_back(get_element(i));
		}

		for (i = 0; i < reinsert_count; i++)
		{
			assert(get_index(reinsert[i]) == i);
			remove_element(i);
		}

		reinsert.push_back(element);

		assert(get_count() > 0);
	}

	RStarTreeNode::RStarTreeNode(const Uint32 level): m_level(level),
		m_count(0)
	{
	}

	RStarTreeNode::~RStarTreeNode() throw()
	{
	}

	Uint32 RStarTreeNode::get_sub_nodes_count() const throw()
	{
		Uint32 i, result;

		if (get_leaf())
		{
			return 0;
		}
		else
		{
			result = get_count();

			for (i = 0; i < get_count(); i++)
			{
				result += get_node(i)->get_sub_nodes_count();
			}

			return result;
		}
	}

	bool RStarTreeNode::check_nodes() const
	{
		Uint32 i;

		for (i = 0; i < get_count(); i++)
		{
			if (!get_bounding_box().contains(get_element_bounding_box(i)))
			{
				return false;
			}

			if (!get_leaf())
			{
				if (!get_node(i)->check_nodes())
				{
					return false;
				}
			}
		}

		return true;
	}

}
