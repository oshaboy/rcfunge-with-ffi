/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef FRTH
#include <time.h>
#include "funge.h"

void Load_FRTH(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_FRTH+00;   /* D */
  vm->IPs[cip].Overloads[11][vm->IPs[cip].NumOvers]=EX_FRTH+01;  /* L */
  vm->IPs[cip].Overloads[14][vm->IPs[cip].NumOvers]=EX_FRTH+02;  /* O */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_FRTH+03;  /* P */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_FRTH+04;  /* R */
}

void Unload_FRTH(VM* vm) {
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,11);
  Unload_Semantic(vm,14);
  Unload_Semantic(vm,15);
  Unload_Semantic(vm,17);
  }

void Do_FRTH(VM* vm,int Cmd)
{
  INT a,b,c,i;
  int cip;
  INT *temp;
  cip = vm->cip;
  switch (Cmd) {
    case EX_FRTH+00:Push(vm,vm->IPs[cip].StackPtr); break;   /* FRTH, D */
    case EX_FRTH+01:a=Pop(vm);                           /* FRTH, L */
                    if (a > 0) {
                      a++;
                      temp = (INT*)malloc(sizeof(INT) * a);
                      for (i=0; i<a; i++) temp[i] = Pop(vm);
                      for (i=a-2; i>=0; i--) Push(vm,temp[i]);
                      Push(vm,temp[a-1]);
                      free(temp);
                      }
                    if (a < 0) {
                      a = 0-a;
                      a++;
                      temp = (INT*)malloc(sizeof(INT) * a);
                      for (i=0; i<a; i++) temp[i] = Pop(vm);
                      Push(vm,temp[0]);
                      for (i=a-1; i>0; i--) Push(vm,temp[i]);
                      free(temp);
                      }
                    break;
    case EX_FRTH+02:a=Pop(vm); b=Pop(vm);               /* FRTH, O */
                    Push(vm,b); Push(vm,a); Push(vm,b);
                    break;
    case EX_FRTH+03:a=Pop(vm);                           /* FRTH, P */
                    if (a < 0) {
                      Reflect(vm);
                      return;
                      }
                    a++;
                    if (a>vm->IPs[cip].StackPtr) Push(vm,0);
                      else Push(vm,vm->IPs[cip].Stack[vm->IPs[cip].StackPtr-a]);
                    break;
    case EX_FRTH+04:a=Pop(vm); b=Pop(vm); c=Pop(vm);   /* FRTH, R */
                    Push(vm,b); Push(vm,a); Push(vm,c);
                    break;

    }
}
#endif

