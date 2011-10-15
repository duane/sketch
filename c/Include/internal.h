#ifndef __C_INCLUDE_INTERNAL_H__
#define __C_INCLUDE_INTERNAL_H__
#include <sketch.h>

// events
static inline void sendMouseDown(SketchContext *ctx, uint32_t button) {
  ctx->mousePressed = true;
  ctx->mouseButton = button;
  ctx->mousePressedf(ctx);
}

static inline void sendMouseUp(SketchContext *ctx) {
  ctx->mousePressed = false;
  // TODO: Fix this: there is no difference between mouseReleased and mouseClicked.
  ctx->mouseClicked(ctx);
  ctx->mouseReleased(ctx);
}

static inline void sendMouseMoved(SketchContext *ctx, double x, double y) {
  ctx->mouseX = x;
  ctx->mouseY = y;
  ctx->mouseMoved(ctx);
}

static inline void sendMouseDragged(SketchContext *ctx, double x, double y) {
  ctx->mouseX = x;
  ctx->mouseY = y;
  ctx->mouseDragged(ctx);
}

static inline void advanceMouseFrame(SketchContext *ctx) {
  ctx->pmouseX = ctx->mouseX;
  ctx->pmouseY = ctx->mouseY;
}

#endif
