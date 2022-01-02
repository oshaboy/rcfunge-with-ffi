/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef JSTR
#include <time.h>
#include <string.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_JSTR(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_JSTR+06;    /* G */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_JSTR+15;   /* P */
}

void Unload_JSTR(VM* vm) {
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,15);
  }

void Do_JSTR(VM* vm,int Cmd)
{
  INT i,x,y,z,dx,dy,dz,n,b;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_JSTR+06:n=Pop(vm);                           /* JSTR, G */
                    if (vm->Mode>2) z=Pop(vm); else z=0;
                    if (vm->Mode>1) y=Pop(vm); else y=0;
                    x=Pop(vm);
                    if (vm->Mode>2) dz=Pop(vm); else dz=0;
                    if (vm->Mode>1) dy=Pop(vm); else dy=0;
                    dx=Pop(vm);
                    for (i=0; i<n; i++) {
                      Push(vm,Get_Funge(vm,x,y,z));
                      x+=dx;
                      y+=dy;
                      z+=dz;
                      }
               break;
    case EX_JSTR+15:n=Pop(vm);                           /* JSTR, P */
                    if (vm->Mode>2) z=Pop(vm); else z=0;
                    if (vm->Mode>1) y=Pop(vm); else y=0;
                    x=Pop(vm);
                    if (vm->Mode>2) dz=Pop(vm); else dz=0;
                    if (vm->Mode>1) dy=Pop(vm); else dy=0;
                    dx=Pop(vm);
                    for (i=0; i<n; i++) {
                      b=Pop(vm);
                      Put_Funge(vm,x,y,z,b);
                      x+=dx;
                      y+=dy;
                      z+=dz;
                      }
               break;

    }
}
#endif

