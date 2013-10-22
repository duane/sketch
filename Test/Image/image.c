#include <sketch.h>

#include <stdlib.h>
#include <time.h>

uint8_t *buf = NULL;
SImage *img;

void setup(SketchContext *ctx) {
  const size_t size = ctx->width * ctx->height * 3;
  buf = malloc(size);
  srandom(time(NULL));
  for (unsigned i = 0; i < size; i++) {
    buf[i] = random() % 256;
  }
  img = CreateSImage(ctx, buf, ctx->width, ctx->height, RGB);
}

void draw(SketchContext *ctx) {
  image(ctx, img, 0, 0);
}

int main(int argc, char **argv) {
  Drawable *drawable = SoftwareDrawable();
  SketchContext *context = CreateSketchContext(drawable, 100, 100, setup, draw);
  RunSketch(context);
}
