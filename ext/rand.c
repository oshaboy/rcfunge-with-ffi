/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef RAND
#include <time.h>
#include <sys/time.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_RAND(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_RAND+8;    /* I */
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_RAND+12;  /* M */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_RAND+17;  /* R */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_RAND+18;  /* S */
  vm->IPs[cip].Overloads[19][vm->IPs[cip].NumOvers]=EX_RAND+19;  /* T */
}

void Unload_RAND(VM* vm) {
  Unload_Semantic(vm,8);
  Unload_Semantic(vm,12);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,19);
  }

void Do_RAND(VM* vm,int Cmd)
{
  INT a;
  unsigned int n;
  float fa;
  union {
    float f;
    long int i;
    } FpSp;
  int cip;
  struct timeval tv;
  cip = vm->cip;
  switch (Cmd) {
    case EX_RAND+ 8:n=Pop(vm);                                /* RAND, I */
                    if (n == 0) {
                      Reflect(vm);
                      return;
                      }
                    fa=(float)rand();
                    fa/=RAND_MAX;
                    fa-=(int)fa;
                    fa*=n;
                    n=(int)fa;
                    Push(vm,n);
                    break;
    case EX_RAND+12:Push(vm,RAND_MAX);                        /* RAND, M */
                    break;
    case EX_RAND+17:FpSp.f=(float)rand();                     /* RAND, R */
                    FpSp.f/=RAND_MAX;
                    Push(vm,FpSp.i);
                    break;
    case EX_RAND+18:a=Pop(vm);                                /* RAND, S */
                    srand(a);
                    break;
    case EX_RAND+19:gettimeofday(&tv,NULL);                   /* RAND, T */
                    srand(tv.tv_usec);
                    break;

    }
}
#endif

