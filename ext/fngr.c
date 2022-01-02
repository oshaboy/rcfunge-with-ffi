/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef FNGR
#include <time.h>
#include "funge.h"
/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */


void Load_FNGR(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_FNGR+00;   /* A */
  vm->IPs[cip].Overloads[1][vm->IPs[cip].NumOvers]=EX_FNGR+01;   /* B */
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_FNGR+02;   /* C */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_FNGR+03;   /* D */
  vm->IPs[cip].Overloads[5][vm->IPs[cip].NumOvers]=EX_FNGR+04;   /* F */
  vm->IPs[cip].Overloads[10][vm->IPs[cip].NumOvers]=EX_FNGR+05;  /* K */
  vm->IPs[cip].Overloads[13][vm->IPs[cip].NumOvers]=EX_FNGR+06;  /* N */
  vm->IPs[cip].Overloads[14][vm->IPs[cip].NumOvers]=EX_FNGR+07;  /* O */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_FNGR+8;   /* R */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_FNGR+10;  /* S */
  vm->IPs[cip].Overloads[19][vm->IPs[cip].NumOvers]=EX_FNGR+11;  /* T */
  vm->IPs[cip].Overloads[23][vm->IPs[cip].NumOvers]=EX_FNGR+9;   /* X */
  vm->IPs[cip].FNGRloaded = 1;
}

void Unload_FNGR(VM* vm) {
  vm->IPs[vm->cip].FNGRloaded = 0;
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,1);
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,5);
  Unload_Semantic(vm,10);
  Unload_Semantic(vm,13);
  Unload_Semantic(vm,14);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,19);
  Unload_Semantic(vm,23);
  }

void CopyFingerprint(VM* vm,int dest,int src)
{ 
  int i;
  int cip;
  cip = vm->cip;
  for (i=0;i<26;i++)
    vm->IPs[cip].Overloads[i][dest]=vm->IPs[cip].Overloads[i][src];
  vm->IPs[cip].OverFinger[dest]=vm->IPs[cip].OverFinger[src];
} 
  
void SwapFingerprint(VM* vm,int dest,int src)
{ 
  int i;
  INT tmp; 
  int cip;
  cip = vm->cip;
  for (i=0;i<26;i++) {
    tmp=vm->IPs[cip].Overloads[i][dest];
    vm->IPs[cip].Overloads[i][dest]=vm->IPs[cip].Overloads[i][src];
    vm->IPs[cip].Overloads[i][src]=tmp;
    }
  tmp=vm->IPs[cip].OverFinger[dest];
  vm->IPs[cip].OverFinger[dest]=vm->IPs[cip].OverFinger[src];
  vm->IPs[cip].OverFinger[src]=tmp;
}

void Do_FNGR(VM* vm,int Cmd)
{
  int i,o,n,old,new;
  INT fp;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_FNGR+00:vm->IPs[cip].FingerMode=FINGER_ABS;               /*  A */
                    vm->IPs[cip].FingerSearch=-1; break;
    case EX_FNGR+01:vm->IPs[cip].NumOvers++;                          /*  B */
                    for (i=0;i<26;i++)
                      vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
                      vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=0xffffffff;
                      Push(vm,0xffffffff); Push(vm,1); break;
    case EX_FNGR+02:o=Pop(vm); old=Pop(vm)-65;                      /*  C */
                    n=Pop(vm); new=Pop(vm)-65;
                    if (o<vm->IPs[cip].NumOvers && n<vm->IPs[cip].NumOvers &&
                        o>=0 && n>=0 &&
                        old>=0 && old<26 && new>=0 && new<26) {
                      vm->IPs[cip].Overloads[new][vm->IPs[cip].NumOvers-n]=
                        vm->IPs[cip].Overloads[old][vm->IPs[cip].NumOvers-o];
                      }
                      else Reflect(vm);
                    break;
    case EX_FNGR+03:o=Pop(vm); old=Pop(vm)-65;                      /*  D */
                    if (o<vm->IPs[cip].NumOvers && o>=0 && old>=0 && old<26) {
                      vm->IPs[cip].Overloads[old][vm->IPs[cip].NumOvers-o]=0;
                      }
                      else Reflect(vm);
                    break;
    case EX_FNGR+04:fp=Pop(vm);                                      /*  F */
                    i=vm->IPs[cip].NumOvers;
                    while (fp!=vm->IPs[cip].OverFinger[i] && i>0) i--;
                    if (i>0) Push(vm,vm->IPs[cip].NumOvers-i);
                    else Reflect(vm);
                    break;
    case EX_FNGR+05:o=Pop(vm);                                       /*  K */
                    if (o<vm->IPs[cip].NumOvers && o>=0) {
                      o=vm->IPs[cip].NumOvers-o;
                      for (i=o;i<vm->IPs[cip].NumOvers;i++)
                        CopyFingerprint(vm,i,i+1);
                      vm->IPs[cip].NumOvers--;
                      }
                      else Reflect(vm);
                    break;
    case EX_FNGR+06:Push(vm,vm->IPs[cip].NumOvers); break;           /*  N */
    case EX_FNGR+07:vm->IPs[cip].FingerMode=FINGER_NORM; break;      /*  O */
    case EX_FNGR+8 :vm->IPs[cip].FingerMode=FINGER_ROLL; break;      /*  R */
    case EX_FNGR+9 :o=Pop(vm);                                       /*  X */
                    n=Pop(vm);
                    if (o<vm->IPs[cip].NumOvers && n<vm->IPs[cip].NumOvers &&
                        o>=0 && n>=0) {
                      o=vm->IPs[cip].NumOvers-o;
                      n=vm->IPs[cip].NumOvers-n;
                      SwapFingerprint(vm,o,n);
                      }
                      else Reflect(vm);
                    break;
    case EX_FNGR+10:vm->IPs[cip].FingerMode=FINGER_SWAP; break;     /*  S */
    case EX_FNGR+11:o=Pop(vm); n=Pop(vm);                           /*  T */
                    if (o<vm->IPs[cip].NumOvers && o>=0) {
                      o=vm->IPs[cip].NumOvers-o;
                      vm->IPs[cip].OverFinger[o]=n;
                      }
                      else Reflect(vm);
                    break;
    }
}
#endif

