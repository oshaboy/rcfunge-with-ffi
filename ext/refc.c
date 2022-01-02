/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef REFC
#include <time.h>
#include "funge.h"

void Load_REFC(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_REFC+01;   /* D */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_REFC+00;  /* R */
}

void Unload_REFC(VM* vm) {
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,17);
  }

void Do_REFC(VM* vm,int Cmd)
{
  INT i,a;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case  EX_REFC+00:i=0;                                  /* REFC, R */
                    while (i<MAX_VECTORS && vm->Vectors[i].Alloc!=0) i++;
                    if (i!=MAX_VECTORS) {
                      if (vm->Mode>2) vm->Vectors[i].z=Pop(vm); else vm->Vectors[i].z=0;
                      if (vm->Mode>1) vm->Vectors[i].y=Pop(vm); else vm->Vectors[i].y=0;
                      vm->Vectors[i].x=Pop(vm);
                      vm->Vectors[i].Alloc=1;
                      Push(vm,i);
                      }
                    else Reflect(vm);
                    break;
    case  EX_REFC+01:a=Pop(vm);                           /* REFC, D */
                    if (vm->Vectors[a].Alloc>0) {
                      Push(vm,vm->Vectors[a].x);
                      if (vm->Mode>1) Push(vm,vm->Vectors[a].y);
                      if (vm->Mode>2) Push(vm,vm->Vectors[a].z);
                      } else Reflect(vm);
                    break;
    }
}
#endif

