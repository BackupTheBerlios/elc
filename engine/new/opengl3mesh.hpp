/****************************************************************************
 *            opengl3mesh.hpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#ifndef	UUID_febadc26_ffea_4ad2_9cef_560fd8aa2478
#define	UUID_febadc26_ffea_4ad2_9cef_560fd8aa2478

#ifndef	__cplusplus
#error	"Including C++ header in C translation unit!"
#endif	/* __cplusplus */

#include "prerequisites.hpp"
#include "abstractmesh.hpp"

/**
 * @file
 * @brief The @c class OpenGl3Mesh.
 * This file contains the @c class OpenGl3Mesh.
 */
namespace eternal_lands
{

	/**
	 * @brief @c class for meshs in a format for OpenGL 3.x.
	 *
	 * @c class for meshs in a format for OpenGL 3.x using hardware
	 * buffers, shaders, vertex array objects, restart index, instancing
	 * and base vertex.
	 */
	class OpenGl3Mesh: public AbstractMesh
	{
		private:
			VertexStreamSharedPtrArray4 m_vertex_data;
			HardwareBufferSharedPtr m_index_data;

			/**
			 * Vertex array object
			 */
			GLuint m_id;

			Uint32 m_restart_index;

			bool m_use_restart_index;

			bool m_16_bit_index;

			static void bind(const VertexStreamSharedPtr &stream,
				const Uint32 divisor);

		public:
			/**
			 * Default constructor.
			 */
			OpenGl3Mesh();

			/**
			 * Default destructor.
			 */
			virtual ~OpenGl3Mesh() throw();

			virtual void bind();
			virtual void draw();

	};

}

#endif	/* UUID_febadc26_ffea_4ad2_9cef_560fd8aa2478 */

