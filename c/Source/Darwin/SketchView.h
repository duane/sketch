#import <Cocoa/Cocoa.h>

#import <sketch.h>

@interface SketchView : NSView {
  SketchContext *context;
  BOOL needsInit;
  NSTimer *timer;
  NSTrackingArea *tracking;

  // event-related state
  BOOL mouseMoved, mouseDragged;
  NSPoint mouse;
}

- (id)initWithFrame:(NSRect) frame sketchContext:(SketchContext*) ctx;

@end
