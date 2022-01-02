/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef SUBR
#include <time.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_SUBR(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_SUBR+03;   /* A */
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_SUBR+01;   /* C */
  vm->IPs[cip].Overloads[9][vm->IPs[cip].NumOvers]=EX_SUBR+00;   /* J */
  vm->IPs[cip].Overloads[14][vm->IPs[cip].NumOvers]=EX_SUBR+04;  /* O */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_SUBR+02;  /* R */
}

void Unload_SUBR(VM* vm) {
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,9);
  Unload_Semantic(vm,14);
  Unload_Semantic(vm,17);
  }

void Do_SUBR(VM* vm,int Cmd)
{
  INT x,y,z,i,a;
  INT Temp[500];
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_SUBR+00:if (vm->Mode>2) z=Pop(vm); else z=0;     /* SUBR, J */
                    if (vm->Mode>1) y=Pop(vm); else y=0;
                    x=Pop(vm);
                    vm->IPs[cip].x=x;
                    vm->IPs[cip].y=y;
                    vm->IPs[cip].z=z;
                    vm->IPs[cip].DeltaX=1;
                    vm->IPs[cip].DeltaY=0;
                    vm->IPs[cip].DeltaZ=0;
                    if (vm->IPs[cip].subr_mode == 'O') {
                      vm->IPs[cip].x+=vm->IPs[cip].OffsetX;
                      vm->IPs[cip].y+=vm->IPs[cip].OffsetY;
                      vm->IPs[cip].z+=vm->IPs[cip].OffsetZ;
                      }
                    Sub_Delta(vm);
                    break;
    case EX_SUBR+01:a=Pop(vm);                           /* SUBR, C */
                    if (vm->Mode>2) z=Pop(vm); else z=0;
                    if (vm->Mode>1) y=Pop(vm); else y=0;
                    x=Pop(vm);
                    for (i=0;i<a;i++) Temp[i]=Pop(vm);
                    Push(vm,vm->IPs[cip].x);
                    if (vm->Mode>1) Push(vm,vm->IPs[cip].y);
                    if (vm->Mode>2) Push(vm,vm->IPs[cip].z);
                    Push(vm,vm->IPs[cip].DeltaX);
                    if (vm->Mode>1) Push(vm,vm->IPs[cip].DeltaY);
                    if (vm->Mode>2) Push(vm,vm->IPs[cip].DeltaZ);
                    for (i=a-1;i>=0;i--) Push(vm,Temp[i]);
                    vm->IPs[cip].x=x;
                    vm->IPs[cip].y=y;
                    vm->IPs[cip].z=z;
                    vm->IPs[cip].DeltaX=1;
                    vm->IPs[cip].DeltaY=0;
                    vm->IPs[cip].DeltaZ=0;
                    if (vm->IPs[cip].subr_mode == 'O') {
                      vm->IPs[cip].x+=vm->IPs[cip].OffsetX;
                      vm->IPs[cip].y+=vm->IPs[cip].OffsetY;
                      vm->IPs[cip].z+=vm->IPs[cip].OffsetZ;
                      }
                    Sub_Delta(vm);
                    break;
    case EX_SUBR+02:a=Pop(vm);                           /* SUBR, R */
                    for (i=0;i<a;i++) Temp[i]=Pop(vm);
                    if (vm->Mode>2) vm->IPs[cip].DeltaZ=Pop(vm);
                      else vm->IPs[cip].DeltaZ=0;
                    if (vm->Mode>1) vm->IPs[cip].DeltaY=Pop(vm);
                      else vm->IPs[cip].DeltaY=0;
                    vm->IPs[cip].DeltaX=Pop(vm);
                    if (vm->Mode>2) vm->IPs[cip].z=Pop(vm); else vm->IPs[cip].z=0;
                    if (vm->Mode>1) vm->IPs[cip].y=Pop(vm); else vm->IPs[cip].y=0;
                    vm->IPs[cip].x=Pop(vm);
                    for (i=a-1;i>=0;i--) Push(vm,Temp[i]);
                    break;
    case EX_SUBR+ 3:vm->IPs[cip].subr_mode = 'A';            /* SUBR, A */
                    break;
    case EX_SUBR+ 4:vm->IPs[cip].subr_mode = 'O';            /* SUBR, O */
                    break;

    }
}
#endif

