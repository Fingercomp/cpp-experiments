cmake_minimum_required(VERSION 2.6)
project(SFMLHiWorld)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(EXECUTABLE_NAME "hiworld")
add_executable(${EXECUTABLE_NAME} src/main.cpp)

set(RESOURCES_DIR "resources" CACHE STRING "Where to find resources")

configure_file(src/cmake_options.hpp.in ${CMAKE_BINARY_DIR}/generated/cmake_options.hpp)
include_directories("${CMAKE_BINARY_DIR}/generated")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_SOURCE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

include_directories("${PROJECT_SOURCE_DIR}/src")

set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED ON)

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
