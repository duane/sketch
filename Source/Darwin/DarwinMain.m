#import <sketch.h>
#import <Cocoa/Cocoa.h>
#import "SketchApplicationDelegate.h"

void RunSketch(SketchContext *context) {
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
  NSApplication *application = [NSApplication sharedApplication];
  
  SketchApplicationDelegate *appDelegate = [[[SketchApplicationDelegate alloc] initWithSketchContext: context] autorelease];
  
  [application setDelegate: appDelegate];
  [application run];
  
  [pool drain];
}


