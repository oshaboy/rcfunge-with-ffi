/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#include "funge.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string.h>

#define MAX_WINDOWS   1000

struct WINDOW {
  Display *display;
  Window  window;
  Window  screen;
  Window  parent;
  Pixmap  backing;
  XGCValues  gcvalues;
  GC      gc;
  long    gcmask;
  unsigned long   event_mask;
  INT             EventDown[3];
  INT             EventUp[3];
  INT             Paint[3];
  INT             Key[3];
  INT             Motion[3];
  INT             Configure[3];
  INT             Focus[3];
  INT             Destroy[3];
  INT             Width,Height;
  };

Window CreateWindow(Display* display,
	Window parent,
	INT x,
	INT y,
	UINT width,
	UINT height,
	UINT border,
	unsigned long fore,
	unsigned long back,
	unsigned long event_mask)
  {
    Window			window;
    XSetWindowAttributes	attributes;
    unsigned long		attribute_mask;
    Visual			*visual=CopyFromParent;

    attributes.background_pixel=back;
    attributes.border_pixel=fore;
    attributes.event_mask=event_mask;
    attribute_mask=CWBackPixel | CWBorderPixel | CWEventMask;
    window = XCreateWindow(display,parent,x,y,width,height,border,
      CopyFromParent,InputOutput,visual,attribute_mask,&attributes);
    return window;
  }

void SetWMHints(Display* display,
	Window window,
	INT x,
	INT y,
	UINT width,
	UINT height,
	INT argc,
	char** argv,
	char* window_name,
	char* icon_name,
	char* class_name,
	char* class_type)
  {
    XTextProperty w_name;
    XTextProperty i_name;
    XSizeHints sizehints;
    XWMHints wmhints;
    XClassHint classhints;
    INT status;
    status=XStringListToTextProperty(&window_name,1,&w_name);
    status=XStringListToTextProperty(&icon_name,1,&i_name);
    sizehints.x=x;
    sizehints.y=y;
    sizehints.width=width;
    sizehints.height=height;
    sizehints.base_width=width;
    sizehints.base_height=height;
    sizehints.flags=USPosition | USSize | PBaseSize;
    wmhints.initial_state=NormalState;
    wmhints.input=True;
    wmhints.flags=StateHint | InputHint;
    classhints.res_name=class_name;
    classhints.res_class=class_type;
    XSetWMProperties(display,window,
      &w_name,
      &i_name,
      argv,argc,
      &sizehints,
      &wmhints,
      &classhints);
    XFree(w_name.value);
    XFree(i_name.value);
  }

Bool FilterEvent(XEvent* event,Bool want_exposes,INT width, INT height)
  {
    Bool status;
    status=(Bool) True;
    if (XFilterEvent(event,(Window) None))
      {
        return (Bool) False;
      }
    switch (event->type)
      {
        case Expose:
          if (!want_exposes)
            {
              if (event->xexpose.count!=0) { status=False; }
            }
          break;
        case ConfigureNotify:
          if ((width == event->xconfigure.width) &&
               height == event->xconfigure.height)
            { status = (Bool) False; }
          break;
        case MappingNotify:
          XRefreshKeyboardMapping((XMappingEvent*) event);
          status=(Bool) False;
          break;
        default: ;
      }
    return status;
  }


struct WINDOW Windows[MAX_WINDOWS];

void setupBacking(INT w,int width,int height) {
  GC  gc;
  long    gcmask;
  XGCValues  gcvalues;
  XWindowAttributes attr;
  XColor clr;
    gcvalues.function=GXcopy;
    XGetWindowAttributes(Windows[w].display,Windows[w].window,&attr);
    Windows[w].backing = XCreatePixmap(Windows[w].display,
              Windows[w].window,width,height,attr.depth);
    gcvalues.foreground=
      BlackPixel(Windows[w].display,Windows[w].screen);
    gcvalues.background=
      WhitePixel(Windows[w].display,Windows[w].screen);
    gcvalues.line_style=0;
    gcvalues.line_width=1;
    gcvalues.fill_style=0;
    gcmask=GCForeground | GCBackground | GCLineWidth | GCLineStyle |
           GCFunction | GCFillStyle;
    gc=XCreateGC(Windows[w].display,Windows[w].window,gcmask,&gcvalues);
    clr.red = 0xffffffff;
    clr.green = 0xffffffff;
    clr.blue = 0xffffffff;
    XAllocColor(Windows[w].display,DefaultColormap(Windows[w].display,DefaultScreen(Windows[w].display)),&clr);
    XSetForeground(Windows[w].display,gc,clr.pixel);
    XFillRectangle(Windows[w].display,
                   Windows[w].backing,gc,0,0,width,height);
    XFreeGC(Windows[w].display,gc);
    XFlush(Windows[w].display);
  }

int New_Window(INT x,INT y,INT wd,INT h)
{
  INT i,w;
  w=-1;
  for (i=0;i<MAX_WINDOWS;i++)
    if (Windows[i].window==0) {w=i; i=MAX_WINDOWS; }
  if (w>=0) {
    Windows[w].Height = h;
    Windows[w].Width = wd;
    Windows[w].event_mask=0;
    Windows[w].display=XOpenDisplay(":0.0");
    Windows[w].screen=DefaultScreen(Windows[w].display);
    Windows[w].parent=RootWindow(Windows[w].display,Windows[w].screen);
    Windows[w].window=CreateWindow(Windows[w].display,Windows[w].parent,x,y,
      wd,h,1,BlackPixel(Windows[w].display,Windows[w].screen),
      WhitePixel(Windows[w].display,Windows[w].screen),
      Windows[w].event_mask);
    XMapRaised(Windows[w].display,Windows[w].window);
    XMoveWindow(Windows[w].display,Windows[w].window,x,y);
    XFlush(Windows[w].display);
    setupBacking(w,wd,h);

    }
  return w;
}

int Close_Window(INT w)
{
  if (Windows[w].window!=0) {
    XDestroyWindow(Windows[w].display,Windows[w].window);
    XFlush(Windows[w].display);
    Windows[w].window=0;
    return 0;
    }
  else return -1;
}

int Raise_Window(INT w)
{
  if (Windows[w].window!=0) {
    XRaiseWindow(Windows[w].display,Windows[w].window);
    XFlush(Windows[w].display);
    return 0;
    }
  else return -1;
}

int Move_Window(INT w,INT x,INT y)
{
  if (Windows[w].window!=0) {
    XMoveWindow(Windows[w].display,Windows[w].window,x,y);
    XFlush(Windows[w].display);
    return 0;
    }
  else return -1;
}

int Size_Window(INT w,INT x,INT y)
{
  XWindowAttributes attr;
  if (Windows[w].window!=0) {
    Windows[w].Height = y;
    Windows[w].Width = x;
    XResizeWindow(Windows[w].display,Windows[w].window,x,y);
    XFlush(Windows[w].display);
    XFreePixmap(Windows[w].display,Windows[w].backing);
    setupBacking(w,x,y);
    return 0;
    }
  else return -1;
}

int Lower_Window(INT w)
{
  if (Windows[w].window!=0) {
    XLowerWindow(Windows[w].display,Windows[w].window);
    XFlush(Windows[w].display);
    return 0;
    }
  else return -1;
}

int Open_GC(INT w)
{
  if (Windows[w].window!=0) {
    Windows[w].gcvalues.function=GXcopy;
    Windows[w].gcvalues.foreground=
      BlackPixel(Windows[w].display,Windows[w].screen);
    Windows[w].gcvalues.background=
      WhitePixel(Windows[w].display,Windows[w].screen);
    Windows[w].gcvalues.line_style=0;
    Windows[w].gcvalues.line_width=1;
    Windows[w].gcvalues.fill_style=0;
    Windows[w].gcmask=GCForeground | GCBackground | GCLineWidth | GCLineStyle |
           GCFunction | GCFillStyle;
    Windows[w].gc=XCreateGC(Windows[w].display,Windows[w].window,
       Windows[w].gcmask,&Windows[w].gcvalues);
    XFlush(Windows[w].display);
    return 0;
    }
  else return -1;
}

int Close_GC(INT w)
{
  if (Windows[w].window!=0) {
    XFreeGC(Windows[w].display,Windows[w].gc);
    XFlush(Windows[w].display);
    return 0;
    }
  else return -1;
}

void Foreground_Color(INT w,int r,int g,int b) {
  XColor clr;
  r = r & 255;
  g = g & 255;
  b = b & 255;
  r |= (r << 8);
  g |= (g << 8);
  b |= (b << 8);
  clr.red = r;
  clr.green = g;
  clr.blue = b;
  XAllocColor(Windows[w].display,DefaultColormap(Windows[w].display,
    DefaultScreen(Windows[w].display)),&clr);
  XSetForeground(Windows[w].display,Windows[w].gc,clr.pixel);
  }

int Line(INT w,INT x1,INT y1,INT x2,INT y2)
{
  if (Windows[w].window!=0) {
    XDrawLine(Windows[w].display,Windows[w].backing,Windows[w].gc,x1,y1,x2,y2);
    XFlush(Windows[w].display);
    return 0;
    }
  else return -1;
}

int Box(INT w,INT x1,INT y1,INT x2,INT y2)
{
  if (Windows[w].window!=0) {
    XDrawRectangle(Windows[w].display,Windows[w].backing,Windows[w].gc,x1,y1,x2,y2);
    XFlush(Windows[w].display);
    return 0;
    }
  else return -1;
}

int Point(INT w,INT x,INT y)
{
  if (Windows[w].window!=0) {
    XDrawPoint(Windows[w].display,Windows[w].backing,Windows[w].gc,x,y);
    XFlush(Windows[w].display);
    return 0;
    }
  else return -1;
}

int Text(INT w,char *buffer,INT x,INT y)
{
  if (Windows[w].window!=0) {
    XDrawString(Windows[w].display,Windows[w].backing,Windows[w].gc,x,y,
      buffer,strlen(buffer));
    XFlush(Windows[w].display);
    return 0;
    }
  else return -1;
}
/*

int LineWidth(INT w,INT width)
{
  if (Windows[w].window!=0) {
    XSetLineAttributes(Windows[w].display,Windows[w].gc,width,0,0,0);
    XFlush(Windows[w].display);
    return 0;
    }
  else return -1;
}
*/

int Event_Down(INT w,INT x,INT y,INT z)
{
  if (Windows[w].window!=0) {
    Windows[w].EventDown[0]=x;
    Windows[w].EventDown[1]=y;
    Windows[w].EventDown[2]=z;
    Windows[w].event_mask |= ButtonPressMask;
    XSelectInput(Windows[w].display,Windows[w].window,Windows[w].event_mask);
    XFlush(Windows[w].display);
    return 0;
    }
  else return -1;
}

int Event_Up(INT w,INT x,INT y,INT z)
{
  if (Windows[w].window!=0) {
    Windows[w].EventUp[0]=x;
    Windows[w].EventUp[1]=y;
    Windows[w].EventUp[2]=z;
    Windows[w].event_mask |= ButtonReleaseMask;
    XSelectInput(Windows[w].display,Windows[w].window,Windows[w].event_mask);
    XFlush(Windows[w].display);
    return 0;
    }
  else return -1;
}

int Event_Motion(INT w,INT x,INT y,INT z)
{
  if (Windows[w].window!=0) {
    Windows[w].Motion[0]=x;
    Windows[w].Motion[1]=y;
    Windows[w].Motion[2]=z;
    Windows[w].event_mask |= ButtonMotionMask;
    XSelectInput(Windows[w].display,Windows[w].window,Windows[w].event_mask);
    XFlush(Windows[w].display);
    return 0;
    }
  else return -1;
}

int Event_Key(INT w,INT x,INT y,INT z)
{
  if (Windows[w].window!=0) {
    Windows[w].Key[0]=x;
    Windows[w].Key[1]=y;
    Windows[w].Key[2]=z;
    Windows[w].event_mask |= KeyPressMask;
    XSelectInput(Windows[w].display,Windows[w].window,Windows[w].event_mask);
    XFlush(Windows[w].display);
    return 0;
    }
  else return -1;
}

int Event_Paint(INT w,INT x,INT y,INT z)
{
  if (Windows[w].window!=0) {
    Windows[w].Paint[0]=x;
    Windows[w].Paint[1]=y;
    Windows[w].Paint[2]=z;
    Windows[w].event_mask |= ExposureMask;
    XSelectInput(Windows[w].display,Windows[w].window,Windows[w].event_mask);
    XFlush(Windows[w].display);
    return 0;
    }
  else return -1;
}

int Event_Configure(INT w,INT x,INT y,INT z)
{
  if (Windows[w].window!=0) {
    Windows[w].Configure[0]=x;
    Windows[w].Configure[1]=y;
    Windows[w].Configure[2]=z;
    Windows[w].event_mask |= StructureNotifyMask;
    XSelectInput(Windows[w].display,Windows[w].window,Windows[w].event_mask);
    XFlush(Windows[w].display);
    return 0;
    }
  else return -1;
}
/*

int Event_Focus(INT w,char *buffer)
{
  if (Windows[w].window!=0) {
    strcpy(Windows[w].Focus,buffer);
    Windows[w].event_mask |= FocusChangeMask;
    XSelectInput(Windows[w].display,Windows[w].window,Windows[w].event_mask);
    XFlush(Windows[w].display);
    return 0;
    }
  else return -1;
}

int Event_Destroy(INT w,char *buffer)
{
  if (Windows[w].window!=0) {
    strcpy(Windows[w].Destroy,buffer);
    Windows[w].event_mask |= 0;
    XSelectInput(Windows[w].display,Windows[w].window,Windows[w].event_mask);
    XFlush(Windows[w].display);
    return 0;
    }
  else return -1;
}
*/

int Install_Handler(INT w,INT evnt,INT x,INT y,INT z)
{
  switch (evnt) {
    case  1:return Event_Down(w,x,y,z); break;
    case  2:return Event_Up(w,x,y,z); break;
    case  3:return Event_Motion(w,x,y,z); break;
    case  4:return Event_Key(w,x,y,z); break;
    case  5:return Event_Paint(w,x,y,z); break;
    case  6:return Event_Configure(w,x,y,z); break;
    default:return -1;
    }
}

int Event(VM* vm,INT w)
{
  XEvent event;
  INT    status;
  INT    EventFound;
  INT    i;
  char   tmpbuf[10];
  XComposeStatus keystatus;
  KeySym         key;
  int cip;
  cip = vm->cip;
  EventFound=0;
  if (Windows[w].window!=0) {
    while (XPending(Windows[w].display)>0)
      {
        status=1;
        EventFound=1;
        XNextEvent(Windows[w].display,&event);
        if (event.type==MappingNotify)
          {
            XRefreshKeyboardMapping((XMappingEvent*) &event);
            status=0;
          }
        if (status!=0) {
          if (event.type==ButtonPress) {
            for (i=0;i<MAX_WINDOWS;i++)
              if (event.xany.window==Windows[i].window) {
                  Push(vm,event.xbutton.x); Push(vm,event.xbutton.y);
                  Push(vm,event.xbutton.button);
                  vm->IPs[cip].x=Windows[i].EventDown[0];
                  vm->IPs[cip].y=Windows[i].EventDown[1];
                  vm->IPs[cip].z=Windows[i].EventDown[2];
                  vm->IPs[cip].DeltaX=1;
                  vm->IPs[cip].DeltaY=0;
                  vm->IPs[cip].DeltaZ=0;
                  Sub_Delta(vm);
                }
            }
          if (event.type==ButtonRelease) {
            for (i=0;i<MAX_WINDOWS;i++)
              if (event.xany.window==Windows[i].window) {
                  Push(vm,event.xbutton.x); Push(vm,event.xbutton.y);
                  Push(vm,event.xbutton.button);
                  vm->IPs[cip].x=Windows[i].EventUp[0];
                  vm->IPs[cip].y=Windows[i].EventUp[1];
                  vm->IPs[cip].z=Windows[i].EventUp[2];
                  vm->IPs[cip].DeltaX=1;
                  vm->IPs[cip].DeltaY=0;
                  vm->IPs[cip].DeltaZ=0;
                  Sub_Delta(vm);
                }
            }
          if (event.type==MotionNotify) {
            for (i=0;i<MAX_WINDOWS;i++)
              if (event.xany.window==Windows[i].window) {
                  Push(vm,event.xmotion.x); Push(vm,event.xmotion.y);
                  Push(vm,event.xmotion.state);
                  vm->IPs[cip].x=Windows[i].Motion[0];
                  vm->IPs[cip].y=Windows[i].Motion[1];
                  vm->IPs[cip].z=Windows[i].Motion[2];
                  vm->IPs[cip].DeltaX=1;
                  vm->IPs[cip].DeltaY=0;
                  vm->IPs[cip].DeltaZ=0;
                  Sub_Delta(vm);
                }
            }
          if (event.type==KeyPress) {
            for (i=0;i<MAX_WINDOWS;i++)
              if (event.xany.window==Windows[i].window) {
                  XLookupString((XKeyEvent*)&event,tmpbuf,10,&key,&keystatus);
                  Push(vm,key);
                  vm->IPs[cip].x=Windows[i].Key[0];
                  vm->IPs[cip].y=Windows[i].Key[1];
                  vm->IPs[cip].z=Windows[i].Key[2];
                  vm->IPs[cip].DeltaX=1;
                  vm->IPs[cip].DeltaY=0;
                  vm->IPs[cip].DeltaZ=0;
                  Sub_Delta(vm);
                }
            }
          if (event.type==Expose) {
            for (i=0;i<MAX_WINDOWS;i++)
              if (event.xany.window==Windows[i].window) {
                  Push(vm,event.xexpose.x);
                  Push(vm,event.xexpose.y);
                  Push(vm,event.xexpose.width);
                  Push(vm,event.xexpose.height);
                  Push(vm,event.xexpose.count);
                  vm->IPs[cip].x=Windows[i].Paint[0];
                  vm->IPs[cip].y=Windows[i].Paint[1];
                  vm->IPs[cip].z=Windows[i].Paint[2];
                  vm->IPs[cip].DeltaX=1;
                  vm->IPs[cip].DeltaY=0;
                  vm->IPs[cip].DeltaZ=0;
                  Sub_Delta(vm);
                }
            }
          if (event.type==ConfigureNotify) {
            for (i=0;i<MAX_WINDOWS;i++)
              if (event.xany.window==Windows[i].window) {
                  Push(vm,event.xconfigure.x);
                  Push(vm,event.xconfigure.y);
                  Push(vm,event.xconfigure.width);
                  Push(vm,event.xconfigure.height);
                  vm->IPs[cip].x=Windows[i].Configure[0];
                  vm->IPs[cip].y=Windows[i].Configure[1];
                  vm->IPs[cip].z=Windows[i].Configure[2];
                  vm->IPs[cip].DeltaX=1;
                  vm->IPs[cip].DeltaY=0;
                  vm->IPs[cip].DeltaZ=0;
                  Sub_Delta(vm);
                }
            }
/*
          if (event.type==FocusIn || event.type==FocusOut) {
            for (i=0;i<MAX_WINDOWS;i++)
              if (event.xany.window==Windows[i].window) {
                a=Find_Function(Windows[i].Focus,c);
                if (a>=0) {
                  if (event.xfocus.type==FocusIn) Put_Stack(1);
                    else Put_Stack(0);
                  Forth(c,c->Functions[a].Ptr);
                  }
                }
            }
          if (event.type==DestroyNotify) {
            for (i=0;i<MAX_WINDOWS;i++)
              if (event.xany.window==Windows[i].window) {
                a=Find_Function(Windows[i].Destroy,c);
                if (a>=0) {
                  Forth(c,c->Functions[a].Ptr);
                  }
                }
            }
*/



          }
      }
    return EventFound;
    }
  else return -1;
}

void Win_Init()
{
  INT i;
  for (i=0;i<MAX_WINDOWS;i++) Windows[i].window=0;
}
 
void Copy_Backing(INT w) {
  XCopyArea(Windows[w].display,
            Windows[w].backing,
            Windows[w].window,
            Windows[w].gc,
            0,0,Windows[w].Width,Windows[w].Height,0,0);
  XFlush(Windows[w].display);
  }

