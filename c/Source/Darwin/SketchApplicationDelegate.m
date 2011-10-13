#import "SketchApplicationDelegate.h"

@implementation SketchApplicationDelegate : NSObject

- (id)initWithSketchContext: (SketchContext*)ctx {
  if (self = [super init]) {
    context = ctx;
  }
  return self;
}

- (void)createMenu: (NSString *)appName {
  NSMenu *appMenu = [[NSMenu alloc] initWithTitle: appName];
  [menu addItem: [[NSMenuItem alloc] initWithTitle: @"About sketch..." action: NULL keyEquivalent: @""]];
  NSMenuItem *appMenuItem = [[NSMenuItem alloc] initWithTitle: appName action: NULL keyEquivalent: @""];
  [appMenuItem setSubmenu: appMenu];  

  [[NSApp menu] addItem: appMenuItem];

  [NSApp performSelector:NSSelectorFromString(@"setAppleMenu:") withObject:appMenu];
}

- (void)applicationDidFinishLaunching: (NSNotification *)notification {
  // the event loop starts here.
  // first initialize the window.
  NSLog(@"Application will finish launching.");

  [self createMenu: @"sketch"];

  NSLog(@"Menu created.");

  NSRect frame = [[NSScreen mainScreen] frame];
  uint32_t x = (frame.size.width - context->width) / 2;
  uint32_t y = (frame.size.height - context->height) / 2;
  NSRect windowRect = NSMakeRect(x, y, context->width, context->height);
  window = [[[NSWindow alloc] initWithContentRect: windowRect styleMask: (NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask) backing: NSBackingStoreBuffered defer: YES] retain];
  [window setDelegate: self];
  NSLog(@"Window created.");
  
  sketchView = [[SketchView alloc] initWithFrame: windowRect sketchContext: context];
  [window setContentView: sketchView];
  NSLog(@"Sketch view initiated.");

  [window makeKeyAndOrderFront:self];
  NSLog(@"Window made key and ordered front.");
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
