/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef IIPC
#include "funge.h"
/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */


void Load_IIPC(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_IIPC+01;     /* A */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_IIPC+05;     /* D */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_IIPC+04;     /* G */
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_IIPC+00;     /* I */
  vm->IPs[cip].Overloads[11][vm->IPs[cip].NumOvers]=EX_IIPC+02;    /* L */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_IIPC+03;    /* P */
}

void Unload_IIPC(VM* vm) {
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,8);
  Unload_Semantic(vm,11);
  Unload_Semantic(vm,15);
  }

void Do_IIPC(VM* vm,int Cmd)
{
  int i,a,b;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_IIPC+00:Push(vm,vm->IPs[cip].uid); break;                    /*  I */
    case EX_IIPC+01:Push(vm,vm->IPs[cip].parent); break;                 /*  A */
    case EX_IIPC+02:a=Pop(vm);                                       /*  L */
                    for (i=0;i<vm->NumIPs;i++)
                      if (vm->IPs[i].uid==a) {
                        vm->cip = i;
                        b=Pop(vm); Push(vm,b);
                        vm->cip = cip;
                        Push(vm,b);
                        i=vm->NumIPs;
                        }
                    break;
    case EX_IIPC+03:a=Pop(vm); b=Pop(vm);                           /*  P */
                    for (i=0;i<vm->NumIPs;i++)
                      if (vm->IPs[i].uid==a) {
                        vm->cip = i;
                        Push(vm,b);
                        vm->cip = cip;
                        vm->IPs[i].dormant=0;
                        i=vm->NumIPs;
                        }
                    break;
    case EX_IIPC+04:a=Pop(vm);                                       /*  G */
                    for (i=0;i<vm->NumIPs;i++)
                      if (vm->IPs[i].uid==a) {
                        vm->cip = i;
                        b=Pop(vm);
                        vm->cip = cip;
                        Push(vm,b);
                        vm->IPs[i].dormant=0;
                        i=vm->NumIPs;
                        }
                    break;
    case EX_IIPC+05:vm->IPs[cip].dormant=1; break;                        /*  G */
    }
}
#endif

