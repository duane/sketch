OPT="-O0 -g"
FLAGS="-Wall -Wextra -Werror -Wno-unused-parameter"
INCLUDE="-I./Include -I/System/Library/Frameworks/Carbon.framework/Versions/A/Frameworks/HIToolbox.framework/Versions/A/Headers/"
CC="clang"
$CC $INCLUDE $OPT $FLAGS Source/Darwin/DarwinMain.m -c -o build/DarwinMain.o || exit 1
$CC $INCLUDE $OPT $FLAGS Source/Darwin/SketchApplicationDelegate.m -c -o build/SketchApplicationDelegate.o || exit 1
$CC $INCLUDE $OPT $FLAGS Source/Darwin/SketchView.m -c -o build/SketchView.o || exit 1
$CC $INCLUDE $OPT $FLAGS Source/Darwin/SoftwareDrawable.c -c -o build/SoftwareDrawable.o || exit 1
$CC $INCLUDE $OPT $FLAGS Source/sketch.c -c -o build/sketch.o || exit 1
$CC $INCLUDE $OPT $FLAGS test.c -c -o build/test.o || exit 1
$CC build/DarwinMain.o build/SketchApplicationDelegate.o build/SketchView.o build/SoftwareDrawable.o build/sketch.o build/test.o -o build/test -framework Cocoa || exit 1
tools/darwin/bundle.sh Test test build/test test || exit 1
rm -r build/Test.app;
mv Test.app/ build/Test.app/ || exit 1
