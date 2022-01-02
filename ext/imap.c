/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef IMAP
#include <time.h>
#include "funge.h"
/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */


void Load_IMAP(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_IMAP+00;   /* C */
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_IMAP+02;  /* M */
  vm->IPs[cip].Overloads[14][vm->IPs[cip].NumOvers]=EX_IMAP+01;  /* O */
}

void Unload_IMAP(VM* vm) {
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,12);
  Unload_Semantic(vm,14);
  }

void Do_IMAP(VM* vm,int Cmd)
{
  int i,j;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_IMAP+00:for (i=0;i<255;i++) vm->Mapper[i]=i; break;     /*  C */
    case EX_IMAP+01:i=Pop(vm);                                      /*  O */
                    if (i>=0 && i<255) vm->Mapper[i]=i;
                    break;
    case EX_IMAP+02:i=Pop(vm); j=Pop(vm);                           /*  M */
                    if (i>=0 && i<256) vm->Mapper[i]=j;
                      else Reflect(vm);
                    break;
    }
}
#endif

