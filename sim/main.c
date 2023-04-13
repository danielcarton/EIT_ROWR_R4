#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <terminal.h>
#include <math.h>
#include <stdbool.h>
#include <stdarg.h>

#include "perlin.h"

static double ipart(double x) {
  return (double)(int)x;
}

static double get_round(double x) {
  return ipart(x + 0.5);
}

static double fpart(double x) { 
  return x - ipart(x);
}

static double rfpart(double x) {
  return 1 - fpart(x);
}

static double get_abs(double value) {
return value < 0 ? -value : value;
}

static void swap(double* a, double* b) {
  double tmp = *a;
  *a = *b;
  *b = tmp;
}

static void plot(double x, double y, double grayscale) {
  terminal_set_cursor((int)x, (int)y);
  terminal_grayscale(grayscale);
  terminal_print("x");
}

static void draw_line(double x0, double y0, double x1, double y1) {
  bool steep = get_abs(y1 - y0) > get_abs(x1 - x0);

  if (steep) {
    swap(&x0, &y0);
    swap(&x1, &y1);
  }

  if (x0 > x1) {
    swap(&x0, &x1);
    swap(&y0, &y1);
  }

  double dx = x1 - x0;
  double dy = y1 - y0;
  double gradient;

  if (dx == 0) {
    gradient = 1.0;
  } else {
    gradient = dy / dx;
  }

  double xend = get_round(x0);
  double yend = y0 + gradient * (xend - x0);
  double xgap = rfpart(x0 + 0.5);
  double xpxl1 = xend;
  double ypxl1 = ipart(yend);

  if (steep) {
    plot(ypxl1,   xpxl1, rfpart(yend) * xgap);
    plot(ypxl1+1, xpxl1,  fpart(yend) * xgap);
  } else {
    plot(xpxl1, ypxl1  , rfpart(yend) * xgap);
    plot(xpxl1, ypxl1+1,  fpart(yend) * xgap);
  }
  double intery = yend + gradient;
    
  xend = get_round(x1);
  yend = y1 + gradient * (xend - x1);
  xgap = fpart(x1 + 0.5);
  double xpxl2 = xend;
  double ypxl2 = ipart(yend);
  
  if (steep) {
    plot(ypxl2  , xpxl2, rfpart(yend) * xgap);
    plot(ypxl2+1, xpxl2,  fpart(yend) * xgap);
  } else {
    plot(xpxl2, ypxl2,  rfpart(yend) * xgap);
    plot(xpxl2, ypxl2+1, fpart(yend) * xgap);
  }
  
  if (steep) {
    for (double x = xpxl1 + 1; x <= xpxl2 - 1; x++) {
      plot(ipart(intery)  , x, rfpart(intery));
      plot(ipart(intery)+1, x,  fpart(intery));
      intery = intery + gradient;
    }
  } else {
    for (double x = xpxl1 + 1; x <= xpxl2 - 1; x++) {
        plot(x, ipart(intery),  rfpart(intery));
        plot(x, ipart(intery)+1, fpart(intery));
        intery = intery + gradient;
    }
  }
}

static void line(double angle, int k) {
  int width, height;
  terminal_get_size(&width, &height);

  width /= 2;

  int min = height;
  if (width < min)
    min = width;
  
  k = min / 2;

  double mid_x = width / 2;
  double mid_y = height / 2;

  double xx = cosf(angle) * k;
  double yy = sinf(angle) * k;

  double x1 = mid_x - xx;
  double y1 = mid_y - yy;
  double x2 = mid_x + xx;
  double y2 = mid_y + yy;

  draw_line(x1, y1, x2, y2);

  terminal_grayscale(1);
  terminal_set_cursor(0, height - 5);
  terminal_print("Angle: %lf\n", angle);
  terminal_set_cursor(0, height - 4);
  terminal_print("Size: %d\n", k);
}

static void floo() {
  #define N 30
  static float xpos = 0; 
  static int count = 0;
  static int heights[N];

    xpos += 0.0001; 
  int height, width;
  terminal_get_size(&width, &height);

  if (count++ % 10 == 0) {
    for (int i = 0; i < N - 1; i++) {
      heights[i] = heights[i + 1];
    }

    heights[N - 1] = (perlin(xpos, 0)*0.5+0.5)*10;
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < heights[i]; j++) {
      terminal_set_cursor(width / 2 - N - 1 + i, height - j - 1);
      terminal_print("x");
    }
  }
}

int main() {
  terminal_init();
  float xpos = 0;

  while (1) {
    for (double i = -M_PI / 2; i < M_PI / 2; i += 0.01) {
      terminal_clear();
      line(i, 20);
      floo();
      terminal_flush();
      for (long long j = 0; j < 5000000; j++) __asm__("nop");
    }
  }


  cursor(0, 100);

  printf("\033[240msdfsdf");
  return 0;
}