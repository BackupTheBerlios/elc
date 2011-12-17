/****************************************************************************
 *            hardwarebuffer.cpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#include "hardwarebuffer.hpp"

namespace eternal_lands
{

	HardwareBuffer::HardwareBuffer()
	{
		ELglGenBuffers(1, &m_id);
	}

	HardwareBuffer::~HardwareBuffer() throw()
	{
		ELglDeleteBuffers(1, &m_id);
	}

	void HardwareBuffer::set_size(const HardwareBufferType type,
		const Uint64 size, const HardwareBufferUsageType usage)
	{
		m_size = size;
		ELglBufferData(type, size, 0, usage);
	}

	void HardwareBuffer::bind(const HardwareBufferType type)
	{
		ELglBindBuffer(type, m_id);
	}

	void HardwareBuffer::unbind(const HardwareBufferType type)
	{
		ELglBindBuffer(type, 0);
	}

	void* HardwareBuffer::map(const HardwareBufferType type,
		const HardwareBufferAccessType access)
	{
		return ELglMapBuffer(type, access);
	}

	bool HardwareBuffer::unmap(const HardwareBufferType type)
	{
		return ELglUnmapBuffer(type) == GL_TRUE;
	}

}

