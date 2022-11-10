cmake_minimum_required(VERSION 3.16)
project(CADCourse LANGUAGES CXX)

find_package(glfw3 REQUIRED) # glfw
find_package(OpenGL REQUIRED) # opengl
find_package(GLEW REQUIRED) # glew
find_package(GLUT REQUIRED) # GLUT

include_directories(/usr/local/include)
include_directories(
    src/HalfEdgeDS
    src/EulerOp
    src/Sweep
    src/Draw
)

add_executable(CADCourse
    src/main.cpp
    src/HalfEdgeDS/HalfEdgeDS.cpp
    src/EulerOp/EulerOp.cpp
    src/Sweep/Sweep.cpp
    src/Draw/Draw.cpp
)

target_link_libraries(
    CADCourse
    glfw
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLUT_LIBRARIES}
)