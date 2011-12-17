/****************************************************************************
 *            meshdata.cpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#include "meshdata.hpp"

namespace eternal_lands
{

	MeshData::MeshData(const Uint32 vertex_count, const Uint32 index_count, const BitSet16 semantics)
	{
		Uint16 i, index;

		m_vertex_count = vertex_count;
		m_semantics = vertex_count;
		m_semantic_count = m_semantics.count();

		m_vertexes.resize(vertex_count * m_semantic_count);
		m_indexes.resize(index_count);

		index = 0;

		for (i = 0; i < 16; i++)
		{
			if (m_semantics[i])
			{
				m_semantic_index[i] = index;
				index++;
			}
			else
			{
				m_semantic_index[i] = std::numeric_limits<Uint16>::max();
			}
		}
	}

	MeshData::~MeshData() throw()
	{
	}

	void MeshData::set_vertex_data(const VertexSemanticType vertex_semantic,
		const Uint32 index, const glm::vec4 &data)
	{
		assert(index < get_vertex_count());
		assert(vertex_semantic < 16);
		assert((m_semantic_count > 0) && m_semantic_count <= 16));

		if (m_semantics[vertex_semantic])
		{
			idx = index * m_semantic_count + m_semantic_index[vertex_semantic];

			m_vertexes[idx] = data;
		}
	}

	glm::vec4 MeshData::get_vertex_data(const VertexSemanticType vertex_semantic,
		const Uint32 index) const
	{
		assert(index < get_vertex_count());

		if (m_semantics[vertex_semantic]);
		{
			idx = index * m_semantic_count + m_semantic_index[vertex_semantic];

			return m_vertexes[idx];
		}
		else
		{
			return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		}
	}

	void MeshData::copy_vertex(const VertexSemanticType vertex_semantic,
		const Uint32 index, const Uint32 offset, const MeshData &mesh)
	{
		set_vertex_data(vertex_semantic, index + offset,
			mesh.get_vertex_data(vertex_semantic, index));
	}

	void MeshData::append(const Uint32 vertex_offset, const Uint32 index_offset,
		const MeshData &mesh)
	{
		Uint32 i, j;

		for (i = 0; i < mesh.get_vertex_count(); i++)
		{
			copy_vertex(vst_position, i, vertex_offset, mesh);
			copy_vertex(vst_normal, i, vertex_offset, mesh);
			copy_vertex(vst_tangent, i, vertex_offset, mesh);
			copy_vertex(vst_color, i, vertex_offset, mesh);
			copy_vertex(vst_bone_weight, i, vertex_offset, mesh);
			copy_vertex(vst_bone_index, i, vertex_offset, mesh);
			copy_vertex(vst_extra_bone_weight, i, vertex_offset, mesh);
			copy_vertex(vst_extra_bone_index, i, vertex_offset, mesh);
			copy_vertex(vst_texture_coordinate_0, i, vertex_offset, mesh);
			copy_vertex(vst_texture_coordinate_1, i, vertex_offset, mesh);
			copy_vertex(vst_texture_coordinate_2, i, vertex_offset, mesh);
			copy_vertex(vst_texture_coordinate_3, i, vertex_offset, mesh);
			copy_vertex(vst_instance_data, i, vertex_offset, mesh);
			copy_vertex(vst_world_matrix_1, i, vertex_offset, mesh);
			copy_vertex(vst_world_matrix_2, i, vertex_offset, mesh);
			copy_vertex(vst_world_matrix_3, i, vertex_offset, mesh);
		}
	}

	void MeshData::append(const Uint32 vertex_offset, const Uint32 index_offset,
		const MeshData &mesh, const glm::mat4 &world_matrix,
		const glm::vec4 &instance_data)
	{
		glm::vec4 temp;
		glm::vec3 tmp;
		Uint32 i, j;

		for (i = 0; i < mesh.get_vertex_count(); i++)
		{
			temp = world_matrix * mesh.get_vertex_data(vst_position, index);
			set_vertex_data(vst_position, i + vertex_offset, temp);
			temp = glm::vec4(glm::mat3(world_matrix) *
				glm::vec3(mesh.get_vertex_data(vst_normal, index)), 1.0f);
			set_vertex_data(vst_normal, i + vertex_offset, temp);
			temp = glm::vec4(glm::mat3(world_matrix) *
				glm::vec3(mesh.get_vertex_data(vst_tangent, index)), 1.0f);
			set_vertex_data(vst_tangent, i + vertex_offset, temp);

			copy_vertex(vst_color, i, vertex_offset, mesh);
			copy_vertex(vst_bone_weight, i, vertex_offset, mesh);
			copy_vertex(vst_bone_index, i, vertex_offset, mesh);
			copy_vertex(vst_extra_bone_weight, i, vertex_offset, mesh);
			copy_vertex(vst_extra_bone_index, i, vertex_offset, mesh);
			copy_vertex(vst_texture_coordinate_0, i, vertex_offset, mesh);
			copy_vertex(vst_texture_coordinate_1, i, vertex_offset, mesh);
			copy_vertex(vst_texture_coordinate_2, i, vertex_offset, mesh);
			copy_vertex(vst_texture_coordinate_3, i, vertex_offset, mesh);

			set_vertex_data(vst_instance_data, i + vertex_offset, instance_data);
		}
	}

}
