#include <sketch.h>
#include <math.h>
#include <stdio.h>

static int x;

void setup(SketchContext *ctx) {
  x = 0;
}

void draw(SketchContext *ctx) {
  ellipse(ctx, x, ctx->height / 2, 50, 50);
  x = (x + 1) % ctx->width;
}

int main(int argc, char **argv) {
  Drawable *drawable = SoftwareDrawable();
  SketchContext *context = CreateSketchContext(drawable, 500, 500, setup, draw);
  RunSketch(context);
  return 0;
}

