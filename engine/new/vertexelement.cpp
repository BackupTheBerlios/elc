/****************************************************************************
 *            vertexelement.cpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#include "vertexelement.hpp"
#include "exceptions.hpp"

namespace eternal_lands
{

	namespace
	{

		class VertexElementTypeData
		{
			private:
				const String m_name;
				const Uint32 m_size;
				const GLenum m_gl_type;
				const Uint16 m_element_count;
				const bool m_dynamic_range;
				const bool m_signed_elements;

			public:
				inline VertexElementTypeData(const String &name,
					const Uint32 size, const GLenum gl_type,
					const Uint16 element_count, const bool dynamic_range,
					const bool signed_elements): m_name(name), m_size(size),
					m_gl_type(gl_type), m_element_count(element_count),
					m_dynamic_range(dynamic_range),
					m_signed_elements(signed_elements)
				{
					assert(get_element_count() > 0);
				}

				inline ~VertexElementTypeData() throw()
				{
				}

				inline const String &get_name() const
				{
					return m_name;
				}

				inline Uint32 get_size() const
				{
					return m_size;
				}

				inline GLenum get_gl_type() const
				{
					return m_gl_type;
				}

				inline Uint16 get_element_count() const
				{
					return m_element_count;
				}

				inline bool get_dynamic_range() const
				{
					return m_dynamic_range;
				}

				inline bool get_signed_elements() const
				{
					return m_signed_elements;
				}

		};

		const VertexElementTypeData vertex_element_type_datas[] =
		{
			VertexElementTypeData("float1", 1 * sizeof(GLfloat),
				GL_FLOAT, 1, true, true),
			VertexElementTypeData("float2", 2 * sizeof(GLfloat),
				GL_FLOAT, 2, true, true),
			VertexElementTypeData("float3", 3 * sizeof(GLfloat),
				GL_FLOAT, 3, true, true),
			VertexElementTypeData("float4", 4 * sizeof(GLfloat),
				GL_FLOAT, 4, true, true),
			VertexElementTypeData("half2", 2 * sizeof(GLhalfARB),
				GL_HALF_FLOAT, 2, true, true),
			VertexElementTypeData("half4", 4 * sizeof(GLhalfARB),
				GL_HALF_FLOAT, 4, true, true),
			VertexElementTypeData("short2", 2 * sizeof(GLshort),
				GL_SHORT, 2, false, true),
			VertexElementTypeData("short4", 4 * sizeof(GLshort),
				GL_SHORT, 4, false, true),
			VertexElementTypeData("ushort2", 2 * sizeof(GLushort),
				GL_UNSIGNED_SHORT, 2, false, false),
			VertexElementTypeData("ushort4", 4 * sizeof(GLushort),
				GL_UNSIGNED_SHORT, 4, false, false),
			VertexElementTypeData("byte4", 4 * sizeof(GLbyte),
				GL_BYTE, 4, false, true),
			VertexElementTypeData("ubyte4", 4 * sizeof(GLubyte),
				GL_UNSIGNED_BYTE, 4, false, false),
			VertexElementTypeData("signed_xyz10_w2", sizeof(GLint),
				GL_INT_2_10_10_10_REV, 4, false, true),
			VertexElementTypeData("unsigned_xyz10_w2", sizeof(GLuint),
				GL_UNSIGNED_INT_2_10_10_10_REV, 4, false, false),
		};

		const Uint32 vertex_element_type_datas_count =
			sizeof(vertex_element_type_datas) / sizeof(VertexElementTypeData);

		const String vertex_semantic_type_names[] =
		{
			"position",
			"normal",
			"tangent",
			"color",
			"bone_weight",
			"bone_index",
			"extra_bone_weight",
			"extra_bone_index",
			"texture_coordinate[0]",
			"texture_coordinate[1]",
			"texture_coordinate[2]",
			"texture_coordinate[3]",
			"instance_data",
			"world_matrix[0]",
			"world_matrix[1]",
			"world_matrix[2]"
		};

		const Uint32 vertex_semantic_type_names_count =
			sizeof(vertex_semantic_type_names) / sizeof(String);

	}

	VertexElement::VertexElement(const VertexSemanticType semantic,
		const VertexElementType type, const bool normalize_integer):
		m_semantic(semantic), m_type(type), m_offset(0),
		m_normalize_integer(normalize_integer)
	{
		m_count = get_element_count(get_type());
		m_size = get_size(get_type());
		m_gl_type = get_gl_type(get_type());
	}

	VertexElement::~VertexElement() throw()
	{
	}

	void VertexElement::log(std::ostream &str) const
	{
		str << "[semantic] " << get_semantic();
		str << " [type] " << get_type();
		str << " [offset] " << get_offset();
		str << " [count] " << get_count();
		str << " [size] " << get_size();
		str << " [normalize] " << get_normalize();
	}

	const String &VertexElement::get_str(
		const VertexElementType vertex_element_type)
	{
		if (vertex_element_type_datas_count <= vertex_element_type)
		{
			EL_THROW_EXCEPTION(InvalidParameterException()
				<< errinfo_range_min(0)
				<< errinfo_range_max(vertex_element_type_datas_count - 1)
				<< errinfo_range_index(static_cast<Uint32>(
					vertex_element_type))
				<< boost::errinfo_type_info_name(typeid(
					VertexElementType).name()));
		}

		return vertex_element_type_datas[vertex_element_type].get_name();
	}

	const String &VertexElement::get_str(
		const VertexSemanticType vertex_semantic_type)
	{
		if (vertex_semantic_type_names_count <= vertex_semantic_type)
		{
			EL_THROW_EXCEPTION(InvalidParameterException()
				<< errinfo_range_min(0)
				<< errinfo_range_max(vertex_semantic_type_names_count - 1)
				<< errinfo_range_index(static_cast<Uint32>(
					vertex_semantic_type))
				<< boost::errinfo_type_info_name(typeid(
					VertexSemanticType).name()));
		}

		return vertex_semantic_type_names[vertex_semantic_type];
	}

	VertexElementType VertexElement::get_vertex_element_type(const String &str)
	{
		Uint32 i;
		VertexElementType vertex_element_type;

		for (i = 0; i < vertex_element_type_datas_count; i++)
		{
			vertex_element_type = static_cast<VertexElementType>(i);

			if (str == get_str(vertex_element_type))
			{
				return vertex_element_type;
			}
		}

		EL_THROW_EXCEPTION(InvalidParameterException()
			<< errinfo_string_value(str)
			<< boost::errinfo_type_info_name(typeid(
				VertexElementType).name()));
	}

	VertexSemanticType VertexElement::get_vertex_semantic_type(
		const String &str)
	{
		Uint32 i;
		VertexSemanticType vertex_semantic_type;

		for (i = 0; i < vertex_semantic_type_names_count; i++)
		{
			vertex_semantic_type = static_cast<VertexSemanticType>(i);

			if (str == get_str(vertex_semantic_type))
			{
				return vertex_semantic_type;
			}
		}

		EL_THROW_EXCEPTION(InvalidParameterException()
			<< errinfo_string_value(str)
			<< boost::errinfo_type_info_name(typeid(
				VertexSemanticType).name()));
	}

	void VertexElement::validate() const
	{
		switch (get_type())
		{
			case vet_half2:
			case vet_half4:
//				OpenGlUtil::check_extension(oet_arb_half_float_vertex);
			case vet_float1:
			case vet_float2:
			case vet_float3:
			case vet_float4:
				if (get_normalize())
				{
					EL_THROW_EXCEPTION(InvalidParameterException());
				}
				return;
			case vet_short2:
			case vet_short4:
			case vet_ushort2:
			case vet_ushort4:
			case vet_byte4:
			case vet_ubyte4:
				return;
			case vet_signed_xyz10_w2:
			case vet_unsigned_xyz10_w2:
//				OpenGlUtil::check_extension(
//					oet_arb_vertex_type_2_10_10_10_rev);
				return;
		}
		/**
		 * We should be never here. If so, it's a programming error,
		 * because we forgot to add all types to the switch or an invalid int
		 * was used (with a type cast)!
		 */
		VALUE_NOT_IN_SWITCH(get_type());
	}

	Uint32 VertexElement::get_size(const VertexElementType vertex_element_type)
	{
		if (vertex_element_type_datas_count <= vertex_element_type)
		{
			EL_THROW_EXCEPTION(InvalidParameterException()
				<< errinfo_range_min(0)
				<< errinfo_range_max(vertex_element_type_datas_count - 1)
				<< errinfo_range_index(static_cast<Uint32>(
					vertex_element_type))
				<< boost::errinfo_type_info_name(typeid(
					VertexElementType).name()));
		}

		return vertex_element_type_datas[vertex_element_type].get_size();
	}

	Uint32 VertexElement::get_element_count(
		const VertexElementType vertex_element_type)
	{
		if (vertex_element_type_datas_count <= vertex_element_type)
		{
			EL_THROW_EXCEPTION(InvalidParameterException()
				<< errinfo_range_min(0)
				<< errinfo_range_max(vertex_element_type_datas_count - 1)
				<< errinfo_range_index(static_cast<Uint32>(
					vertex_element_type))
				<< boost::errinfo_type_info_name(typeid(
					VertexElementType).name()));
		}

		return vertex_element_type_datas[
			vertex_element_type].get_element_count();
	}

	GLenum VertexElement::get_gl_type(
		const VertexElementType vertex_element_type)
	{
		if (vertex_element_type_datas_count <= vertex_element_type)
		{
			EL_THROW_EXCEPTION(InvalidParameterException()
				<< errinfo_range_min(0)
				<< errinfo_range_max(vertex_element_type_datas_count - 1)
				<< errinfo_range_index(static_cast<Uint32>(
					vertex_element_type))
				<< boost::errinfo_type_info_name(typeid(
					VertexElementType).name()));
		}

		return vertex_element_type_datas[vertex_element_type].get_gl_type();
	}

	bool VertexElement::get_supported(
		const VertexElementType vertex_element_type)
	{
		switch (vertex_element_type)
		{
			case vet_float1:
			case vet_float2:
			case vet_float3:
			case vet_float4:
			case vet_short2:
			case vet_short4:
			case vet_ushort2:
			case vet_ushort4:
			case vet_byte4:
			case vet_ubyte4:
				return true;
			case vet_half2:
			case vet_half4:
				return true;//OpenGlUtil::get_extension(oet_arb_half_float_vertex);
			case vet_signed_xyz10_w2:
			case vet_unsigned_xyz10_w2:
				return true;//OpenGlUtil::get_extension(
//					oet_arb_vertex_type_2_10_10_10_rev);
		}
		/**
		 * We should be never here. If so, it's a programming error,
		 * because we forgot to add all types to the switch or an invalid int
		 * was used (with a type cast)!
		 */
		VALUE_NOT_IN_SWITCH(vertex_element_type);
	}

	bool VertexElement::get_signed_elements(
		const VertexElementType vertex_element_type)
	{
		if (vertex_element_type_datas_count <= vertex_element_type)
		{
			EL_THROW_EXCEPTION(InvalidParameterException()
				<< errinfo_range_min(0)
				<< errinfo_range_max(vertex_element_type_datas_count - 1)
				<< errinfo_range_index(static_cast<Uint32>(
					vertex_element_type))
				<< boost::errinfo_type_info_name(typeid(
					VertexElementType).name()));
		}

		return vertex_element_type_datas[
			vertex_element_type].get_signed_elements();
	}

	bool VertexElement::get_dynamic_range(
		const VertexElementType vertex_element_type)
	{
		if (vertex_element_type_datas_count <= vertex_element_type)
		{
			EL_THROW_EXCEPTION(InvalidParameterException()
				<< errinfo_range_min(0)
				<< errinfo_range_max(vertex_element_type_datas_count - 1)
				<< errinfo_range_index(static_cast<Uint32>(
					vertex_element_type))
				<< boost::errinfo_type_info_name(typeid(
					VertexElementType).name()));
		}

		return vertex_element_type_datas[
			vertex_element_type].get_dynamic_range();
	}

	std::ostream& operator<< (std::ostream &str, const VertexElement &value)
	{
		value.log(str);

		return str;
	}

	std::ostream& operator<< (std::ostream &str,
		const VertexElementType &value)
	{
		str << VertexElement::get_str(value);

		return str;
	}

	std::ostream& operator<< (std::ostream &str,
		const VertexSemanticType &value)
	{
		str << VertexElement::get_str(value);

		return str;
	}

}
