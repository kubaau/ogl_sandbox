cmake_minimum_required(VERSION 3.16)

project(ogl_sandbox)

include(../tools/CMakeCommon.cmake)

verifyCppCompiler(8 6)

find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_EXE_LINKER_FLAGS "-Wl,--export-dynamic,--no-as-needed")
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} SegFault)
