#import <Cocoa/Cocoa.h>

#import <sketch.h>

@interface SketchView : NSView {
  SketchContext *context;
  BOOL needsInit;
}

- (id)initWithFrame:(NSRect) frame sketchContext:(SketchContext*) ctx;

@end
