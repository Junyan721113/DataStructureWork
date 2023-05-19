cmake_minimum_required (VERSION 3.8)

project ("DataStructureWork")

find_package(OpenCV REQUIRED)
# opencv include path: /usr/local/include/opencv4

link_libraries(${OpenCV_LIBS})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")

add_executable (rain "rain.cpp")