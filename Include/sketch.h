#ifndef __INCLUDE_CONTEXT_H__
#define __INCLUDE_CONTEXT_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

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


enum {
  CENTER = 1,
  RADIUS = 2,
  CORNER = 3,
  CORNERS = 4,
  CODED = 0x80,
  UNICODED = 0x81,
  RIGHT = sVK_Right,
  LEFT = sVK_Left,
  UP = sVK_Up,
  DOWN = sVK_Down,
  
  BACKSPACE = sVK_Delete,
  TAB = sVK_Tab,
  ENTER = sVK_Enter,
  RETURN = sVK_Return,
  SPACE = sVK_Space,
  ESC = sVK_Escape,
  DELETE = sVK_ForwardDelete,
};


struct SketchContext;

enum {
  RGB = 0,
  ARGB = 1,
  ALPHA = 2,
};

typedef uint32_t ImageFormat;

typedef struct {
  uint8_t *buf;
  size_t width, height;
  ImageFormat format;
  void *impl;
} SImage;

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

  void (*CreateSImage)(struct SketchContext *ctx, SImage *image);
  void (*image)(struct SketchContext *ctx, SImage *image, double x, double y, double width, double height);

  void *implData;
} Drawable;

typedef struct {
  double v1, v2, v3, a;
} color __attribute__ ((aligned (8)));

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
  uint8_t key;
  uint32_t unicodeKey;
  uint32_t keyCode;
} SketchContext __attribute__ ((aligned (8)));

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
extern double bezierPoint(double a, double b, double c, double d, double t);

extern void fill(SketchContext *ctx, double v1, double v2, double v3);
extern void stroke(SketchContext *ctx, double v1, double v2, double v3);
extern void noFill(SketchContext *ctx);
extern void noStroke(SketchContext *ctx);
extern void ellipseMode(SketchContext *ctx, uint32_t mode);
extern void rectMode(SketchContext *ctx, uint32_t mode);

extern void smooth(SketchContext *ctx);
extern void noSmooth(SketchContext *ctx);

extern void background(SketchContext *ctx, double v1, double v2, double v3);

extern double min(double a, double b);
extern double max(double a, double b);
extern double constrain(double v, double lower, double upper);

extern SImage *CreateSImage(SketchContext *ctx, uint8_t *buf, size_t width, size_t height, ImageFormat format);
extern void image(SketchContext *ctx, SImage *image, double x, double y);

static inline size_t BytesPerPixel(ImageFormat format) {
  return 3;
}

#endif
