/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef MODU
#include <time.h>
#include "funge.h"

void Load_MODU(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_MODU+00;  /* M */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_MODU+02;  /* R */
  vm->IPs[cip].Overloads[20][vm->IPs[cip].NumOvers]=EX_MODU+01;  /* U */
}

void Unload_MODU(VM* vm) {
  Unload_Semantic(vm,12);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,20);
  }

void Do_MODU(VM* vm,int Cmd)
{
  INT a,b;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_MODU+00:b=Pop(vm); a=Pop(vm);               /* MODU, M */
                    if (b==0) Push(vm,0); 
                      else {
                        Push(vm,a-floor((float)(a/b))*b);
                        if ((a<0 && b>=0) || (a>=0 && b<0)) {
                          a=-Pop(vm);
                          Push(vm,a);
                          }
                        }
                    break;
    case EX_MODU+01:b=abs(Pop(vm)); a=abs(Pop(vm));     /* MODU, U */
                    if (b==0) Push(vm,0);
                      else Push(vm,a%b);
                    break;
    case EX_MODU+02:b=Pop(vm); a=Pop(vm);               /* MODU, R */
                    if (b==0) Push(vm,0);
                      else Push(vm,a%b);
                    break;

    }
}
#endif

