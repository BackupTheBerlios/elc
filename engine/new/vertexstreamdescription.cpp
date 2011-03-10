/****************************************************************************
 *            vertexstreamdescription.cpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#include "vertexstreamdescription.hpp"
#include "exceptions.hpp"

namespace eternal_lands
{

	VertexStreamDescription::VertexStreamDescription(): m_stride(0)
	{
	}

	VertexStreamDescription::~VertexStreamDescription() throw()
	{
	}

	void VertexStreamDescription::set_vertex_elements(
		const VertexElementVector &vertex_elements)
	{
		m_stride = 0;

		BOOST_FOREACH(VertexElement &vertex_element, m_vertex_elements)
		{
			vertex_element.set_offset(m_stride);

			m_stride += vertex_element.get_size();
		}
	}

}
