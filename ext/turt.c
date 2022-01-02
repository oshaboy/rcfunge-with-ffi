/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef TURT
#include <time.h>
#include "funge.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define TURT_W      800
#define TURT_H      600
#define CENTER_X    TURT_W/2
#define CENTER_Y    TURT_H/2
#define DEGRAD      (3.14159265358979323846/180)

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

Window t_window;
Pixmap t_pixmap;
int    turtle_x;
int    turtle_y;
char   turtle_pen;
double turtle_dir;
Display* t_display;
GC       t_gc;
char   turtle_loaded = 'N';

void Load_TURT(VM* vm,long int FingerPrint)
{
  INT  i;
  XSetWindowAttributes attributes;
  XWindowAttributes    attr;
  XGCValues            values;
  unsigned long        mask;
  Visual               *visual=CopyFromParent;
  Window               parent;
  int cip;
  cip = vm->cip;
  if (turtle_loaded != 'Y') {
    if (XEnabled == 'Y') {
      t_display = XOpenDisplay(":0.0");
      if (t_display == NULL) XEnabled = 'N';
      if (XEnabled == 'Y') {
        parent = DefaultRootWindow(t_display);
        attributes.background_pixel=BlackPixel(t_display,DefaultScreen(t_display));
        mask=CWBackPixel;
        t_window = XCreateWindow(t_display,parent,0,0,TURT_W,TURT_H,1,
           CopyFromParent,InputOutput,visual,mask,&attributes);
        XSelectInput(t_display,t_window,ExposureMask);
        XMapWindow(t_display,t_window);
        XFlush(t_display);
        mask=GCForeground | GCBackground;
        values.foreground=WhitePixel(t_display,DefaultScreen(t_display));
        values.background=BlackPixel(t_display,DefaultScreen(t_display));
        t_gc = XCreateGC(t_display,t_window,mask,&values);
        XGetWindowAttributes(t_display,t_window,&attr);
        t_pixmap = XCreatePixmap(t_display,t_window,TURT_W,TURT_H,attr.depth);
        XFillRectangle(t_display,t_pixmap,t_gc,0,0,TURT_W,TURT_H);
        }
      }
    turtle_x = 0;
    turtle_y = 0;
    turtle_pen = 0;
    turtle_dir = 0;
    turtle_loaded = 'Y';
    TURTOffX = CENTER_X;
    TURTOffY = CENTER_Y;
    }
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_TURT+0;    /* A */
  vm->IPs[cip].Overloads[1][vm->IPs[cip].NumOvers]=EX_TURT+1;    /* B */
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_TURT+2;    /* C */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_TURT+3;    /* D */
  vm->IPs[cip].Overloads[4][vm->IPs[cip].NumOvers]=EX_TURT+4;    /* E */
  vm->IPs[cip].Overloads[5][vm->IPs[cip].NumOvers]=EX_TURT+5;    /* F */
  vm->IPs[cip].Overloads[7][vm->IPs[cip].NumOvers]=EX_TURT+7;    /* H */
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_TURT+21;   /* I */
  vm->IPs[cip].Overloads[11][vm->IPs[cip].NumOvers]=EX_TURT+11;  /* L */
  vm->IPs[cip].Overloads[13][vm->IPs[cip].NumOvers]=EX_TURT+13;  /* N */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_TURT+15;  /* P */
  vm->IPs[cip].Overloads[16][vm->IPs[cip].NumOvers]=EX_TURT+16;  /* Q */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_TURT+17;  /* R */
  vm->IPs[cip].Overloads[19][vm->IPs[cip].NumOvers]=EX_TURT+19;  /* T */
  vm->IPs[cip].Overloads[20][vm->IPs[cip].NumOvers]=EX_TURT+20;  /* U */
}

void Unload_TURT(VM* vm) {
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,1);
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,4);
  Unload_Semantic(vm,5);
  Unload_Semantic(vm,7);
  Unload_Semantic(vm,8);
  Unload_Semantic(vm,11);
  Unload_Semantic(vm,13);
  Unload_Semantic(vm,15);
  Unload_Semantic(vm,16);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,19);
  Unload_Semantic(vm,20);
  }

void Cycle_TURT() {
  if (XEnabled == 'Y') {
    XEvent event;
    if (turtle_loaded != 'Y') return;
    if (XPending(t_display) == 0) return;
    XNextEvent(t_display,&event);
    if (event.type == Expose) {
      if (event.xexpose.count != 0) return;
      XCopyArea(t_display,t_pixmap,t_window,t_gc,0,0,TURT_W,TURT_H,0,0);
      }
    }
  }

void Do_TURT(VM* vm,int Cmd)
{
  int    l;
  double dl;
  double xd,yd;
  XColor clr;
  XGCValues            values;
  unsigned long        mask;
  GC     tmp_gc;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_TURT+00:Push(vm,turtle_dir);                 /* TURT, A */
                    break;
    case EX_TURT+21:                                      /* TURT, I */
                    break;
    case EX_TURT+01:l=Pop(vm);                           /* TURT, B */
                    dl = l;
                    xd = dl * cos(turtle_dir * DEGRAD);
                    yd = dl * sin(turtle_dir * DEGRAD);
                    if (XEnabled == 'Y') {
                      if (turtle_pen == 1) {
                        XDrawLine(t_display,t_window,t_gc,CENTER_X+turtle_x-TURTOffX,CENTER_Y+turtle_y-TURTOffY,
                           CENTER_X+turtle_x-xd-TURTOffX,CENTER_Y+turtle_y-yd-TURTOffY);
                        XDrawLine(t_display,t_pixmap,t_gc,CENTER_X+turtle_x-TURTOffX,CENTER_Y+turtle_y-TURTOffY,
                           CENTER_X+turtle_x-xd-TURTOffX,CENTER_Y+turtle_y-yd-TURTOffY);
                        }
                      XFlush(t_display);
                      }
                    turtle_x -= xd;
                    turtle_y -= yd;
                    break;
    case EX_TURT+02:l = Pop(vm);                         /* TURT, C */
                    clr.red = ((l >> 16) & 0xff) << 8;
                    clr.green = ((l >> 8) & 0xff) << 8;
                    clr.blue = (l & 0xff) << 8;
                    if (XEnabled == 'Y') {
                      XAllocColor(t_display,DefaultColormap(t_display,
                          DefaultScreen(t_display)),&clr);
                      XSetForeground(t_display,t_gc,clr.pixel);
                      XFlush(t_display);
                      }
                    break;
    case EX_TURT+03:l = Pop(vm);                         /* TURT, D */
                    if (XEnabled == 'Y') {
                      if (l == 0) /* XUnmapWindow(t_display,t_window) */;
                        else XMapWindow(t_display,t_window);
                      XFlush(t_display);
                      }
                    break;
    case EX_TURT+04:Push(vm,turtle_pen);                 /* TURT, E */
                    break;
    case EX_TURT+05:l=Pop(vm);                           /* TURT, F */
                    dl = l;
                    xd = dl * cos(turtle_dir * DEGRAD);
                    yd = dl * sin(turtle_dir * DEGRAD);
                    if (XEnabled == 'Y') {
                      if (turtle_pen == 1) {
                        XDrawLine(t_display,t_window,t_gc,CENTER_X+turtle_x-TURTOffX,CENTER_Y+turtle_y-TURTOffY,
                           CENTER_X+turtle_x+xd-TURTOffX,CENTER_Y+turtle_y+yd-TURTOffY);
                        XDrawLine(t_display,t_pixmap,t_gc,CENTER_X+turtle_x-TURTOffX,CENTER_Y+turtle_y-TURTOffY,
                           CENTER_X+turtle_x+xd-TURTOffX,CENTER_Y+turtle_y+yd-TURTOffY);
                        XFlush(t_display);
                        }
                      }
                    turtle_x += xd;
                    turtle_y += yd;
                    break;
    case EX_TURT+07:turtle_dir=Pop(vm);                  /* TURT, H */
                    break;
    case EX_TURT+11:turtle_dir -= Pop(vm);               /* TURT, L */
                    while (turtle_dir >= 360) turtle_dir -= 360;
                    while (turtle_dir < 0) turtle_dir += 360;
                    break;
    case EX_TURT+13:l = Pop(vm);                         /* TURT, N */
                    clr.red = ((l >> 16) & 0xff) << 8;
                    clr.green = ((l >> 8) & 0xff) << 8;
                    clr.blue = (l & 0xff) << 8;
                    if (XEnabled == 'Y') {
                      XAllocColor(t_display,DefaultColormap(t_display,
                          DefaultScreen(t_display)),&clr);
                      mask=GCForeground | GCBackground;
                      values.foreground=
                           WhitePixel(t_display,DefaultScreen(t_display));
                      values.background=
                           BlackPixel(t_display,DefaultScreen(t_display));
                      tmp_gc = XCreateGC(t_display,t_window,mask,&values);
                      XSetForeground(t_display,tmp_gc,clr.pixel);
                      XFillRectangle(t_display,t_window,tmp_gc,0,0,
                        TURT_W,TURT_H);
                      XFillRectangle(t_display,t_pixmap,tmp_gc,0,0,
                       TURT_W,TURT_H);
                      XFreeGC(t_display,tmp_gc);
                      XFlush(t_display);
                      }
                    break;
    case EX_TURT+15:turtle_pen = (Pop(vm) != 0) ? 1 : 0; /* TURT, P */
                    break;
    case EX_TURT+16:Push(vm,turtle_x);                   /* TURT, Q */
                    Push(vm,turtle_y);
                    break;
    case EX_TURT+17:turtle_dir += Pop(vm);               /* TURT, R */
                    while (turtle_dir >= 360) turtle_dir -= 360;
                    while (turtle_dir < 0) turtle_dir += 360;
                    break;
    case EX_TURT+19:turtle_y = Pop(vm);                  /* TURT, T */
                    turtle_x = Pop(vm);
                    break;
    case EX_TURT+20:Push(vm,0-CENTER_X);                 /* TURT, U */
                    Push(vm,0-CENTER_Y);
                    Push(vm,TURT_W-CENTER_X);
                    Push(vm,TURT_H-CENTER_Y);
                    break;
    }
}
#endif

