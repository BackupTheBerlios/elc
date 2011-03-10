cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

include(FindBoost)
include(CheckCXXCompilerFlag)

set(Boost_USE_STATIC_LIBS off)
set(Boost_USE_MULTITHREADED on)
find_package(Boost 1.40.0)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(EL3D_SYSTEM EL3D_MACOS)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(EL3D_SYSTEM EL3D_LINUX)
elseif (WIN32)
	set(EL3D_SYSTEM EL3D_WIN32)
endif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

if (MSVC)
	CHECK_CXX_COMPILER_FLAG(/fp:fast msvc_fastmath)
	CHECK_CXX_COMPILER_FLAG(-D_SCL_SECURE_NO_WARNINGS msvc_scl_secure)
else (MSVC)
	CHECK_CXX_COMPILER_FLAG(-march=native gcc_native)
	CHECK_CXX_COMPILER_FLAG(-ffast-math gcc_fastmath)
	CHECK_CXX_COMPILER_FLAG(-fvisibility-inlines-hidden gcc_visibility)
	CHECK_CXX_COMPILER_FLAG(-Wall gcc_wall)
	CHECK_CXX_COMPILER_FLAG(-pedantic gcc_pedantic)
endif (MSVC)

if (${gcc_fastmath})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math")
elseif (${msvc_fastmath})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:fast")
endif (${gcc_fastmath})

if (${gcc_visibility})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility-inlines-hidden")
endif (${gcc_visibility})

if (${gcc_wall})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif (${gcc_wall})

if (${gcc_pedantic})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
endif (${gcc_pedantic})

if (${msvc_scl_secure})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_SCL_SECURE_NO_WARNINGS")
endif (${msvc_scl_secure})

if (${gcc_native})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif (${gcc_native})

include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(engine)
add_subdirectory(tests)

