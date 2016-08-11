cmake_minimum_required(VERSION 2.6)
project(SFMLHiWorld)

set(EXECUTABLE_NAME "hiworld")
add_executable(${EXECUTABLE_NAME} src/main.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_SOURCE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

include_directories("${PROJECT_BINARY_DIR}/src")
