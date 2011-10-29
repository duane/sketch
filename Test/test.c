#include <sketch.h>
#include <stdio.h>

void setup(SketchContext *ctx) {
}

void draw(SketchContext *ctx) {
  if (ctx->keyPressed)
    fill(ctx, 1, 1, 1);
  else
    fill(ctx, 0, 0, 0);
  rect(ctx, 25, 25, 50, 50);
}

int main(int argc, char **argv) {
  Drawable *drawable = SoftwareDrawable();
  SketchContext *context = CreateSketchContext(drawable, 100, 100, setup, draw);
  RunSketch(context);
  return 0;
}

