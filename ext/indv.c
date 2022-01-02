/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef INDV
#include <time.h>
#include "funge.h"

void Load_INDV(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_INDV+00;   /* G */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_INDV+01;  /* P */
  vm->IPs[cip].Overloads[21][vm->IPs[cip].NumOvers]=EX_INDV+02;  /* V */
  vm->IPs[cip].Overloads[22][vm->IPs[cip].NumOvers]=EX_INDV+03;  /* W */
}

void Unload_INDV(VM* vm) {
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,15);
  Unload_Semantic(vm,21);
  Unload_Semantic(vm,22);
  }

void Do_INDV(VM* vm,int Cmd)
{
  INT x,y,z;
  INT a,b,c;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_INDV+00:if (vm->Mode>2) z=Pop(vm); else z=0;     /* PNTR, G */
                    if (vm->Mode>1) y=Pop(vm); else y=0;
                    x=Pop(vm);
                    if (vm->Mode>2) c=Get_Funge(vm,x++,y,z); else c=0;
                    if (vm->Mode>1) b=Get_Funge(vm,x++,y,z); else b=0;
                    a=Get_Funge(vm,x,y,z);
                    Push(vm,Get_Funge(vm,a,b,c)); break;
    case EX_INDV+01:if (vm->Mode>2) z=Pop(vm); else z=0;     /* PNTR, P */
                    if (vm->Mode>1) y=Pop(vm); else y=0;
                    x=Pop(vm);
                    if (vm->Mode>2) c=Get_Funge(vm,x++,y,z); else c=0;
                    if (vm->Mode>1) b=Get_Funge(vm,x++,y,z); else b=0;
                    a=Get_Funge(vm,x,y,z);
                    Put_Funge(vm,a,b,c,Pop(vm)); break;
    case EX_INDV+02:if (vm->Mode>2) z=Pop(vm); else z=0;     /* PNTR, V */
                    if (vm->Mode>1) y=Pop(vm); else y=0;
                    x=Pop(vm);
                    if (vm->Mode>2) c=Get_Funge(vm,x++,y,z); else c=0;
                    if (vm->Mode>1) b=Get_Funge(vm,x++,y,z); else b=0;
                    a=Get_Funge(vm,x,y,z);
                    a += (vm->Mode-1);
                    Push(vm,Get_Funge(vm,a--,b,c));
		    if (vm->Mode>1) Push(vm,Get_Funge(vm,a--,b,c));
                    if (vm->Mode>2) Push(vm,Get_Funge(vm,a--,b,c));
                    break;
    case EX_INDV+03:if (vm->Mode>2) z=Pop(vm); else z=0;     /* PNTR, W */
                    if (vm->Mode>1) y=Pop(vm); else y=0;
                    x=Pop(vm);
                    if (vm->Mode>2) c=Get_Funge(vm,x++,y,z); else c=0;
                    if (vm->Mode>1) b=Get_Funge(vm,x++,y,z); else b=0;
                    a=Get_Funge(vm,x,y,z);
                    if (vm->Mode>2) Put_Funge(vm,a++,b,c,Pop(vm));
                    if (vm->Mode>1) Put_Funge(vm,a++,b,c,Pop(vm));
                    Put_Funge(vm,a,b,c,Pop(vm));
                    break;
    }
}
#endif

