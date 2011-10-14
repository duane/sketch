#include <sketch.h>
#include <stdlib.h>

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

  return context;
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
  ctx->drawable->stroke(ctx, v1, v2, v3);
}

extern void smooth(SketchContext *ctx) {
  ctx->drawable->smooth(ctx);
}

extern void noSmooth(SketchContext *ctx) {
  ctx->drawable->noSmooth(ctx);
}

extern void background(SketchContext *ctx, double v1, double v2, double v3) {
  ctx->drawable->background(ctx, v1, v2, v3);
}

extern void doSetup(SketchContext *ctx) {
  stroke(ctx, 0.0, 0.0, 0.0);
  fill(ctx, 255.0, 255.0, 255.0);
  background(ctx, 214, 214, 214);
  noSmooth(ctx);  

  ctx->setup(ctx);
}

