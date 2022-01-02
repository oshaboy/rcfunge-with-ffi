/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef BASE
#include <time.h>
#include "funge.h"

void Load_BASE(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[1][vm->IPs[cip].NumOvers]=EX_BASE+02;    /* B */
  vm->IPs[cip].Overloads[7][vm->IPs[cip].NumOvers]=EX_BASE+00;    /* H */
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_BASE+04;    /* I */
  vm->IPs[cip].Overloads[13][vm->IPs[cip].NumOvers]=EX_BASE+03;   /* N */
  vm->IPs[cip].Overloads[14][vm->IPs[cip].NumOvers]=EX_BASE+01;   /* O */
}

void Unload_BASE(VM* vm) {
  Unload_Semantic(vm,1);
  Unload_Semantic(vm,7);
  Unload_Semantic(vm,8);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,13);
  Unload_Semantic(vm,14);
  }


void Base_Out(INT base,UINT v)
{
  char Temp[100];
  INT  i,j;
  if (base<2) return;
  i=0;
  while (v>0) {
    j=v%base;
    if (j<10) Temp[i++]=48+j; else Temp[i++]=87+j;
    v/=base;
    }
  j=i-1;
  while (j>0 && Temp[j]=='0') j--;
  for (i=j;i>=0;i--) printf("%c",Temp[i]);
}

INT Base_In(INT base)
{
  INT v;
  char c;
  INT  ch;
  INT minus;
  v=0; ch=0; minus=0;
  while (ch>=0) {
    c=getchar();
    if (c>='0' && c<='9') ch=c-48;
    else if (c>='a' && c<='z') ch=c-87;
    else if (c>='A' && c<='Z') ch=c-55;
    else if (c=='-' && v==0) minus=1;
    else ch=-1;
    if (ch>=base) ch=-1;
    if (ch>=0) v=v*base+ch;
      else ungetc(c,stdin);
    }
  if (minus==1) v=0-v;
  return v;
}

void Do_BASE(VM* vm,int Cmd)
{
  int b,v;
  switch (Cmd) {
    case EX_BASE+00:printf("%x ",Pop(vm));  break;       /* BASE, H */
    case EX_BASE+01:printf("%o ",Pop(vm));  break;       /* BASE, O */
    case EX_BASE+02:Base_Out(2,Pop(vm)); break;          /* BASE, B */
    case EX_BASE+03:b = Pop(vm);                         /* BASE, N */
                    if (b < 2) {
                      Reflect(vm);
                      return;
                      }
                    v = Pop(vm);
                    Base_Out(b,v);
                    break;
    case EX_BASE+04:Push(vm,Base_In(Pop(vm))); break;    /* BASE, I */
    }
}
#endif

