/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef IMTH
#include <time.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_IMTH(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_IMTH+ 0;   /* A */
  vm->IPs[cip].Overloads[1][vm->IPs[cip].NumOvers]=EX_IMTH+ 1;   /* B */
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_IMTH+ 2;   /* C */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_IMTH+ 3;   /* D */
  vm->IPs[cip].Overloads[4][vm->IPs[cip].NumOvers]=EX_IMTH+ 4;   /* E */
  vm->IPs[cip].Overloads[5][vm->IPs[cip].NumOvers]=EX_IMTH+ 5;   /* F */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_IMTH+ 6;   /* G */
  vm->IPs[cip].Overloads[7][vm->IPs[cip].NumOvers]=EX_IMTH+ 7;   /* H */
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_IMTH+ 8;   /* I */
  vm->IPs[cip].Overloads[11][vm->IPs[cip].NumOvers]=EX_IMTH+11;  /* L */
  vm->IPs[cip].Overloads[13][vm->IPs[cip].NumOvers]=EX_IMTH+13;  /* N */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_IMTH+17;  /* R */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_IMTH+18;  /* S */
  vm->IPs[cip].Overloads[19][vm->IPs[cip].NumOvers]=EX_IMTH+19;  /* T */
  vm->IPs[cip].Overloads[20][vm->IPs[cip].NumOvers]=EX_IMTH+20;  /* U */
  vm->IPs[cip].Overloads[23][vm->IPs[cip].NumOvers]=EX_IMTH+23;  /* X */
  vm->IPs[cip].Overloads[25][vm->IPs[cip].NumOvers]=EX_IMTH+25;  /* Z */
}

void Unload_IMTH(VM* vm) {
  Unload_Semantic(vm,2);
  }

void Do_IMTH(VM* vm,int Cmd)
{
  int i;
  int c;
  int n;
  int sum;
  int cip;
  UINT u;
  cip = vm->cip;
  switch (Cmd) {
    case EX_IMTH+00:c=Pop(vm);                           /* IMTH, A */
                    if (c == 0) {
                      Push(vm,c);
                      return;
                      }
                    if (c<0) {
                      Reflect(vm);
                      return;
                      }
                    sum = 0;
                    for (i=0; i<c; i++) sum += Pop(vm);
                    sum /= c;
                    Push(vm,sum);
                    break;
    case EX_IMTH+ 1:i=Pop(vm);                           /* IMTH, B */
                    Push(vm,( (i<0)?0-i:i));
                    break;
    case EX_IMTH+ 2:i=Pop(vm);                           /* IMTH, C */
                    Push(vm,i*100);
                    break;
    case EX_IMTH+ 3:i=Pop(vm);                           /* IMTH, D */
                    if (i>0) i--;
                      else if (i<0) i++;
                    Push(vm,i);
                    break;
    case EX_IMTH+ 4:i=Pop(vm);                           /* IMTH, E */
                    Push(vm,i*10000);
                    break;
    case EX_IMTH+ 5:c=Pop(vm);                           /* IMTH, F */
                    if (c == 0) {
                      Push(vm,c);
                      return;
                      }
                    if (c<0) {
                      Reflect(vm);
                      return;
                      }
                    sum = 1;
                    for (i=1; i<=c; i++) sum *= i;
                    Push(vm,sum);
                    break;
    case EX_IMTH+ 6:c=Pop(vm);                           /* IMTH, G */
                    if (c<0) Push(vm,-1);
                    else if (c>0) Push(vm,1);
                    else Push(vm,0);
                    break;
    case EX_IMTH+ 7:i=Pop(vm);                           /* IMTH, H */
                    Push(vm,i*1000);
                    break;
    case EX_IMTH+ 8:i=Pop(vm);                           /* IMTH, I */
                    if (i>0) i++;
                      else if (i<0) i--;
                    Push(vm,i);
                    break;
    case EX_IMTH+11:c=Pop(vm);                           /* IMTH, L */
                    i=Pop(vm);
                    i = (c>=0) ? i << c : i >> (0-c);
                    Push(vm,i);
                    break;
    case EX_IMTH+13:c=Pop(vm);                           /* IMTH, N */
                    if (c<=0) {
                      Reflect(vm);
                      return;
                      }
                    sum = Pop(vm);
                    for (i=1; i<c; i++) {
                      n = Pop(vm);
                      if (n < sum) sum = n;
                      }
                    Push(vm,sum);
                    break;
    case EX_IMTH+17:c=Pop(vm);                           /* IMTH, R */
                    i=Pop(vm);
                    i = (c>=0) ? i >> c : i << (0-c);
                    Push(vm,i);
                    break;
    case EX_IMTH+18:c=Pop(vm);                           /* IMTH, S */
                    if (c == 0) {
                      Push(vm,c);
                      return;
                      }
                    if (c<0) {
                      Reflect(vm);
                      return;
                      }
                    sum = 0;
                    for (i=0; i<c; i++) sum += Pop(vm);
                    Push(vm,sum);
                    break;
    case EX_IMTH+19:i=Pop(vm);                           /* IMTH, T */
                    Push(vm,i*10);
                    break;
    case EX_IMTH+20:u=Pop(vm);                           /* IMTH, U */
                    printf("%u",u);
                    break;
    case EX_IMTH+23:c=Pop(vm);                           /* IMTH, X */
                    if (c<=0) {
                      Reflect(vm);
                      return;
                      }
                    sum = Pop(vm);
                    for (i=1; i<c; i++) {
                      n = Pop(vm);
                      if (n > sum) sum = n;
                      }
                    Push(vm,sum);
                    break;
    case EX_IMTH+25:c=Pop(vm);                           /* IMTH, Z */
                    Push(vm,0-c);
                    break;
    }
}
#endif

