/****************************************************************************
 *            prerequisites.hpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#ifndef	UUID_a9b0cc4b_b046_4138_b8f4_d747aac1179a
#define	UUID_a9b0cc4b_b046_4138_b8f4_d747aac1179a

#ifndef	__cplusplus
#error	"Including C++ header in C translation unit!"
#endif	/* __cplusplus */

#include "../platform.h"

#define BOOST_FILESYSTEM_VERSION 2
#define BOOST_THREAD_USE_LIB

#include <string>
#include <limits>
#include <bitset>
#include <boost/array.hpp>
#include <boost/assign.hpp>
#include <boost/cast.hpp>
#include <boost/cstdint.hpp>
#include <boost/foreach.hpp>
#include <boost/type_traits.hpp>
#include <boost/utility.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
#include <cmath>

namespace eternal_lands
{

	typedef boost::uint8_t Uint8;
	typedef boost::uint16_t Uint16;
	typedef boost::uint32_t Uint32;
	typedef boost::uint64_t Uint64;
	typedef boost::int8_t Sint8;
	typedef boost::int16_t Sint16;
	typedef boost::int32_t Sint32;
	typedef boost::int64_t Sint64;

	#define SHARED_PTR(type) typedef boost::shared_ptr<type> type##SharedPtr
	#define VECTOR(type) typedef std::vector<type> type##Vector

	typedef std::string String;

	class HardwareBuffer;
	class VertexElement;
	class VertexStreamDescription;

	SHARED_PTR(HardwareBuffer);

	VECTOR(VertexElement);

}

#endif	/* UUID_a9b0cc4b_b046_4138_b8f4_d747aac1179a */
