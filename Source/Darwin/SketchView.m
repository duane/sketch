#import "SketchView.h"

#include <internal.h>

@implementation SketchView

- (id)initWithFrame:(NSRect) frame sketchContext:(SketchContext*)ctx{
  if (self = [super initWithFrame: frame]) {
    context = ctx;
    needsInit = YES;

    if ([self window] != nil)
      [[self window] setAcceptsMouseMovedEvents:YES];

    timer = [NSTimer scheduledTimerWithTimeInterval:1/60.0
                                             target:self
                                           selector:@selector(mainLoop)
                                           userInfo:nil
                                            repeats:YES];
    [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSEventTrackingRunLoopMode];
    tracking = [[NSTrackingArea alloc]
                initWithRect:[self bounds]
                     options: (NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved | NSTrackingActiveAlways)
                       owner:self
                    userInfo:nil];
    [self addTrackingArea:tracking];
  }
  return self;
}

- (void)drawRect:(NSRect)rect {
  CGContextRef ctxRef = (CGContextRef)[[NSGraphicsContext currentContext] graphicsPort];
  context->drawable->implData = (void*)ctxRef;
  if (needsInit) {
    doSetup(context);
    needsInit = false;
  }
  fill(context, context->fillColor.v1, context->fillColor.v2, context->fillColor.v3);
  stroke(context, context->strokeColor.v1, context->strokeColor.v2, context->strokeColor.v3);
  context->draw(context);
}

- (BOOL)isFlipped {
  return YES;
}

- (BOOL)acceptsFirstMouse {
  return YES;
}

- (BOOL)acceptsFirstResponder {
  return YES;
}

- (void)mouseDown:(NSEvent*)theEvent {
  sendMouseDown(context, LEFT);
}

- (void)mouseUp:(NSEvent*)event {
  sendMouseUp(context);
}

- (void)mouseMoved:(NSEvent*)event {
  mouseMoved = YES;
  mouse = [event locationInWindow];
}

- (void)mouseDragged:(NSEvent*)event {
  mouseDragged = YES;
  mouse = [event locationInWindow];
}

- (void)handleEvents {
  NSRect bounds = [self bounds];
  mouse.y = bounds.size.height - mouse.y; // View coordinate system is flipped; mouse locations use the unflipped coordinate system.
  
  advanceMouseFrame(context);
  if (mouseMoved) {
    sendMouseMoved(context, mouse.x, mouse.y);
    mouseMoved = NO;
  }
  if (mouseDragged) {
    sendMouseDragged(context, mouse.x, mouse.y);
    mouseDragged = NO;
  }
}

- (void)mainLoop {
  [self handleEvents];
  [self setNeedsDisplay:YES];
}

@end
