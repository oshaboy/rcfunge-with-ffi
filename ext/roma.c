/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef ROMA
#include <time.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_ROMA(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_ROMA+00;   /* I */
  vm->IPs[cip].Overloads[21][vm->IPs[cip].NumOvers]=EX_ROMA+01;  /* V */
  vm->IPs[cip].Overloads[23][vm->IPs[cip].NumOvers]=EX_ROMA+02;  /* X */
  vm->IPs[cip].Overloads[11][vm->IPs[cip].NumOvers]=EX_ROMA+03;  /* L */
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_ROMA+04;   /* C */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_ROMA+05;   /* D */
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_ROMA+06;  /* M */
}

void Unload_ROMA(VM* vm) {
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,8);
  Unload_Semantic(vm,11);
  Unload_Semantic(vm,12);
  Unload_Semantic(vm,21);
  Unload_Semantic(vm,23);
  }

void Do_ROMA(VM* vm,int Cmd)
{
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_ROMA+00:Push(vm,1); break;                   /* ROMA, I */
    case EX_ROMA+01:Push(vm,5); break;                   /* ROMA, V */
    case EX_ROMA+02:Push(vm,10); break;                  /* ROMA, X */
    case EX_ROMA+03:Push(vm,50); break;                  /* ROMA, L */
    case EX_ROMA+04:Push(vm,100); break;                 /* ROMA, C */
    case EX_ROMA+05:Push(vm,500); break;                 /* ROMA, D */
    case EX_ROMA+06:Push(vm,1000); break;                /* ROMA, M */
    }
}
#endif

