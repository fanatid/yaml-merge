cmake_minimum_required (VERSION 2.6)

project (yaml-merge)

# https://github.com/rkrhlikar/yaml-cpp-issue-612-example
set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "Enable testing")
add_subdirectory(yaml-cpp)

include_directories(yaml-cpp/include)
add_executable(yaml-merge main.cpp)
target_link_libraries(yaml-merge yaml-cpp)
