cmake_minimum_required (VERSION 3.8)

project ("DataStructureWork")

find_package(OpenCV REQUIRED)
# opencv version: 4.7.0

link_libraries(${OpenCV_LIBS})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")

add_executable(rain "rain.cpp")
