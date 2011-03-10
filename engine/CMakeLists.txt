project(EL3D)

# project options
set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 9)
set(${PROJECT_NAME}_PATCH_LEVEL 0)

math(EXPR ${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_MAJOR_VERSION} * 10000 + ${${PROJECT_NAME}_MINOR_VERSION} * 100 + ${${PROJECT_NAME}_PATCH_LEVEL}")
set(${PROJECT_NAME}_VERSION_STRING "${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_LEVEL}")

file(GLOB header_files *.hpp)
file(GLOB cpp_files *.cpp)
list(APPEND el3d_cpp_files ${cpp_files})
list(APPEND el3d_header_files ${header_files})

add_library(el3d ${el3d_cpp_files} ${el3d_header_files})
target_link_libraries(el3d ${Boost_LIBRARIES})

set_target_properties(el3d PROPERTIES VERSION ${${PROJECT_NAME}_VERSION_STRING})

