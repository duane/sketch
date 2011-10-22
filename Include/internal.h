#ifndef __C_INCLUDE_INTERNAL_H__
#define __C_INCLUDE_INTERNAL_H__
#include <sketch.h>

extern void doSetup(SketchContext *ctx);

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

static inline void sendKeyDown(SketchContext *ctx, char key, uint32_t unicodeKey, uint32_t keyCode, bool repeat) {
  ctx->key = key;
  ctx->unicodeKey = unicodeKey;
  ctx->keyCode = keyCode;
  if (!repeat
      || keyCode == sVK_Up
      || keyCode == sVK_Down
      || keyCode == sVK_Left
      || keyCode == sVK_Right) {
    ctx->keyPressed = true;
    ctx->keyPressedf(ctx);
  }
  if (key != CODED)
    ctx->keyTyped(ctx);
}

static inline void sendKeyUp(SketchContext *ctx) {
  ctx->keyPressed = false;
  ctx->keyReleased(ctx);
}

#endif
