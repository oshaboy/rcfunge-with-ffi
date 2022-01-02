/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef FPRT
#include <time.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_FPRT(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_FPRT+ 3;   /* D */
  vm->IPs[cip].Overloads[5][vm->IPs[cip].NumOvers]=EX_FPRT+ 5;   /* F */
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_FPRT+ 8;   /* I */
  vm->IPs[cip].Overloads[11][vm->IPs[cip].NumOvers]=EX_FPRT+11;  /* L */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_FPRT+18;  /* S */
}

void Unload_FPRT(VM* vm) {
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,5);
  Unload_Semantic(vm,8);
  Unload_Semantic(vm,11);
  Unload_Semantic(vm,18);
  }

void Do_FPRT(VM* vm,int Cmd)
{
  int i;
  long long l,l2;
  int cip;
  char fmt[1000];
  char buf[1000];
  char str[1000];
  union {
    float f;
    long int i;
    } FpSp;
  cip = vm->cip;
  switch (Cmd) {
    case EX_FPRT+ 5:FpSp.i=Pop(vm);                      /* FPRT, F */
                    Pop_String(vm,fmt);
                    i=sprintf(buf,fmt,FpSp.f);
                    if (i<0) {
                      Reflect(vm);
                      return;
                      }
                    Push_String(vm,buf);
                    break;
    case EX_FPRT+ 8:i=Pop(vm);                           /* FPRT, I */
                    Pop_String(vm,fmt);
                    i=sprintf(buf,fmt,i);
                    if (i<0) {
                      Reflect(vm);
                      return;
                      }
                    Push_String(vm,buf);
                    break;
    case EX_FPRT+11:l=Pop(vm);                           /* FPRT, L */
                    l2=Pop(vm);
                    l = (l2 << 32) | l;
                    Pop_String(vm,fmt);
                    i=sprintf(buf,fmt,l);
                    if (i<0) {
                      Reflect(vm);
                      return;
                      }
                    Push_String(vm,buf);
                    break;
    case EX_FPRT+18:Pop_String(vm,str);                  /* FPRT, S */
                    Pop_String(vm,fmt);
                    i=sprintf(buf,fmt,str);
                    if (i<0) {
                      Reflect(vm);
                      return;
                      }
                    Push_String(vm,buf);
                    break;
    }
}
#endif

