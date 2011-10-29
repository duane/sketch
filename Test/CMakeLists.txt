add_executable(test MACOSX_BUNDLE test.c)


find_library(COCOA_FRAMEWORK Cocoa)
target_link_libraries(test sketch ${COCOA_FRAMEWORK})
