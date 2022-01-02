/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef ORTH
#include <time.h>
#include "funge.h"

void Load_ORTH(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_ORTH+00;   /* A */
  vm->IPs[cip].Overloads[4][vm->IPs[cip].NumOvers]=EX_ORTH+02;   /* E */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_ORTH+07;   /* G */
  vm->IPs[cip].Overloads[14][vm->IPs[cip].NumOvers]=EX_ORTH+01;  /* O */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_ORTH+8;   /* P */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_ORTH+10;  /* S */
  vm->IPs[cip].Overloads[21][vm->IPs[cip].NumOvers]=EX_ORTH+05;  /* V */
  vm->IPs[cip].Overloads[22][vm->IPs[cip].NumOvers]=EX_ORTH+06;  /* W */
  vm->IPs[cip].Overloads[23][vm->IPs[cip].NumOvers]=EX_ORTH+03;  /* X */
  vm->IPs[cip].Overloads[24][vm->IPs[cip].NumOvers]=EX_ORTH+04;  /* Y */
  vm->IPs[cip].Overloads[25][vm->IPs[cip].NumOvers]=EX_ORTH+9;   /* Z */
}

void Unload_ORTH(VM* vm) {
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,4);
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,14);
  Unload_Semantic(vm,15);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,21);
  Unload_Semantic(vm,22);
  Unload_Semantic(vm,23);
  Unload_Semantic(vm,24);
  Unload_Semantic(vm,25);
  }

void Do_ORTH(VM* vm,int Cmd)
{
  INT x,y,a;
  char Buffer[1000];
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_ORTH+00:Push(vm,Pop(vm)&Pop(vm)); break;         /* ORTH, A */
    case EX_ORTH+01:Push(vm,Pop(vm)|Pop(vm)); break;         /* ORTH, O */
    case EX_ORTH+02:Push(vm,Pop(vm)^Pop(vm)); break;         /* ORTH, E */
    case EX_ORTH+03:vm->IPs[cip].x=Pop(vm); break;           /* ORTH, X */
    case EX_ORTH+04:vm->IPs[cip].y=Pop(vm); break;           /* ORTH, Y */
    case EX_ORTH+05:vm->IPs[cip].DeltaX=Pop(vm); break;      /* ORTH, V */
    case EX_ORTH+06:vm->IPs[cip].DeltaY=Pop(vm); break;      /* ORTH, W */
    case EX_ORTH+07:x=Pop(vm); y=Pop(vm);                    /* ORTH, G */
                    Push(vm,Get_Funge(vm,x,y,0)); break;
    case EX_ORTH+8 :x=Pop(vm); y=Pop(vm); a=Pop(vm);         /* ORTH, P */
                    Put_Funge(vm,x,y,0,a); break;
    case EX_ORTH+9 :x=Pop(vm);                               /* ORTH, Z */
                    if (x==0) Add_Delta(vm);
                    break;
    case EX_ORTH+10:Pop_String(vm,Buffer);                   /* ORTH, S */
                    printf("%s",Buffer);
                    break;
    }
}
#endif

