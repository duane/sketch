#import <Cocoa/Cocoa.h>
#include <sketch.h>

#import "SketchView.h"

@interface SketchApplicationDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate> {
  NSWindow *window;
  NSMenu *menu;
  SketchView *sketchView;
  SketchContext *context;
}

- (id)initWithSketchContext:(SketchContext*)ctx;

@end
