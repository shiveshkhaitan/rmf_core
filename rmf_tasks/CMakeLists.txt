cmake_minimum_required(VERSION 3.5.0)

project(rmf_tasks)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

find_package(ament_cmake REQUIRED)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if(NOT CMAKE_BUILD_TYPE)
  # Use the Release build type by default if the user has not specified one
  set(CMAKE_BUILD_TYPE Release)
endif()

include(GNUInstallDirs)

find_package(rmf_utils REQUIRED)
find_package(rmf_traffic REQUIRED)
find_package(rmf_task_msgs REQUIRED)

# file(GLOB lib_srs "src/*.cpp")
# add_library(rmf_tasks SHARED
#   ${lib_srs}
# )

# target_link_libraries(rmf_tasks
#   rmf_utils::rmf_utils
# )

# target_include_directories(rmf_tasks
#   PUBLIC
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#     $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
# )

add_executable(test_poly
  src/main.cpp
)

install(
  DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  TARGETS test_poly
  RUNTIME DESTINATION lib/rmf_tasks
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

ament_package()
