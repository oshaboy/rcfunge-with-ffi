/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef TERM
#include <time.h>
#include "funge.h"
/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */
void Load_TERM(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_TERM+00;   /* C */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_TERM+02;   /* D */
  vm->IPs[cip].Overloads[11][vm->IPs[cip].NumOvers]=EX_TERM+05;  /* L */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_TERM+01;   /* G */
  vm->IPs[cip].Overloads[7][vm->IPs[cip].NumOvers]=EX_TERM+06;   /* H */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_TERM+04;  /* S */
  vm->IPs[cip].Overloads[20][vm->IPs[cip].NumOvers]=EX_TERM+03;  /* U */
}

void Unload_TERM(VM* vm) {
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,7);
  Unload_Semantic(vm,11);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,20);
  }

void Do_TERM(VM* vm,int Cmd)
{
  INT x,y;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_TERM+00:ClrScr(); break;                                  /*  C */
    case EX_TERM+01:y=Pop(vm); x=Pop(vm); GotoXY(x,y); break;         /*  G */
    case EX_TERM+02:x = Pop(vm);                                      /* D */
                    if (x>=0) CursorDown(x);
                    if (x<0) CursorUp(-x);
                    break;
    case EX_TERM+03:x = Pop(vm);                                      /* U */
                    if (x>=0) CursorUp(x);
                    if (x<0) CursorDown(-x);
                    break;
    case EX_TERM+04:ClrEos(); break;                                  /*  S */
    case EX_TERM+05:ClrEol(); break;                                  /*  L */
    case EX_TERM+06:GotoXY(0,0); break;                               /*  H */
    }
}
#endif

