cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(tests)

include(FindBoost)

set(Boost_USE_STATIC_LIBS off)
set(Boost_USE_MULTITHREADED on)

find_package(Boost 1.40.0 COMPONENTS unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(../engine)

add_definitions(-DBOOST_TEST_DYN_LINK)

ENABLE_TESTING()

link_directories(${TESTS_BINARY_DIR})

file(GLOB tests *.cpp)

foreach(FILE_NAME ${tests})
	file(RELATIVE_PATH PROG_NAME ${CMAKE_CURRENT_SOURCE_DIR} ${FILE_NAME})

	string(REPLACE ".cpp" "" PROG_NAME ${PROG_NAME})

	add_executable(${PROG_NAME} WIN32 ${files_cpp} ${files_hpp} ${FILE_NAME})

	target_link_libraries(${PROG_NAME} el3d)
	target_link_libraries(${PROG_NAME} ${Boost_LIBRARIES})

	add_test(${PROG_NAME} ${EXECUTABLE_OUTPUT_PATH}/${PROG_NAME})
endforeach(FILE_NAME)

#
#file(GLOB tests_files_cpp *.cpp)
#file(GLOB tests_files_hpp *.hpp)
#
#add_executable(tests WIN32 ${files_cpp} ${files_hpp} ${tests_files_cpp} ${tests_files_hpp})
#target_link_libraries(tests ${Boost_LIBRARIES})
#add_test(tests ${EXECUTABLE_OUTPUT_PATH}/test)

