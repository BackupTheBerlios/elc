/****************************************************************************
 *            opengl1mesh.cpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#include "abstractmesh.hpp"

namespace eternal_lands
{

	OpenGl1Mesh::OpenGl1Mesh()
	{
	}

	OpenGl1Mesh::~OpenGl1Mesh() throw()
	{
	}

	void OpenGl1Mesh::init()
	{
	}

	void OpenGl1Mesh::bind()
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, m_position_data.get());

		if (m_normal_data.get() != 0)
		{
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, 0, m_normal_data.get());
		}
		else
		{
			glDisableClientState(GL_NORMAL_ARRAY);
		}

		if (m_color_data.get() != 0)
		{
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_UNSIGNED_BYTE, 0,
				m_color_data.get());
		}
		else
		{
			glDisableClientState(GL_COLOR_ARRAY);
		}

		if (m_texture_coordinate_data.get() != 0)
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, 0,
				m_texture_coordinate_data.get());
		}
		else
		{
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
	}

	void OpenGl1Mesh::draw()
	{
		Uint32 i;

		for (i = 0; i < instances; i++)
		{
			if (m_index_data.get() != 0)
			{
				glDrawElements(primitive, count, type,
					m_index_data.get() + index);
			}
			else
			{
				glDrawArrays(primitive, index, count);
			}
		}
	}

}

