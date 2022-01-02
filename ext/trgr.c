/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef TRGR
#include <time.h>
#include "funge.h"

void Load_TRGR(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  for (i=0; i<26; i++) 
    vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=EX_TRGR+i;
}

void Unload_TRGR(VM* vm) {
  int i;
  for (i=0;i<26; i++)
    Unload_Semantic(vm,i);
  }

void Do_TRGR(VM* vm,int Cmd)
{
  int cip;
  int mx,my,mz;
  cip = vm->cip;
    if (Cmd >= EX_TRGR && Cmd <=EX_TRGR+24) {             /* TRGR, A-Y */
      mx = vm->IPs[cip].mx;
      my = vm->IPs[cip].my+(Cmd - EX_TRGR);
      mz = vm->IPs[cip].mz;

/*      New_IP(vm); */
      Insert_IP(vm,Dup_IP(vm->IPs[cip]));
      vm->IPs[vm->NumIPs-1].DeltaX=1;
      vm->IPs[vm->NumIPs-1].DeltaY=0;
      vm->IPs[vm->NumIPs-1].DeltaZ=0;
      vm->IPs[vm->NumIPs-1].x = mx;
      vm->IPs[vm->NumIPs-1].y = my;
      vm->IPs[vm->NumIPs-1].z = mz;
      vm->cip = vm->NumIPs-1;
      Push(vm,vm->IPs[cip].uid);
      vm->cip = cip;
      Push(vm,vm->IPs[vm->NumIPs-1].uid);
      }
    if (Cmd == EX_TRGR+25) {                              /* TRGR, Z */
      if (vm->Mode>2) mz=Pop(vm); else mz=0;
      if (vm->Mode>1) my=Pop(vm); else my=0;
      mx=Pop(vm);
      vm->IPs[cip].mx = mx;
      vm->IPs[cip].my = my;
      vm->IPs[cip].mz = mz;
      }
}
#endif

