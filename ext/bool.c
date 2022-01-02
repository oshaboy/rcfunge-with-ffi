/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef BOOL
#include <time.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_BOOL(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_BOOL+ 0;   /* A */
  vm->IPs[cip].Overloads[13][vm->IPs[cip].NumOvers]=EX_BOOL+13;  /* N */
  vm->IPs[cip].Overloads[14][vm->IPs[cip].NumOvers]=EX_BOOL+14;  /* O */
  vm->IPs[cip].Overloads[23][vm->IPs[cip].NumOvers]=EX_BOOL+23;  /* X */
}

void Unload_BOOL(VM* vm) {
  Unload_Semantic(vm,2);
  }

void Do_BOOL(VM* vm,int Cmd)
{
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_BOOL+ 0:Push(vm,Pop(vm) & Pop(vm));          /* BOOL, I */
                    break;
    case EX_BOOL+13:Push(vm,~Pop(vm));                   /* BOOL, N */
                    break;
    case EX_BOOL+14:Push(vm,Pop(vm) | Pop(vm));          /* BOOL, O */
                    break;
    case EX_BOOL+23:Push(vm,Pop(vm) ^ Pop(vm));          /* BOOL, X */
                    break;
    }
}
#endif

