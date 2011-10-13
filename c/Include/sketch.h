#ifndef __INCLUDE_CONTEXT_H__
#define __INCLUDE_CONTEXT_H__

#include <stdint.h>
#include <stdbool.h>

const static uint32_t CENTER = 0;
const static uint32_t RADIUS = 1;
const static uint32_t CORNER = 2;
const static uint32_t CORNERS = 3;

struct SketchContext;

typedef struct {
  void (*ellipse)(struct SketchContext*, double, double, double, double);
  void (*arc)(struct SketchContext*, double, double, double, double, double, double);
  void (*line)(struct SketchContext*, double, double, double, double);
  void (*point)(struct SketchContext*, double, double);
  void (*quad)(struct SketchContext*, double, double, double, double, double, double, double, double);
  void (*rect)(struct SketchContext*, double, double, double, double);
  void (*triangle)(struct SketchContext*, double, double, double, double, double, double);

  void (*bezier)(struct SketchContext*, double, double, double, double, double, double, double, double);

  void (*fill)(struct SketchContext*, double, double, double);
  void (*stroke)(struct SketchContext*, double, double, double);
  void (*background)(struct SketchContext*, double, double, double);

  void (*smooth)(struct SketchContext*);
  void (*noSmooth)(struct SketchContext*);

  void *implData;
} Drawable;

typedef struct SketchContext {
  Drawable *drawable;
  void (*setup)(struct SketchContext*);
  void (*draw)(struct SketchContext*);
 
  uint32_t width, height;
  uint32_t ellipseMode, rectMode; 
  
  bool fill, stroke;
} SketchContext;

extern SketchContext *CreateSketchContext(Drawable *drawable, uint32_t width, uint32_t height, void (*setup)(SketchContext*), void (*draw)(SketchContext*));
extern Drawable *SoftwareDrawable(void);

extern void RunSketch(SketchContext *context);

extern void ellipse(SketchContext *ctx, double x, double y, double height, double width);
extern void arc(SketchContext *ctx, double x, double y, double width, double height, double start, double stop);
extern void line(SketchContext *ctx, double x1, double y1, double x2, double y2);
extern void point(SketchContext *ctx, double x, double y);
extern void quad(SketchContext *ctx, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
extern void rect(SketchContext *ctx, double x, double y, double width, double height);
extern void triangle(SketchContext *ctx, double x1, double y1, double x2, double y2, double x3, double y3);

extern void bezier(SketchContext *ctx, double x1, double y1, double cx1, double cy1, double cx2, double cy2, double x2, double y2);

extern void fill(SketchContext *ctx, double v1, double v2, double v3);
extern void stroke(SketchContext *ctx, double v1, double v2, double v3);

extern void smooth(SketchContext *ctx);
extern void noSmooth(SketchContext *ctx);

extern void background(SketchContext *ctx, double v1, double v2, double v3);


extern void doSetup(SketchContext *ctx);


static inline double min(double a, double b) {
  return a < b ? a : b;
}

static inline double max(double a, double b) {
  return a > b ? a : b;
}

static inline double constrain(double v, double lower, double upper) {
  if (v < lower)
    return lower;
  if (v > upper)
    return upper;
  return v;
}

static inline void noFill(SketchContext *ctx) {
  ctx->fill = false;
}

static inline void noStroke(SketchContext *ctx) {
  ctx->stroke = false;
}

static inline void ellipseMode(SketchContext *ctx, uint32_t mode) {
  if (mode > CORNERS)
    mode = CENTER;
  ctx->ellipseMode = mode;
}

static inline void rectMode(SketchContext *ctx, uint32_t mode) {
  if (mode > CORNERS)
    mode = CORNER;
  ctx->rectMode = mode;
}

static inline double bezierPoint(double a, double b, double c, double d, double t) {
// B(t) = (1-t)^(3)P_0 + 3(1-t)^(2)tP_1 + 3(1-t)t^(2)P_2 + t^(3)P_3
  double t2 = t * t;
  double t3 = t2 * t;
  return ((-t3 + 3 * t2 - 3 * t + 1) * a) + (3 * (t2 - 2 * t + 1) * t * b) + (3 * (1 - t) * t2 * c) + (t3 * d);
}

#endif
