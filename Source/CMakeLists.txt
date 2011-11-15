set(SKETCH_LIB_SOURCES sketch.c)

message(STATUS "System name: ${CMAKE_SYSTEM_NAME}")

if("${CMAKE_SYSTEM_NAME}" STREQUAL Darwin)
list(APPEND SKETCH_LIB_SOURCES Darwin/DarwinMain.m Darwin/SketchApplicationDelegate.m Darwin/SketchView.m Darwin/SoftwareDrawable.c)

endif("${CMAKE_SYSTEM_NAME}" STREQUAL Darwin)

message(STATUS "Sketch lib sources: ${SKETCH_LIB_SOURCES}")

add_library(sketch SHARED ${SKETCH_LIB_SOURCES})
find_library(COCOA_FRAMEWORK Cocoa)
target_link_libraries(sketch ${COCOA_FRAMEWORK})
