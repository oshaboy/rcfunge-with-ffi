/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef IPMD
#include <time.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_IPMD(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[1][vm->IPs[cip].NumOvers]=EX_IPMD+ 1;   /* B */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_IPMD+ 3;   /* D */
  vm->IPs[cip].Overloads[16][vm->IPs[cip].NumOvers]=EX_IPMD+16;  /* Q */
  vm->IPs[cip].Overloads[19][vm->IPs[cip].NumOvers]=EX_IPMD+19;  /* T */
  vm->IPs[cip].Overloads[20][vm->IPs[cip].NumOvers]=EX_IPMD+20;  /* U */
}

void Unload_IPMD(VM* vm) {
  Unload_Semantic(vm,1);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,16);
  Unload_Semantic(vm,19);
  Unload_Semantic(vm,20);
  }

void Do_IPMD(VM* vm,int Cmd)
{
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_IPMD+ 1:vm->IPs[cip].IPMDMode = 2;           /* IPMD, B */
                    break;
    case EX_IPMD+ 3:vm->IPs[cip].IPMDMode = vm->Mode;    /* IPMD, D */
                    break;
    case EX_IPMD+16:Push(vm,vm->IPs[cip].IPMDMode);      /* IPMD, Q */
                    break;
    case EX_IPMD+19:vm->IPs[cip].IPMDMode = 3;           /* IPMD, T */
                    break;
    case EX_IPMD+20:vm->IPs[cip].IPMDMode = 1;           /* IPMD, U */
                    break;
    }
}
#endif

