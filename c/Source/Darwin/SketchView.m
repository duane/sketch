#import "SketchView.h"

@implementation SketchView

- (id)initWithFrame:(NSRect) frame sketchContext:(SketchContext*)ctx{
  if (self = [super initWithFrame: frame]) {
    context = ctx;
    needsInit = YES;
    timer = [NSTimer scheduledTimerWithTimeInterval:1/60.0
                                             target:self
                                           selector:@selector(mainLoop)
                                           userInfo:nil
                                            repeats:YES];
    [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSEventTrackingRunLoopMode];
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

- (void)mainLoop {
  [self setNeedsDisplay:YES];
}

@end
