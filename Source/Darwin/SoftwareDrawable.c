#include <sketch.h>
#include <stdlib.h>

#include <ApplicationServices/ApplicationServices.h>

static inline CGPathDrawingMode drawingMode(SketchContext *ctx) {
  if (ctx->stroke && ctx->fill)
    return kCGPathFillStroke;
  if (ctx->fill)
    return kCGPathFill;
  return kCGPathStroke;
}

static void darwin_arc(SketchContext *ctx, double x, double y, double width, double height, double start, double stop) {
  CGContextRef cgCtx = ctx->drawable->implData;
  if (!(ctx->stroke || ctx->fill))
    return;
    
  double xPrime, yPrime;
  double xScale, yScale;
  switch(ctx->ellipseMode) {
    case CENTER:
    default:
      xScale = width / 2;
      yScale = height / 2;
      xPrime = x;
      yPrime = y;
      break;
    case RADIUS:
      xScale = width;
      yScale = height;
      xPrime = x;
      yPrime = y;
      break;
    case CORNER:
      xScale = width / 2;
      yScale = height / 2;
      xPrime = x + xScale;
      yPrime = y + yScale;
      break;
    case CORNERS:
      xScale = (x - width) / 2;
      yScale = (y - height) / 2;
      xPrime = x - xScale;
      yPrime = y - yScale;
      break;
  }
   
  if (ctx->fill) {
    CGContextSaveGState(cgCtx);
    CGContextTranslateCTM(cgCtx, xPrime, yPrime);
    CGContextScaleCTM(cgCtx, xScale, yScale);
    if (stop - start < M_PI * 2) {
      CGContextMoveToPoint(cgCtx, cos(start), sin(start));
      CGContextAddLineToPoint(cgCtx, 0.0, 0.0);
      CGContextAddLineToPoint(cgCtx, cos(stop), sin(stop));
    }
    CGContextAddArc(cgCtx, 0, 0, 1.0, start, stop, 0);
    CGContextRestoreGState(cgCtx);
    CGContextFillPath(cgCtx);
  }
  if (ctx->stroke) {
    CGContextSaveGState(cgCtx);
    CGContextTranslateCTM(cgCtx, xPrime, yPrime);
    CGContextScaleCTM(cgCtx, xScale, yScale);
    CGContextAddArc(cgCtx, 0, 0, 1.0, start, stop, 0);
    CGContextRestoreGState(cgCtx); 
    CGContextStrokePath(cgCtx);
  }
}

static void darwin_ellipse(SketchContext *ctx, double x, double y, double width, double height) {
  darwin_arc(ctx, x, y, width, height, 0, M_PI*2);
}

static void darwin_line(SketchContext *ctx, double x1, double y1, double x2, double y2) {
  if (!(ctx->stroke || ctx->fill))
    return;
  CGContextRef cgCtx = ctx->drawable->implData;
  CGContextMoveToPoint(cgCtx, x1, y1);
  CGContextAddLineToPoint(cgCtx, x2, y2);
  if (ctx->stroke)
    CGContextStrokePath(cgCtx);
}

static void darwin_point(SketchContext *ctx, double x, double y) {
  if (!(ctx->stroke || ctx->fill))
    return;
  CGContextRef cgCtx = ctx->drawable->implData;
  CGRect pointRect = CGRectMake(x - 0.5, y - 0.5, 1.0, 1.0);
  CGContextFillRect(cgCtx, pointRect);
}

static void darwin_quad(SketchContext *ctx, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
  if (!(ctx->stroke || ctx->fill))
    return;
  CGContextRef cgCtx = ctx->drawable->implData;
  CGContextMoveToPoint(cgCtx, x1, y1);
  CGContextAddLineToPoint(cgCtx, x2, y2);
  CGContextAddLineToPoint(cgCtx, x3, y3);
  CGContextAddLineToPoint(cgCtx, x4, y4);
  CGContextAddLineToPoint(cgCtx, x1, y1);
  CGContextDrawPath(cgCtx, drawingMode(ctx));
}

static void darwin_rect(SketchContext *ctx, double x, double y, double width, double height) {
  if (!(ctx->stroke || ctx->fill))
    return;
  CGContextRef cgCtx = ctx->drawable->implData;
  
  double xPrime, yPrime;
  double xLen, yLen;
  switch(ctx->rectMode) {
    case CENTER:
      xPrime = x - (width / 2);
      yPrime = y - (height / 2);
      xLen = width;
      yLen = height;
      break;
    case RADIUS:
      xPrime = x - width;
      yPrime = y - height;
      xLen = width * 2;
      yLen = height * 2;
      break;
    case CORNER:
    default:
      xPrime = x;
      yPrime = y;
      xLen = width;
      yLen = height;
      break;
    case CORNERS:
      xPrime = x;
      yPrime = y;
      xLen = width - x;
      yLen = height - y;
      break;
  }
  CGRect rect = CGRectMake(xPrime, yPrime, xLen, yLen);
  
  CGContextAddRect(cgCtx, rect);
  CGContextDrawPath(cgCtx, drawingMode(ctx));
}

static void darwin_triangle(SketchContext *ctx, double x1, double y1, double x2, double y2, double x3, double y3) {
  if (!(ctx->stroke || ctx->fill))
    return;
  CGContextRef cgCtx = ctx->drawable->implData;
  CGContextMoveToPoint(cgCtx, x1, y1);
  CGContextAddLineToPoint(cgCtx, x2, y2);
  CGContextAddLineToPoint(cgCtx, x3, y3);
  CGContextAddLineToPoint(cgCtx, x1, y1);
  CGContextDrawPath(cgCtx, drawingMode(ctx));
}

static void darwin_bezier(SketchContext *ctx, double x1, double y1, double cx1, double cy1, double cx2, double cy2, double x2, double y2) {
  if (!ctx->stroke)
    return;
  CGContextRef cgCtx = ctx->drawable->implData;
  CGContextMoveToPoint(cgCtx, x1, y1);
  CGContextAddCurveToPoint(cgCtx, cx1, cy1, cx2, cy2, x2, y2);
  CGContextStrokePath(cgCtx);
}

static void darwin_background(SketchContext *ctx, double v1, double v2, double v3) {
  CGContextRef cgCtx = ctx->drawable->implData;
  CGContextSaveGState(cgCtx);
  CGContextSetRGBFillColor(cgCtx, constrain(v1, 0.0, 255.0) / 255, constrain(v2, 0.0, 255.0) / 255, constrain(v3, 0.0, 255.0) / 255, 1.0);
  CGContextFillRect(cgCtx, CGRectMake(0, 0, ctx->width, ctx->height));
  CGContextRestoreGState(cgCtx);
}

static void darwin_fill(SketchContext *ctx, double v1, double v2, double v3) {
  CGContextRef cgCtx = ctx->drawable->implData;
  CGContextSetRGBFillColor(cgCtx, v1, v2, v3, 1.0);
}

static void darwin_stroke(SketchContext *ctx, double v1, double v2, double v3) {
  CGContextRef cgCtx = ctx->drawable->implData;
  CGContextSetRGBStrokeColor(cgCtx, v1, v2, v3, 1.0);
}

static void darwin_smooth(SketchContext *ctx) {
  CGContextRef cgCtx = ctx->drawable->implData;
  CGContextSetShouldAntialias(cgCtx, true);
}

static void darwin_noSmooth(SketchContext *ctx) {
  CGContextRef cgCtx = ctx->drawable->implData;
  CGContextSetShouldAntialias(cgCtx, false);
}

extern Drawable *SoftwareDrawable() {
  Drawable *drawable = malloc(sizeof(Drawable));
  
  drawable->arc = darwin_arc;
  drawable->ellipse = darwin_ellipse;
  drawable->line = darwin_line;
  drawable->point = darwin_point;
  drawable->quad = darwin_quad; 
  drawable->rect = darwin_rect;
  drawable->triangle = darwin_triangle;

  drawable->bezier = darwin_bezier;

  drawable->fill = darwin_fill;
  drawable->stroke = darwin_stroke;
  drawable->background = darwin_background;
  
  drawable->smooth = darwin_smooth;
  drawable->noSmooth = darwin_noSmooth;

  drawable->implData = NULL;
  
  return drawable;
}

