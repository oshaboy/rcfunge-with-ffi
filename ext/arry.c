/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef ARRY
#include <time.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_ARRY(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_ARRY+ 0;   /* A */
  vm->IPs[cip].Overloads[1][vm->IPs[cip].NumOvers]=EX_ARRY+ 1;   /* B */
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_ARRY+ 2;   /* C */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_ARRY+ 3;   /* D */
  vm->IPs[cip].Overloads[4][vm->IPs[cip].NumOvers]=EX_ARRY+ 4;   /* E */
  vm->IPs[cip].Overloads[5][vm->IPs[cip].NumOvers]=EX_ARRY+ 5;   /* F */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_ARRY+ 6;   /* G */
}

void Unload_ARRY(VM* vm) {
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,1);
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,4);
  Unload_Semantic(vm,5);
  Unload_Semantic(vm,6);
  }

void Do_ARRY(VM* vm,int Cmd)
{
  VECTOR va;
  int x,y,z,n;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_ARRY+ 0:x=Pop(vm);                           /* ARRY, A */
                    n=Pop(vm);
                    va=Pop_Vector(vm);
                    Put_Funge(vm,va.x+x-vm->IPs[cip].OffsetX,
                                 va.y-vm->IPs[cip].OffsetY,
                                 va.z-vm->IPs[cip].OffsetZ,n);
                    Push_Vector(vm,va);
                    break;
    case EX_ARRY+ 1:x=Pop(vm);                           /* ARRY, B */
                    va=Pop_Vector(vm);
                    n=Get_Funge(vm,va.x+x-vm->IPs[cip].OffsetX,
                                 va.y-vm->IPs[cip].OffsetY,
                                 va.z-vm->IPs[cip].OffsetZ);
                    Push_Vector(vm,va);
                    Push(vm,n);
                    break;
    case EX_ARRY+ 2:y=Pop(vm);                           /* ARRY, C */
                    x=Pop(vm);
                    n=Pop(vm);
                    va=Pop_Vector(vm);
                    Put_Funge(vm,va.x+x-vm->IPs[cip].OffsetX,
                                 va.y+y-vm->IPs[cip].OffsetY,
                                 va.z-vm->IPs[cip].OffsetZ,n);
                    Push_Vector(vm,va);
                    break;
    case EX_ARRY+ 3:y=Pop(vm);                           /* ARRY, D */
                    x=Pop(vm);
                    va=Pop_Vector(vm);
                    n=Get_Funge(vm,va.x+x-vm->IPs[cip].OffsetX,
                                 va.y+y-vm->IPs[cip].OffsetY,
                                 va.z-vm->IPs[cip].OffsetZ);
                    Push_Vector(vm,va);
                    Push(vm,n);
                    break;
    case EX_ARRY+ 4:z=Pop(vm);                           /* ARRY, E */
                    y=Pop(vm);
                    x=Pop(vm);
                    n=Pop(vm);
                    va=Pop_Vector(vm);
                    Put_Funge(vm,va.x+x-vm->IPs[cip].OffsetX,
                                 va.y+y-vm->IPs[cip].OffsetY,
                                 va.z+z-vm->IPs[cip].OffsetZ,n);
                    Push_Vector(vm,va);
                    break;
    case EX_ARRY+ 5:z=Pop(vm);                           /* ARRY, F */
                    y=Pop(vm);
                    x=Pop(vm);
                    va=Pop_Vector(vm);
                    n=Get_Funge(vm,va.x+x-vm->IPs[cip].OffsetX,
                                 va.y+y-vm->IPs[cip].OffsetY,
                                 va.z+z-vm->IPs[cip].OffsetZ);
                    Push_Vector(vm,va);
                    Push(vm,n);
                    break;
    case EX_ARRY+ 6:Push(vm,3);                          /* ARRY, F */
                    break;
    }
}
#endif

