#import "SketchApplicationDelegate.h"

@implementation SketchApplicationDelegate : NSObject

- (id)initWithSketchContext: (SketchContext*)ctx {
  if ((self = [super init])) {
    context = ctx;
  }
  return self;
}

- (void)applicationDidFinishLaunching: (NSNotification *)notification {
  NSRect frame = [[NSScreen mainScreen] frame];
  uint32_t x = (frame.size.width - context->width) / 2;
  uint32_t y = (frame.size.height - context->height) / 2;
  NSRect windowRect = NSMakeRect(x, y, context->width, context->height);
  window = [[[NSWindow alloc] initWithContentRect: windowRect styleMask: (NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask) backing: NSBackingStoreBuffered defer: YES] retain];
  [window setDelegate: self];

  sketchView = [[SketchView alloc] initWithFrame: windowRect sketchContext: context];
  [window setContentView: sketchView];

  [window makeKeyAndOrderFront:self];
}

- (void)windowWillClose: (NSNotification *)notification {
  [[NSApplication sharedApplication] terminate: self];
}
 
- (void)dealloc {
  [super dealloc];
  [window dealloc];
  [sketchView dealloc];
}

@end
