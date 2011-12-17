/****************************************************************************
 *            opengl2mesh.hpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#ifndef	UUID_34996477_5a8c_4089_b9fa_6fd676c1af0d
#define	UUID_34996477_5a8c_4089_b9fa_6fd676c1af0d

#ifndef	__cplusplus
#error	"Including C++ header in C translation unit!"
#endif	/* __cplusplus */

#include "prerequisites.hpp"
#include "abstractmesh.hpp"

/**
 * @file
 * @brief The @c class OpenGl2Mesh.
 * This file contains the @c class OpenGl2Mesh.
 */
namespace eternal_lands
{

	/**
	 * @brief @c class for meshs in a format for OpenGL 2.x.
	 *
	 * @c class for meshs in a format for OpenGL 2.x using hardware
	 * buffers and shaders.
	 */
	class OpenGl2Mesh: public AbstractMesh
	{
		private:
			VertexStreamSharedPtrArray4 m_vertex_data;
			HardwareBufferSharedPtr m_index_data;

			bool m_16_bit_index;

			static void bind(const VertexStreamSharedPtr &stream);

		public:
			/**
			 * Default constructor.
			 */
			OpenGl2Mesh();

			/**
			 * Default destructor.
			 */
			virtual ~OpenGl2Mesh() throw();

			virtual void bind();
			virtual void draw();

	};

}

#endif	/* UUID_34996477_5a8c_4089_b9fa_6fd676c1af0d */

