/****************************************************************************
 *            opengl2mesh.cpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#include "abstractmesh.hpp"

namespace eternal_lands
{

	OpenGl2Mesh::OpenGl2Mesh()
	{
	}

	OpenGl2Mesh::~OpenGl2Mesh() throw()
	{
	}

	void OpenGl2Mesh::bind(const VertexStreamSharedPtr &stream)
	{
		void* source;
		Uint32 stride, offset, count;
		GLenum type;
		GLboolean normalized;
		vertex_semantic_type semantic;

		stream->bind(hbt_vertex);

		stride = element.get_stride();

		BOOST_FOREACH(const VertexElement &element,
			stream->get_vertex_elements())
		{
			source = element.get_offset();
			count = element.get_count();
			type = element.get_gl_type();
			normalized = element.get_normalized();
			semantic = element.get_semantic();

			glVertexAttribPointer(semantic, count, type,
				normalized, stride, source);

			glEnableVertexAttribArray(semantic);
		}
	}

	void OpenGl2Mesh::init()
	{
	}

	void OpenGl2Mesh::bind()
	{
		BOOST_FOREACH(const VertexStreamSharedPtr &stream,
			m_vertex_data)
		{
			bind(*stream);
		}

		if (m_index_data.get() != 0)
		{
			m_index_data->bind(hbt_index);
		}
	}

	void OpenGl2Mesh::draw()
	{
		Uint32 i;

		for (i = 0; i < instances; i++)
		{
			if (m_index_data.get() != 0)
			{
				glDrawElements(primitive, count, type, index);
			}
			else
			{
				glDrawArrays(primitive, index, count);
			}
		}
	}

}

