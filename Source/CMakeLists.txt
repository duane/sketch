set(SKETCH_LIB_SOURCES sketch.c)

message(STATUS "System name: ${CMAKE_SYSTEM_NAME}")

if("${CMAKE_SYSTEM_NAME}" STREQUAL Darwin)
list(APPEND SKETCH_LIB_SOURCES Darwin/DarwinMain.m Darwin/SketchApplicationDelegate.m Darwin/SketchView.m Darwin/SoftwareDrawable.c)

endif("${CMAKE_SYSTEM_NAME}" STREQUAL Darwin)

message(STATUS "Sketch lib sources: ${SKETCH_LIB_SOURCES}")

add_library(sketch ${SKETCH_LIB_SOURCES})
