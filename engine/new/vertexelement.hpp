/****************************************************************************
 *            vertexelement.hpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#ifndef	UUID_391f1863_20f2_46a8_af7d_4cd5b6ffa619
#define	UUID_391f1863_20f2_46a8_af7d_4cd5b6ffa619

#ifndef	__cplusplus
#error	"Including C++ header in C translation unit!"
#endif	/* __cplusplus */

#include "prerequisites.hpp"

/**
 * @file
 * @brief The @c class VertexElement.
 * This file contains the @c class VertexElement.
 */
namespace eternal_lands
{

	/**
	 * Different vertex element semantic types.
	 * @{
	 */
	enum VertexSemanticType
	{
		vst_position = 0,
		vst_normal = 1,
		vst_tangent = 2,
		vst_color = 3,
		vst_bone_weight = 4,
		vst_bone_index = 5,
		vst_extra_bone_weight = 6
		vst_extra_bone_index = 7,
		vst_texture_coordinate_0 = 8,
		vst_texture_coordinate_1 = 9,
		vst_texture_coordinate_2 = 10,
		vst_texture_coordinate_3 = 11,
		vst_instance_data = 12,
		vst_world_matrix_1 = 13,
		vst_world_matrix_2 = 14,
		vst_world_matrix_3 = 15
	};
	/**
	 * @}
	 */

	/**
	 * @enum VertexElementType
	 * Types of vertex elements.
	 * @{
	 */
	enum VertexElementType
	{
		/**
		 * One float
		 */
		vet_float1,
		/**
		 * Two floats
		 */
		vet_float2,
		/**
		 * Three floats
		 */
		vet_float3,
		/**
		 * Four floats
		 */
		vet_float4,
		/**
		 * Two half floats
		 */
		vet_half2,
		/**
		 * Four half floats
		 */
		vet_half4,
		/**
		 * Two signed shorts
		 */
		vet_short2,
		/**
		 * Four signed shorts
		 */
		vet_short4,
		/**
		 * Two unsigned shorts
		 */
		vet_ushort2,
		/**
		 * Four unsigned shorts
		 */
		vet_ushort4,
		/**
		 * Four signed bytes
		 */
		vet_byte4,
		/**
		 * Four unsigned bytes
		 */
		vet_ubyte4,
		/**
		 * Three 10 bit signed integers and one two bit signed integer.
		 *
		 */
		vet_signed_xyz10_w2,
		/**
		 * Three 10 bit unsigned integers and one two bit unsigned integer.
		 */
		vet_unsigned_xyz10_w2
	};
	/**
	 * @}
	 */

	/**
	 * @brief This class describes a vertex element.
	 *
	 * An vertex element is defined throught its semantic, type, buffer and
	 * offset. The semantic defines what the data is, like position, normal
	 * etc. The type defines if the data are floats, shorts etc. The buffer
	 * defines in what buffer of the mesh the data is and the offset is used
	 * for accese of these data in the buffer.
	 */
	class VertexElement
	{
		private:
			VertexSemanticType m_semantic;
			VertexElementType m_type;
			Uint32 m_offset;
			Uint32 m_count;
			Uint32 m_size;
			Uint32 m_divisor;
			GLenum m_gl_type;
			bool m_normalize_integer;

			void check() const;

		public:
			/**
			 * @brief Default constructor.
			 * Default constructor initializes the vertex element.
			 * @param semantic The semantic for the vertex element.
			 * @param type The type for the vertex element.
			 * @param normalize_integer True for normalized integers, false else.
			 */
			VertexElement(const VertexSemanticType semantic,
				const VertexElementType type,
				const bool normalize_integer = false);

			/**
			 * Default destructor.
			 */
			~VertexElement() throw();

			/**
			 * Returns the semantic of the vertex element.
			 * @return The semantic of the vertex element.
			 */
			inline VertexSemanticType get_semantic() const
			{
				return m_semantic;
			}

			/**
			 * Returns the type of the vertex element.
			 * @return The type of the vertex element.
			 */
			inline VertexElementType get_type() const
			{
				return m_type;
			}

			/**
			 * Returns the offset of the vertex element in the vertex buffer.
			 * @return The offset of the vertVertexElementTypeex element.
			 */
			inline Uint32 get_offset() const
			{
				return m_offset;
			}

			/**
			 * Sets the semantic of the vertex element.
			 * @param semantic The new semantic for the vertex element.
			 */
			inline void set_semantic(const VertexSemanticType semantic)
			{
				m_semantic = semantic;
			}

			/**
			 * Sets the type of the vertex element.
			 * @param type The new type for the vertex element.
			 */
			inline void set_type(const VertexElementType type)
			{
				m_type = type;
				m_size = get_size(get_type());
			}

			/**
			 * Sets the offset of the vertex element.
			 * @param offset The new offset for the vertex element.
			 */
			inline void set_offset(const Uint32 offset)
			{
				m_offset = offset;
			}

			/**
			 * Returns the count of values the vertex element
			 * contains.
			 * @return The count of values the vertex element
			 * contains.
			 */
			inline Uint32 get_count() const
			{
				return m_count;
			}

			/**
			 * Returns the size of the vertex element (in bytes).
			 * @return The size of the vertex element (in bytes).
			 */
			inline Uint32 get_size() const
			{
				return m_size;
			}

			/**
			 * Returns the OpenGL tpye of the vertex element.
			 * @return The OpenGL tpye of the vertex element.
			 */
			inline GLenum get_gl_type() const
			{
				return m_gl_type;
			}

			/**
			 * Returns true if the signed integer values get scaled so they fit
			 * into -1.0 .. 1.0 range and if the unsigned inter values get
			 * scaled so they fit into the 0.0 .. 1.0 range. False otherwise.
			 * @return True if normalization is used, else false.
			 */
			inline bool get_normalize() const
			{
				return m_normalize_integer;
			}

			/**
			 * Returns GL_TRUE if the signed integer values get scaled so they
			 * fit into -1.0 .. 1.0 range and if the unsigned inter values get
			 * scaled so they fit into the 0.0 .. 1.0 range. GL_FALSE
			 * otherwise.
			 * @return GL_TRUE if normalization is used, else GL_FALSE.
			 */
			inline GLenum get_gl_normalize() const
			{
				if (get_normalize())
				{
					return GL_TRUE;
				}
				else
				{
					return GL_FALSE;
				}
			}

			/**
			 * Log the class to an output stream.
			 * @param str The stream where to log this vertex element.
			 */
			void log(std::ostream &str) const;
			void validate() const;

			/**
			  * Returns the string representation of the given enum value.
			  * @param vertex_element_type The enum to use.
			  * @return The string representation of the given enum value.
			  */
			static const String &get_str(
				const VertexElementType vertex_element_type);

			/**
			  * Returns the string representation of the given enum value.
			  * @param vertex_semantic_type The enum to use.
			  * @return The string representation of the given enum value.
			  */
			static const String &get_str(
				const VertexSemanticType vertex_semantic_type);

			/**
			  * Returns the vertex element type represented by the
			  * string.
			  * @param str The string to use.
			  * @return The vertex element type represented by the
			  * string
			  */
			static VertexElementType get_vertex_element_type(const String &str);

			/**
			  * Returns the vertex semantic type represented by the
			  * string.
			  * @param str The string to use.
			  * @return The vertex semantic type represented by the
			  * string
			  */
			static VertexSemanticType get_vertex_semantic_type(const String &str);

			/**
			 * Returns the size of the vertex element type (in bytes).
			 * @param vertex_element_type The type for the vertex element to use.
			 * @return The size of the vertex element type (in bytes).
			 */
			static Uint32 get_size(const VertexElementType vertex_element_type);

			/**
			 * Returns the element count that the vertex element type contains.
			 * @param vertex_element_type The type for the vertex element to use.
			 * @return The count of floats/shorts/bytes the vertex element type
			 * contains.
			 */
			static Uint32 get_element_count(
				const VertexElementType vertex_element_type);

			/**
			 * Returns true if the elements of the given type are signed, false
			 * else.
			 * @param vertex_element_type The type for the vertex element to
			 * use.
			 * @return True if its a signed type, false else.
			 */
			static bool get_signed_elements(
				const VertexElementType vertex_element_type);

			/**
			 * Returns true if its a type with dynamic range, false else.
			 * @param vertex_element_type The type for the vertex element to
			 * use.
			 * @return True if its a type with dynamic range, false else.
			 */
			static bool get_dynamic_range(
				const VertexElementType vertex_element_type);

			/**
			 * Returns the OpenGL tpye of the vertex element type.
			 * @param vertex_element_type The type for the vertex element to use.
			 * @return The OpenGL tpye of the vertex element type.
			 */
			static GLenum get_gl_type(
				const VertexElementType vertex_element_type);

			/**
			 * Returns true if the vertex element type is supported,
			 * else false.
			 * @param vertex_element_type The type for the vertex element to use.
			 * @return True if supported, false else.
			 */
			static bool get_supported(
				const VertexElementType vertex_element_type);

	};

	std::ostream& operator<< (std::ostream &str,
		const VertexElement &value);
	std::ostream& operator<< (std::ostream &str,
		const VertexElementType &value);
	std::ostream& operator<< (std::ostream &str,
		const VertexSemanticType &value);

}

#endif	/* UUID_391f1863_20f2_46a8_af7d_4cd5b6ffa619 */
