#include <sketch.h>
#include <math.h>
#include <stdio.h>

void setup(SketchContext *ctx) {
}

void draw(SketchContext *ctx) {
  smooth(ctx);
  noFill(ctx);
  bezier(ctx, 85, 20, 10, 10, 90, 90, 15, 80);
  fill(ctx, 255, 255, 255);
  int steps = 10;
  for (int i = 0; i <= steps; i++) {
    double t = (double)i / steps;
    double x = bezierPoint(85, 10, 90, 15, t);
    double y = bezierPoint(20, 10, 90, 80, t);
    ellipse(ctx, x, y, 5, 5);
  }
}

int main(int argc, char **argv) {
  Drawable *drawable = SoftwareDrawable();
  SketchContext *context = CreateSketchContext(drawable, 100, 100, setup, draw);
  RunSketch(context);
  return 0;
}

