#import "SketchView.h"

@implementation SketchView

- (id)initWithFrame:(NSRect) frame sketchContext:(SketchContext*)ctx{
  if (self = [super initWithFrame: frame]) {
    context = ctx;
    needsInit = YES;
  }
  return self;
}

- (void)drawRect:(NSRect)rect {
  CGContextRef ctxRef = (CGContextRef)[[NSGraphicsContext currentContext] graphicsPort];
  context->drawable->implData = (void*)ctxRef;
  if (needsInit)
    doSetup(context);
  context->draw(context);
}

- (BOOL)isFlipped {
  return YES;
}

@end
