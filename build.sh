OPT="-O0 -g"
INCLUDE="-I./c/Include"
CC="clang"
${CC} $INCLUDE $OPT c/Source/Darwin/EventLoop.m -c -o build/EventLoop.o || exit 1
${CC} $INCLUDE $OPT c/Source/Darwin/SketchApplicationDelegate.m -c -o build/SketchApplicationDelegate.o || exit 1
${CC} $INCLUDE $OPT c/Source/Darwin/SketchView.m -c -o build/SketchView.o || exit 1
${CC} $INCLUDE $OPT c/Source/Darwin/SoftwareDrawable.m -c -o build/SoftwareDrawable.o || exit 1
${CC} $INCLUDE $OPT c/Source/sketch.c -c -o build/sketch.o || exit 1
${CC} $INCLUDE $OPT test.c -c -o build/test.o || exit 1
${CC} build/EventLoop.o build/SketchApplicationDelegate.o build/SketchView.o build/SoftwareDrawable.o build/sketch.o build/test.o -o build/test -framework Cocoa || exit 1
tools/darwin/bundle.sh Test test build/test test || exit 1
