/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef LONG
#include <time.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_LONG(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_LONG+00;   /* A */
  vm->IPs[cip].Overloads[1][vm->IPs[cip].NumOvers]=EX_LONG+01;   /* B */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_LONG+03;   /* D */
  vm->IPs[cip].Overloads[4][vm->IPs[cip].NumOvers]=EX_LONG+04;   /* E */
  vm->IPs[cip].Overloads[11][vm->IPs[cip].NumOvers]=EX_LONG+11;  /* L */
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_LONG+12;  /* M */
  vm->IPs[cip].Overloads[13][vm->IPs[cip].NumOvers]=EX_LONG+13;  /* N */
  vm->IPs[cip].Overloads[14][vm->IPs[cip].NumOvers]=EX_LONG+14;  /* O */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_LONG+15;  /* P */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_LONG+17;  /* R */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_LONG+18;  /* S */
  vm->IPs[cip].Overloads[25][vm->IPs[cip].NumOvers]=EX_LONG+25;  /* Z */
}

void Unload_LONG(VM* vm) {
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,1);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,11);
  Unload_Semantic(vm,12);
  Unload_Semantic(vm,13);
  Unload_Semantic(vm,14);
  Unload_Semantic(vm,15);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,25);
  }

void Do_LONG(VM* vm,int Cmd)
{
  UINT h1,l1,l2,i,n;
  DINT v1,v2;
  INT sl1,sh1;
  char Buffer[1000];
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_LONG+ 0:l1=Pop(vm);                           /* LONG, A */
                    v1=Pop(vm);
                    l2=Pop(vm);
                    v2=Pop(vm);
                    v1 = (v1<<32) | l1;
                    v2 = (v2<<32) | l2;
                    v1 += v2;
                    h1 = (v1 >> 32);
                    l1 = (v1 & 0xffffffff);
                    Push(vm,h1); 
                    Push(vm,l1);
                    break;
    case EX_LONG+ 1:l1=Pop(vm);                           /* LONG, B */
                    v1=Pop(vm);
                    v1 = (v1<<32) | l1;
                    if (v1 < 0) v1 = 0-v1;
                    h1 = (v1 >> 32);
                    l1 = (v1 & 0xffffffff);
                    Push(vm,h1); 
                    Push(vm,l1);
                    break;
    case EX_LONG+ 3:l1=Pop(vm);                           /* LONG, D */
                    v1=Pop(vm);
                    l2=Pop(vm);
                    v2=Pop(vm);
                    v1 = (v1<<32) | l1;
                    v2 = (v2<<32) | l2;
                    if (v1 == 0) v2 = 0;
                      else v2 /= v1;
                    h1 = (v2 >> 32);
                    l1 = (v2 & 0xffffffff);
                    Push(vm,h1); 
                    Push(vm,l1);
                    break;
    case EX_LONG+ 4:sl1=Pop(vm);                          /* LONG, E */
                    sh1 = (sl1 < 0) ? -1 : 0;
                    Push(vm,sh1);
                    Push(vm,sl1);
                    break;
    case EX_LONG+11:n=Pop(vm);                            /* LONG, L */
                    if (n < 0) {
                      Reflect(vm);
                      return;
                      }
                    l1=Pop(vm);
                    v1=Pop(vm);
                    v1 = (v1<<32) | l1;
                    for (i=0; i<n; i++) v1 <<= 1;
                    h1 = (v1 >> 32);
                    l1 = (v1 & 0xffffffff);
                    Push(vm,h1); 
                    Push(vm,l1);
                    break;
    case EX_LONG+12:l1=Pop(vm);                           /* LONG, M */
                    v1=Pop(vm);
                    l2=Pop(vm);
                    v2=Pop(vm);
                    v1 = (v1<<32) | l1;
                    v2 = (v2<<32) | l2;
                    v1 *= v2;
                    h1 = (v1 >> 32);
                    l1 = (v1 & 0xffffffff);
                    Push(vm,h1); 
                    Push(vm,l1);
                    break;
    case EX_LONG+13:l1=Pop(vm);                           /* LONG, N */
                    v1=Pop(vm);
                    v1 = (v1<<32) | l1;
                    v1 = 0-v1;
                    h1 = (v1 >> 32);
                    l1 = (v1 & 0xffffffff);
                    Push(vm,h1); 
                    Push(vm,l1);
                    break;
    case EX_LONG+14:l1=Pop(vm);                           /* LONG, O */
                    v1=Pop(vm);
                    l2=Pop(vm);
                    v2=Pop(vm);
                    v1 = (v1<<32) | l1;
                    v2 = (v2<<32) | l2;
                    if (v1 == 0) v2 = 0;
                      else v2 = v2 % v1;
                    h1 = (v2 >> 32);
                    l1 = (v2 & 0xffffffff);
                    Push(vm,h1); 
                    Push(vm,l1);
                    break;
    case EX_LONG+15:l1=Pop(vm);                           /* LONG, P */
                    v1=Pop(vm);
                    v1 <<= 32;
                    v1 |= l1;
                    printf("%lld ",v1);
                    break;
    case EX_LONG+17:n=Pop(vm);                            /* LONG, R */
                    if (n < 0) {
                      Reflect(vm);
                      return;
                      }
                    l1=Pop(vm);
                    v1=Pop(vm);
                    v1 = (v1<<32) | l1;
                    for (i=0; i<n; i++) v1 >>= 1;
                    h1 = (v1 >> 32);
                    l1 = (v1 & 0xffffffff);
                    Push(vm,h1); 
                    Push(vm,l1);
                    break;
    case EX_LONG+18:l1=Pop(vm);                           /* LONG, D */
                    v1=Pop(vm);
                    l2=Pop(vm);
                    v2=Pop(vm);
                    v1 = (v1<<32) | l1;
                    v2 = (v2<<32) | l2;
                    v2 -= v1;
                    h1 = (v2 >> 32);
                    l1 = (v2 & 0xffffffff);
                    Push(vm,h1); 
                    Push(vm,l1);
                    break;
    case EX_LONG+25:Pop_String(vm,Buffer);              /* LONG, Z */
                    v2 = atoll(Buffer);
                    h1 = (v2 >> 32);
                    l1 = (v2 & 0xffffffff);
                    Push(vm,h1); 
                    Push(vm,l1);
                    break;
    }
}
#endif

