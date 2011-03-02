/****************************************************************************
 *            extendedexception.hpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#ifndef	UUID_2895e87c_d039_42e6_8628_577d13de5d2a
#define	UUID_2895e87c_d039_42e6_8628_577d13de5d2a

#ifndef	__cplusplus
#error	"Including C++ header in C translation unit!"
#endif	/* __cplusplus */

#include <boost/exception/all.hpp>

namespace eternal_lands
{

	class IoErrorException: public virtual ::std::exception,
		public virtual ::boost::exception {};
	class FileNotFoundException: public virtual IoErrorException {};
	class ReadErrorException: public virtual IoErrorException {};
	class InvalidParameterException: public virtual ::std::exception,
		public virtual ::boost::exception {};
	class ItemNotFoundException: public virtual InvalidParameterException {};
	class DuplicateItemException: public virtual InvalidParameterException {};
	class BufferTooSmallException: public virtual InvalidParameterException {};
	class NullPtrException: public virtual InvalidParameterException {};
	class InternalErrorException: public virtual ::std::exception,
		public virtual ::boost::exception {};
	class EnumNotInSwitchException: public virtual InternalErrorException {};
	class NotImplementedException: public virtual InternalErrorException {};
	class UnkownFormatException: public virtual InvalidParameterException,
		public virtual IoErrorException, public virtual NotImplementedException {};
	class BadCastException: public virtual ::std::bad_cast,
		public virtual ::boost::exception {};
	class RangeErrorException: public virtual InvalidParameterException {};
	class ArraySizeErrorException: public virtual RangeErrorException {};
	class InvalidTokenException: public virtual InvalidParameterException {};

	typedef boost::error_info<struct errinfo_message_, String> errinfo_message;
	typedef boost::error_info<struct errinfo_file_position_, Uint64> errinfo_file_position;
	typedef boost::error_info<struct errinfo_value_, Uint32> errinfo_value;
	typedef boost::error_info<struct errinfo_size_, Uint64> errinfo_size;
	typedef boost::error_info<struct errinfo_item_id_, Uint32> errinfo_item_id;
	typedef boost::error_info<struct errinfo_item_name_, String> errinfo_item_name;
	typedef boost::error_info<struct errinfo_string_value_, String> errinfo_string_value;
	typedef boost::error_info<struct errinfo_page_name_, String> errinfo_page_name;
	typedef boost::error_info<struct errinfo_archive_name_, String> errinfo_archive_name;
	typedef boost::error_info<struct errinfo_resource_name_, String> errinfo_resource_name;
	typedef boost::error_info<struct errinfo_resource_type_name_, String>
		errinfo_resource_type_name;
	typedef boost::error_info<struct errinfo_range_min_, Sint64> errinfo_range_min;
	typedef boost::error_info<struct errinfo_range_max_, Sint64> errinfo_range_max;
	typedef boost::error_info<struct errinfo_range_index_, Sint64> errinfo_range_index;
	typedef boost::error_info<struct errinfo_float_range_min_, float> errinfo_float_range_min;
	typedef boost::error_info<struct errinfo_float_range_max_, float> errinfo_float_range_max;
	typedef boost::error_info<struct errinfo_float_range_index_, float>
		errinfo_float_range_index;
	typedef boost::error_info<struct errinfo_array_size_0_, Uint64> errinfo_array_size_0;
	typedef boost::error_info<struct errinfo_array_size_1_, Uint64> errinfo_array_size_1;
	typedef boost::error_info<struct errinfo_array_size_2_, Uint64> errinfo_array_size_2;

#define EL_THROW_EXCEPTION(exception)	\
	throw exception <<\
	::boost::throw_function(BOOST_CURRENT_FUNCTION) <<\
	::boost::throw_file(__FILE__) <<\
	::boost::throw_line((int)__LINE__)

#define	VALUE_NOT_IN_SWITCH(type)	\
	EL_THROW_EXCEPTION(::eternal_lands::BadCastException()	\
		<< ::eternal_lands::errinfo_value(static_cast<Uint32>(type))	\
		<< ::boost::errinfo_type_info_name(typeid(type).name()))

}

#endif	/* UUID_2895e87c_d039_42e6_8628_577d13de5d2a */
