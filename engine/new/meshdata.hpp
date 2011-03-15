/****************************************************************************
 *            meshdata.hpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#ifndef	UUID_ea879c22_9289_40a2_8984_ef65232243b0
#define	UUID_ea879c22_9289_40a2_8984_ef65232243b0

#ifndef	__cplusplus
#error	"Including C++ header in C translation unit!"
#endif	/* __cplusplus */

#include "prerequisites.hpp"

/**
 * @file
 * @brief The @c class MeshData.
 * This file contains the @c class MeshData.
 */
namespace eternal_lands
{

	/**
	 * @brief @c class for mesh data.
	 *
	 * @c class for mesh data.
	 */
	class MeshData
	{
		private:
			Uint16Array16 m_semantic_index;
			Vec4Vector m_vertexes
			Uint32Vector m_indexes;
			Uint32 m_vertex_count;
			BitSet16 m_semantics;
			Uint16 m_semantic_count;

			void copy_vertex(const VertexSemanticType vertex_semantic,
				const Uint32 index, const Uint32 offset,
				const MeshData &mesh);

		public:
			/**
			 * @brief Default constructor.
			 * Default constructor initializes the buffers for vertex and index data.
			 * @param vertex_count The number of vertexes.
			 * @param index_count The number of indices.
			 * @param semantics The vertex semantics that are used.
			 */
			MeshData(const Uint32 vertex_count, const Uint32 index_count,
				const BitSet16 semantics);

			/**
			 * Default destructor.
			 */
			virtual ~MeshData() throw();

			inline Uint32 get_vertex_count() const
			{
				return m_vertex_count;
			}

			inline Uint32 get_index_count() const
			{
				return m_indexes.size();
			}

			void set_vertex_data(const VertexSemanticType vertex_semantic,
				const Uint32 index, const glm::vec4 &data);

			glm::vec4 get_vertex_data(const VertexSemanticType vertex_semantic,
				const Uint32 index) const;

			inline void set_index_data(const Uint32 index, const Uint32 data)
			{
				assert(index < get_index_count());

				m_indexes[index] = data;
			}

			inline Uint32 get_index_data(const Uint32 index) const
			{
				assert(index < get_index_count());

				return m_indexes[index];
			}

			void append(const Uint32 vertex_offset, const Uint32 index_offset,
				const MeshData &mesh);
			void append(const Uint32 vertex_offset, const Uint32 index_offset,
				const MeshData &mesh, const glm::mat4 &world_matrix,
				const glm::vec4 &instance_data)

	};

}

#endif	/* UUID_ea879c22_9289_40a2_8984_ef65232243b0 */
