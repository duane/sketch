#import "SketchView.h"

#include <Events.h> // HIToolbox, for key codes.

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

- (void)keyDown:(NSEvent*)event {
  unsigned short inKeyCode = [event keyCode];
  
  char key;
  uint32_t unicodeKey;
  uint32_t keyCode;
  if (inKeyCode == 0x0) {
    NSString *characters = [event characters];
    unichar uc = [characters characterAtIndex:0];
    if (uc < 0x80) {
      key = uc;
      unicodeKey = uc;
      keyCode = 0;
    } else {
      key = UNICODED;
      unicodeKey = uc;
      keyCode = 0;
    }
  } else {
    key = CODED;
    unicodeKey = CODED;
    switch(inKeyCode) {
      case kVK_F1:
        keyCode = sVK_F1;
        break;
      case kVK_F2:
        keyCode = sVK_F2;
        break;
      case kVK_F3:
        keyCode = sVK_F3;
        break;
      case kVK_F4:
        keyCode = sVK_F4;
        break;
      case kVK_F5:
        keyCode = sVK_F5;
        break;
      case kVK_F6:
        keyCode = sVK_F6;
        break;
      case kVK_F7:
        keyCode = sVK_F7;
        break;
      case kVK_F8:
        keyCode = sVK_F8;
        break;
      case kVK_F9:
        keyCode = sVK_F9;
        break;
      case kVK_F10:
        keyCode = sVK_F10;
        break;
      case kVK_F11:
        keyCode = sVK_F11;
        break;
      case kVK_F12:
        keyCode = sVK_F12;
        break;
      case kVK_F13:
        keyCode = sVK_F13;
        break;
      case kVK_F14:
        keyCode = sVK_F14;
        break;
      case kVK_F15:
        keyCode = sVK_F15;
        break;
      case kVK_F16:
        keyCode = sVK_F16;
        break;
      case kVK_F17:
        keyCode = sVK_F17;
        break;
      case kVK_F18:
        keyCode = sVK_F18;
        break;
      case kVK_F19:
        keyCode = sVK_F19;
        break;
      case kVK_F20:
        keyCode = sVK_F20;
        break;
      
      case kVK_UpArrow:
        keyCode = sVK_Up;
        break;
      case kVK_DownArrow:
        keyCode = sVK_Down;
        break;
      case kVK_LeftArrow:
        keyCode = sVK_Left;
        break;
      case kVK_RightArrow:
        keyCode = sVK_Right;
        break;
      
      case kVK_CapsLock:
        keyCode = sVK_CapsLock;
        break;
      case kVK_Delete:
        key = unicodeKey = '\b';
        keyCode = sVK_Delete;
        break;
      case kVK_End:
        keyCode = sVK_End;
        break;
      case kVK_ANSI_KeypadEnter:
        key = unicodeKey = '\n';
        keyCode = sVK_Enter;
        break;
      case kVK_Escape:
        key = unicodeKey = '\e';
        keyCode = sVK_Escape;
        break;
      case kVK_ForwardDelete:
        keyCode = sVK_ForwardDelete;
        break;
      case kVK_Home:
        keyCode = sVK_Home;
        break;
      case kVK_PageDown:
        keyCode = sVK_PageDown;
        break;
      case kVK_PageUp:
        keyCode = sVK_PageUp;
        break;
      case kVK_Return:
        key = keyCode = '\n'; // not technically correct, but it's compatible with Processing.
        keyCode = sVK_Return;
        break;
      case kVK_Space:
        key = unicodeKey = ' ';
        keyCode = sVK_Space;
        break;
      case kVK_Tab:
        key = unicodeKey = '\t';
        keyCode = sVK_Tab; 
        break;
      default:
        keyCode = sVK_Other;
        break;
    }
  }

  sendKeyDown(context, key, unicodeKey, keyCode, [event isARepeat]);
}

- (void)keyUp:(NSEvent*)event {
  sendKeyUp(context);
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
