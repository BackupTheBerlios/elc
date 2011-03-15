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

//#include "../platform.h"

#define BOOST_FILESYSTEM_VERSION 2
#define BOOST_THREAD_USE_LIB

#include <string>
#include <limits>
#include <bitset>
#include <iostream>
#include <boost/array.hpp>
#include <boost/cast.hpp>
#include <boost/cstdint.hpp>
#include <boost/foreach.hpp>
#include <boost/type_traits.hpp>
#include <boost/utility.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include <stack>

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

	#define SHARED_PTR_NAME(type, name) typedef boost::shared_ptr<type> name##SharedPtr
	#define ARRAY_NAME(type, N, name) typedef boost::array<type, N> name##Array##N
	#define VECTOR_NAME(type, name) typedef std::vector<type> name##Vector

	#define SHARED_PTR(type) SHARED_PTR_NAME(type, type)
	#define ARRAY(type, N) ARRAY_NAME(type, N, type)
	#define VECTOR(type) VECTOR_NAME(type, type)

	ARRAY_NAME(float, 6, Float);
	ARRAY(Uint16, 16);

	typedef std::string String;
	typedef std::bitset<32> BitSet32;
	typedef std::bitset<16> BitSet16;

	class BoundedObject;
	class HardwareBuffer;
	class RStarTree;
	class RStarTreeNode;
	class VertexElement;
	class VertexStreamDescription;

	typedef BoundedObject* BoundedObjectPtr;
	typedef RStarTree* RStarTreePtr;
	typedef RStarTreeNode* RStarTreeNodePtr;

	typedef std::stack<RStarTreeNodePtr> RStarTreeNodePtrStack;

	SHARED_PTR(HardwareBuffer);

	VECTOR(VertexElement);
	VECTOR(BoundedObjectPtr);
	VECTOR(RStarTreeNodePtr);

}

#endif	/* UUID_a9b0cc4b_b046_4138_b8f4_d747aac1179a */
