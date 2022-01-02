/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef WIND
#include <time.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_WIND(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[1][vm->IPs[cip].NumOvers]=EX_WIND+9;    /* B */
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_WIND+06;   /* C */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_WIND+05;   /* D */
  vm->IPs[cip].Overloads[4][vm->IPs[cip].NumOvers]=EX_WIND+13;   /* E */
  vm->IPs[cip].Overloads[5][vm->IPs[cip].NumOvers]=EX_WIND+14;   /* F */
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_WIND+12;   /* I */
  vm->IPs[cip].Overloads[10][vm->IPs[cip].NumOvers]=EX_WIND+01;  /* K */
  vm->IPs[cip].Overloads[11][vm->IPs[cip].NumOvers]=EX_WIND+8;   /* L */
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_WIND+03;  /* M */
  vm->IPs[cip].Overloads[14][vm->IPs[cip].NumOvers]=EX_WIND+07;  /* O */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_WIND+10;  /* P */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_WIND+02;  /* R */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_WIND+04;  /* S */
  vm->IPs[cip].Overloads[19][vm->IPs[cip].NumOvers]=EX_WIND+11;  /* T */
  vm->IPs[cip].Overloads[22][vm->IPs[cip].NumOvers]=EX_WIND+00;  /* W */
  vm->IPs[cip].Overloads[24][vm->IPs[cip].NumOvers]=EX_WIND+15;  /* Y */
}

void Unload_WIND(VM* vm) {
  Unload_Semantic(vm,1);
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,4);
  Unload_Semantic(vm,5);
  Unload_Semantic(vm,8);
  Unload_Semantic(vm,10);
  Unload_Semantic(vm,11);
  Unload_Semantic(vm,12);
  Unload_Semantic(vm,14);
  Unload_Semantic(vm,15);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,19);
  Unload_Semantic(vm,22);
  Unload_Semantic(vm,24);
  }

void Do_WIND(VM* vm,int Cmd)
{
  INT w,h,a;
  INT x,y,z;
  INT r,g,b;
  char Buffer[1000];
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_WIND+00:h=Pop(vm); w=Pop(vm);               /* WIND, W */
                    y=Pop(vm); x=Pop(vm);
                    Push(vm,New_Window(x,y,w,h));
                    break;
    case EX_WIND+01:a=Close_Window(Pop(vm));             /* WIND, K */
                    if (a != 0) Reflect(vm);
                    break;
    case EX_WIND+02:a=Raise_Window(Pop(vm));             /* WIND, R */
                    if (a != 0) Reflect(vm);
                    break;
    case EX_WIND+03:w=Pop(vm); y=Pop(vm); x=Pop(vm);   /* WIND, M */
                    a=Move_Window(w,x,y);
                    if (a != 0) Reflect(vm);
                    break;
    case EX_WIND+04:w=Pop(vm); y=Pop(vm); x=Pop(vm);   /* WIND, S */
                    a=Size_Window(w,x,y);
                    if (a != 0) Reflect(vm);
                    break;
    case EX_WIND+05:a=Lower_Window(Pop(vm));             /* WIND, D */
                    if (a != 0) Reflect(vm);
                    break;
    case EX_WIND+06:a=Close_GC(Pop(vm));                /* WIND, C */
                    if (a != 0) Reflect(vm);
                    break;
    case EX_WIND+07:a=Open_GC(Pop(vm));                 /* WIND, O */
                    if (a != 0) Reflect(vm);
                    break;
    case EX_WIND+8 :h=Pop(vm); b=Pop(vm); a=Pop(vm);  /* WIND, L */
                    y=Pop(vm); x=Pop(vm);
                    a=Line(h,x,y,a,b);
                    if (a != 0) Reflect(vm);
                    break;
    case EX_WIND+9 :h=Pop(vm); b=Pop(vm); a=Pop(vm);  /* WIND, B */
                    y=Pop(vm); x=Pop(vm);
                    a=Box(h,x,y,a,b);
                    if (a != 0) Reflect(vm);
                    break;
    case EX_WIND+10:h=Pop(vm); y=Pop(vm); x=Pop(vm);  /* WIND, P */
                    a=Point(h,x,y);
                    if (a != 0) Reflect(vm);
                    break;
    case EX_WIND+11:h=Pop(vm); y=Pop(vm); x=Pop(vm);  /* WIND, T */
                    Pop_String(vm,Buffer);
                    a=Text(h,Buffer,x,y);
                    if (a != 0) Reflect(vm);
                    break;
    case EX_WIND+12:h=Pop(vm); b=Pop(vm);              /* WIND, I */
                    if (vm->Mode>2) z=Pop(vm); else z=0;
                    if (vm->Mode>1) y=Pop(vm); else y=0;
                    x=Pop(vm);
                    a=Install_Handler(h,b,x,y,z);
                    if (a != 0) Reflect(vm);
                    break;
    case EX_WIND+13:h=Pop(vm);                          /* WIND, E */
                    a=Event(vm,h);
                    break;
    case EX_WIND+14:h=Pop(vm);                          /* WIND, F */
                    b = Pop(vm);
                    g = Pop(vm);
                    r = Pop(vm);
                    Foreground_Color(h,r,g,b);
                    break;
    case EX_WIND+15:h=Pop(vm);                          /* WIND, Y */
                    Copy_Backing(h);
                    break;
    }
}
#endif

