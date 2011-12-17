/****************************************************************************
 *            opengl3mesh.cpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#include "abstractmesh.hpp"

namespace eternal_lands
{

	OpenGl3Mesh::OpenGl3Mesh()
	{
	}

	OpenGl3Mesh::~OpenGl3Mesh() throw()
	{
	}

	void OpenGl3Mesh::bind(const VertexStream &stream, const Uint32 divisor)
	{
		void* source;
		Uint32 stride, offset, count;
		GLenum type;
		GLboolean normalized;
		vertex_semantic_type semantic;

		stream.bind(hbt_vertex);

		stride = element.get_stride();

		BOOST_FOREACH(const VertexElement &element,
			stream.get_vertex_elements())
		{
			source = element.get_offset();
			count = element.get_count();
			type = element.get_gl_type();
			normalized = element.get_normalized();
			semantic = element.get_semantic();

			glVertexAttribPointer(semantic, count, type,
				normalized, stride, source);

			glVertexAttribDivisor(semantic, divisor);

			glEnableVertexAttribArray(semantic);
		}
	}

	void OpenGl3Mesh::init()
	{
		glBindVertexArray(m_id);

		BOOST_FOREACH(const VertexStreamSharedPtr &stream,
			m_vertex_data)
		{
			bind(*stream);
		}

		glBindVertexArray(0);
	}

	void OpenGl3Mesh::bind()
	{
		glBindVertexArray(m_id);

		if (m_index_data.get() != 0)
		{
			m_index_data->bind(hbt_index);
		}
	}

	void OpenGl1Mesh::draw()
	{
		if (m_index_data.get() != 0)
		{
			glDrawElementsInstancedBaseVertex(primitive, count,
				type, index, instances, base);
		}
		else
		{
			glDrawArraysInstanced(primitive, index, count,
				instances);
		}
	}

}

