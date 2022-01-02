/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef MODE
#include <time.h>
#include "funge.h"

void Load_MODE(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip; 
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[7][vm->IPs[cip].NumOvers]=EX_MODE+00;   /* H */
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_MODE+01;   /* I */
  vm->IPs[cip].Overloads[16][vm->IPs[cip].NumOvers]=EX_MODE+02;  /* Q */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_MODE+03;  /* S */
}

void Unload_MODE(VM* vm) {
  Unload_Semantic(vm,7);
  Unload_Semantic(vm,8);
  Unload_Semantic(vm,16);
  Unload_Semantic(vm,18);
  }

void Do_MODE(VM* vm,int Cmd)
{
  int cip; 
  cip = vm->cip;
  switch (Cmd) {
    case EX_MODE+00:vm->IPs[cip].HoverMode=1-vm->IPs[cip].HoverMode; break;   /*  H */
    case EX_MODE+01:vm->IPs[cip].InvertMode=1-vm->IPs[cip].InvertMode; break; /*  I */
    case EX_MODE+02:vm->IPs[cip].QueueMode=1-vm->IPs[cip].QueueMode; break;   /*  Q */
    case EX_MODE+03:vm->IPs[cip].SwitchMode=1-vm->IPs[cip].SwitchMode; break; /*  S */
    }
}
#endif

