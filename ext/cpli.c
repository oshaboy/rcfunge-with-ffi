/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef CPLI
#include <time.h>
#include "funge.h"
/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */


void Load_CPLI(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_CPLI+00;   /* A */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_CPLI+04;   /* D */
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_CPLI+02;  /* M */
  vm->IPs[cip].Overloads[14][vm->IPs[cip].NumOvers]=EX_CPLI+03;  /* O */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_CPLI+01;  /* S */
  vm->IPs[cip].Overloads[21][vm->IPs[cip].NumOvers]=EX_CPLI+05;  /* V */
}

void Unload_CPLI(VM* vm) {
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,12);
  Unload_Semantic(vm,14);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,21);
  }

void Do_CPLI(VM* vm,int Cmd)
{
  INT ar,ai,br,bi;
  INT a,b,c,d;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_CPLI+00:bi=Pop(vm); br=Pop(vm);                         /*  A */
                    ai=Pop(vm); ar=Pop(vm);
                    Push(vm,ar+br); Push(vm,ai+bi); break;
    case EX_CPLI+01:bi=Pop(vm); br=Pop(vm);                         /*  S */
                    ai=Pop(vm); ar=Pop(vm);
                    Push(vm,ar-br); Push(vm,ai-bi); break;
    case EX_CPLI+02:bi=Pop(vm); br=Pop(vm);                         /*  M */
                    ai=Pop(vm); ar=Pop(vm);
                    Push(vm,ar*br-ai*bi);
                    Push(vm,ar*bi+ai*br); break;
    case EX_CPLI+03:bi=Pop(vm); br=Pop(vm);                         /*  O */
                    printf("(%d%+di) ",br,bi); break;
    case EX_CPLI+04:d=Pop(vm); c=Pop(vm);                           /*  D */
                    b=Pop(vm); a=Pop(vm);
                    Push(vm,(a*c+b*d)/(c*c+d*d));
                    Push(vm,(b*c-a*d)/(c*c+d*d)); break;
    case EX_CPLI+05:b=Pop(vm); a=Pop(vm);                           /*  V */
                    Push(vm,sqrt(a*a+b*b)); break;
    }
}
#endif

