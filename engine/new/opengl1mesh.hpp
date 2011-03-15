/****************************************************************************
 *            opengl1mesh.hpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#ifndef	UUID_0968615f_72bc_432f_800c_ebc679eede65
#define	UUID_0968615f_72bc_432f_800c_ebc679eede65

#ifndef	__cplusplus
#error	"Including C++ header in C translation unit!"
#endif	/* __cplusplus */

#include "prerequisites.hpp"
#include "abstractmesh.hpp"

/**
 * @file
 * @brief The @c class OpenGl1Mesh.
 * This file contains the @c class OpenGl1Mesh.
 */
namespace eternal_lands
{

	/**
	 * @brief @c class for meshs in a format for OpenGL 1.x.
	 *
	 * @c class for meshs in a format for OpenGL 1.x using vertex arrays
	 * and texture combiners.
	 */
	class OpenGl1Mesh: public AbstractMesh
	{
		private:
			void* m_position_data;
			void* m_texture_coordinate_data;
			void* m_normal_data;
			void* m_color_data;
			void* m_index_data;

			bool m_16_bit_index;

		public:
			/**
			 * Default constructor.
			 */
			OpenGl1Mesh();

			/**
			 * Default destructor.
			 */
			virtual ~OpenGl1Mesh() throw();

			virtual void bind();
			virtual void draw();

	};

}

#endif	/* UUID_0968615f_72bc_432f_800c_ebc679eede65 */

