#ifndef __INCLUDE_CONTEXT_H__
#define __INCLUDE_CONTEXT_H__

#include <stdint.h>
#include <stdbool.h>

// Core constants


const static uint32_t CENTER = 1;
const static uint32_t RADIUS = 2;
const static uint32_t CORNER = 3;
const static uint32_t CORNERS = 4;


// These are defined as macros because they are typeless.
#define CODED 0x80
#define UNICODED 0x81

typedef enum {
  MousePressed,
  MouseReleased,
  MouseClicked,
  MouseMoved,
  MouseDragged
} MouseEvent;

typedef enum {
  KeyPressed,
  KeyReleased
} KeyEvent;

enum {
  sVK_None = 0x0, // use key/unicodeKey instead.

  // Modifier keys.
  sVK_Meta = 0x01,
  sVK_Command = 0x01,
  sVK_Windows = 0x01,
  sVK_Control = 0x02,
  sVK_Option = 0x03,
  sVK_Shift = 0x04,

  // Function keys.
  sVK_F1 = 0x05,
  sVK_F2 = 0x06,
  sVK_F3 = 0x07,
  sVK_F4 = 0x08,
  sVK_F5 = 0x09,
  sVK_F6 = 0x0A,
  sVK_F7 = 0x0B,
  sVK_F8 = 0x0C,
  sVK_F9 = 0x0D,
  sVK_F10 = 0x0E,
  sVK_F11 = 0x0F,
  sVK_F12 = 0x10,
  sVK_F13 = 0x11,
  sVK_F14 = 0x12,
  sVK_F15 = 0x13,
  sVK_F16 = 0x14,
  sVK_F17 = 0x15,
  sVK_F18 = 0x16,
  sVK_F19 = 0x17,
  sVK_F20 = 0x18,
 
  // Directional keys.
  sVK_Up = 0x19,
  sVK_Down = 0x1A,
  sVK_Left = 0x1B,
  sVK_Right = 0x1C,

  // Misc.

  sVK_CapsLock = 0x1D,
  sVK_Delete = 0x1E,
  sVK_End = 0x1F,
  sVK_Enter = 0x20,
  sVK_Escape = 0x21,
  sVK_ForwardDelete = 0x22,
  sVK_Home = 0x23,
  sVK_PageDown = 0x24,
  sVK_PageUp = 0x25,
  sVK_Return = 0x26,
  sVK_Space = 0x27,
  sVK_Tab = 0x28,

  sVK_Other = 0x29,
};

const static uint32_t RIGHT = sVK_Right;
const static uint32_t LEFT = sVK_Left;

const static uint32_t UP = sVK_Up;
const static uint32_t DOWN = sVK_Down;

const static uint32_t BACKSPACE = sVK_Delete;
const static uint32_t TAB = sVK_Tab;
const static uint32_t ENTER = sVK_Enter;
const static uint32_t RETURN = sVK_Return;
const static uint32_t SPACE = sVK_Space;
const static uint32_t ESC = sVK_Escape;
const static uint32_t DELETE = sVK_ForwardDelete;


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

typedef struct {
  double v1, v2, v3, a;
} color;

typedef struct SketchContext {
  Drawable *drawable;
  void (*setup)(struct SketchContext*);
  void (*draw)(struct SketchContext*);

  void (*mouseClicked)(struct SketchContext*);
  void (*mouseDragged)(struct SketchContext*);
  void (*mouseMoved)(struct SketchContext*);
  void (*mousePressedf)(struct SketchContext*);
  void (*mouseReleased)(struct SketchContext*);

  void (*keyPressedf)(struct SketchContext*);
  void (*keyReleased)(struct SketchContext*);
  void (*keyTyped)(struct SketchContext*);
 
  uint32_t width, height;
  uint32_t ellipseMode, rectMode; 
  
  bool fill, stroke;

  color strokeColor, fillColor;
  
  double mouseX, mouseY, pmouseX, pmouseY;
  uint32_t mouseButton;
  bool mousePressed;

  bool keyPressed;
  char key;
  uint32_t unicodeKey;
  uint32_t keyCode;
} SketchContext;

extern SketchContext *CreateSketchContext(Drawable *drawable, uint32_t width, uint32_t height, void (*setup)(SketchContext*), void (*draw)(SketchContext*));
extern Drawable *SoftwareDrawable(void);
extern void RegisterMouse(SketchContext *ctx, MouseEvent event, void (*mouseCallback)(SketchContext*));
extern void RegisterKey(SketchContext *ctx, KeyEvent event, void (*keyCallback)(SketchContext*));

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
