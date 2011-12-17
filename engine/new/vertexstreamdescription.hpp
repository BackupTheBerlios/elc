/****************************************************************************
 *            vertexstreamdescription.hpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#ifndef	UUID_fec52827_8a6c_4e0d_aabd_1a96d4c65ad3
#define	UUID_fec52827_8a6c_4e0d_aabd_1a96d4c65ad3

#ifndef	__cplusplus
#error	"Including C++ header in C translation unit!"
#endif	/* __cplusplus */

#include "vertexelement.hpp"

/**
 * @file
 * @brief The @c class VertexStreamDescription.
 * This file contains the @c class VertexStreamDescription.
 */
namespace eternal_lands
{

	/**
	 * @brief This class describes a vertex strean.
	 *
	 * An vertex stream is defined throught its vertex elements.
	 */
	class VertexStream: public HardwareBuffer
	{
		private:
			VertexElementVector m_vertex_elements;
			Uint32 m_stride;

		public:
			/**
			 * Default constructor.
			 */
			VertexStreamDescription();

			/**
			 * Default destructor.
			 */
			~VertexStreamDescription() throw();

			/**
			 * @brief Gets the vertex elements.
			 * Sets the vertex elements for this stream. Also the size
			 * stride is calculated for the stream.
			 * @param vertex_elements The new vertex elements.
			 */
			void set_vertex_elements(
				const VertexElementVector &vertex_elements);

			/**
			 * @brief Gets the vertex elements.
			 * Returns the vertex elements for this stream.
			 * @return The vertex elements.
			 */
			inline const VertexElementVector &get_vertex_elements()
				const
			{
				return m_vertex_elements;
			}

			inline Uint32 get_stride() const
			{
				return m_stride;
			}

	};

}

#endif	/* UUID_fec52827_8a6c_4e0d_aabd_1a96d4c65ad3 */
