#include <sketch.h>
#include <stdlib.h>

#include <assert.h>

static void empty(SketchContext *ctx) {}

extern SketchContext *CreateSketchContext(Drawable *drawable, uint32_t width, uint32_t height, void (*setup)(SketchContext*), void (*draw)(SketchContext*)) {
  SketchContext *context = malloc(sizeof(SketchContext));
  context->width = width;
  context->height = height;
  context->setup = setup;
  context->draw = draw;
  context->drawable = drawable;
  
  context->ellipseMode = CENTER;
  context->rectMode = CORNER;
 
  context->stroke = context->fill = true;

  context->mousePressedf = context->mouseReleased = context->mouseClicked = context->mouseMoved = context->mouseDragged = empty;
  context->mousePressed = false;
  
  
  context->keyPressedf = context->keyReleased = context->keyTyped = empty;
  context->keyPressed = false;  

  return context;
}

extern void RegisterMouse(SketchContext *ctx, MouseEvent event, void (*mouseCallback)(SketchContext*)) {
  switch(event) {
    case MousePressed:
      ctx->mousePressedf = mouseCallback;
      break;
    case MouseReleased:
      ctx->mouseReleased = mouseCallback;
      break;
    case MouseClicked:
      ctx->mouseClicked = mouseCallback;
      break;
    case MouseMoved:
      ctx->mouseMoved = mouseCallback;
    case MouseDragged:
      ctx->mouseDragged = mouseCallback;
      break;
    default:
      break;
  }
}

extern void RegisterKey(SketchContext *ctx, KeyEvent event, void (*keyCallback)(SketchContext*)) {
  switch(event) {
    case KeyPressed:
      ctx->keyPressedf = keyCallback;
      break;
    case KeyReleased:
      ctx->keyReleased = keyCallback;
      break;
    default:
      break;
  }
}

extern SImage *CreateSImage(SketchContext *ctx, uint8_t *buf, size_t width, size_t height, ImageFormat format) {
  SImage *image = malloc(sizeof(SImage));
  assert(image);
  image->buf = buf;
  image->width = width;
  image->height = height;
  image->format = format;
  ctx->drawable->CreateSImage(ctx, image);
  return image;
}

extern void image(SketchContext *ctx, SImage *image, double x, double y) {
  ctx->drawable->image(ctx, image, x, y, image->width, image->height);
}

extern double min(double a, double b) {
  return a < b ? a : b;
}

extern double max(double a, double b) {
  return a > b ? a : b;
}

extern double constrain(double v, double lower, double upper) {
  if (v < lower)
    return lower;
  if (v > upper)
    return upper;
  return v;
}

extern void ellipse(SketchContext *ctx, double x, double y, double width, double height) {
  ctx->drawable->ellipse(ctx, x, y, width, height);
}

extern void arc(SketchContext *ctx, double x, double y, double width, double height, double start, double stop) {
  ctx->drawable->arc(ctx, x, y, width, height, start, stop);
}

extern void line(SketchContext *ctx, double x1, double y1, double x2, double y2) {
  ctx->drawable->line(ctx, x1, y1, x2, y2);
}

extern void point(SketchContext *ctx, double x, double y) {
  ctx->drawable->point(ctx, x, y);
}

extern void quad(SketchContext *ctx, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
  ctx->drawable->quad(ctx, x1, y1, x2, y2, x3, y3, x4, y4);
}

extern void rect(SketchContext *ctx, double x, double y, double width, double height) {
  ctx->drawable->rect(ctx, x, y, width, height);
}

extern void triangle(SketchContext *ctx, double x1, double y1, double x2, double y2, double x3, double y3) {
  ctx->drawable->triangle(ctx, x1, y1, x2, y2, x3, y3);
}

extern void bezier(SketchContext *ctx, double x1, double y1, double cx1, double cy1, double cx2, double cy2, double x2, double y2) {
  ctx->drawable->bezier(ctx, x1, y1, cx1, cy1, cx2, cy2, x2, y2);
}

extern void fill(SketchContext *ctx, double v1, double v2, double v3) {
  ctx->fill = true;
  v1 = constrain(v1, 0.0, 1.0);
  v2 = constrain(v2, 0.0, 1.0);
  v3 = constrain(v3, 0.0, 1.0);
  double a = 1.0;
  ctx->fillColor.v1 = v1;
  ctx->fillColor.v2 = v2;
  ctx->fillColor.v3 = v3;
  ctx->fillColor.a = a;
  ctx->drawable->fill(ctx, v1, v2, v3);
}

extern void stroke(SketchContext *ctx, double v1, double v2, double v3) {
  ctx->fill = true;
  v1 = constrain(v1, 0.0, 1.0);
  v2 = constrain(v2, 0.0, 1.0);
  v3 = constrain(v3, 0.0, 1.0);
  double a = 1.0;
  ctx->strokeColor.v1 = v1;
  ctx->strokeColor.v2 = v2;
  ctx->strokeColor.v3 = v3;
  ctx->strokeColor.a = a;
  ctx->drawable->stroke(ctx, v1, v2, v3);
}

extern void noFill(SketchContext *ctx) {
  ctx->fill = false;
}

extern void noStroke(SketchContext *ctx) {
  ctx->stroke = false;
}

extern void smooth(SketchContext *ctx) {
  ctx->drawable->smooth(ctx);
}

extern void noSmooth(SketchContext *ctx) {
  ctx->drawable->noSmooth(ctx);
}

extern void ellipseMode(SketchContext *ctx, uint32_t mode) {
  if (mode > CORNERS)
    mode = CENTER;
  ctx->ellipseMode = mode;
}

extern void rectMode(SketchContext *ctx, uint32_t mode) {
  if (mode > CORNERS)
    mode = CORNER;
  ctx->rectMode = mode;
}

extern void background(SketchContext *ctx, double v1, double v2, double v3) {
  ctx->drawable->background(ctx, v1, v2, v3);
}

extern double bezierPoint(double a, double b, double c, double d, double t) {
// B(t) = (1-t)^(3)P_0 + 3(1-t)^(2)tP_1 + 3(1-t)t^(2)P_2 + t^(3)P_3
  double t2 = t * t;
  double t3 = t2 * t;
  return ((-t3 + 3 * t2 - 3 * t + 1) * a) + (3 * (t2 - 2 * t + 1) * t * b) + (3 * (1 - t) * t2 * c) + (t3 * d);
}

extern void doSetup(SketchContext *ctx) {
  stroke(ctx, 0.0, 0.0, 0.0);
  fill(ctx, 255.0, 255.0, 255.0);
  background(ctx, 214, 214, 214);
  noSmooth(ctx);  

  ctx->setup(ctx);
}

