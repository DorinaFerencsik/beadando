cmake_minimum_required(VERSION 3.5.1)
project(beadando)

set(CMAKE_CXX_STANDARD 11)
add_executable(beadando main.c camera.c camera.h draw.c draw.h model.c model.h)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )


target_link_libraries(beadando ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
