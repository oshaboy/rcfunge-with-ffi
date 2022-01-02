/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef ICAL
#include <time.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_ICAL(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_ICAL+ 0;   /* A */
  vm->IPs[cip].Overloads[5][vm->IPs[cip].NumOvers]=EX_ICAL+ 5;   /* F */
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_ICAL+ 8;   /* I */
  vm->IPs[cip].Overloads[13][vm->IPs[cip].NumOvers]=EX_ICAL+13;  /* N */
  vm->IPs[cip].Overloads[14][vm->IPs[cip].NumOvers]=EX_ICAL+14;  /* O */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_ICAL+17;  /* R */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_ICAL+18;  /* S */
  vm->IPs[cip].Overloads[23][vm->IPs[cip].NumOvers]=EX_ICAL+23;  /* X */
}

void Unload_ICAL(VM* vm) {
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,5);
  Unload_Semantic(vm,8);
  Unload_Semantic(vm,13);
  Unload_Semantic(vm,14);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,23);
  }

void Do_ICAL(VM* vm,int Cmd)
{
  int  i;
  UINT v;
  UINT n;
  UINT a,b;
  VECTOR vec;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_ICAL+ 0:v=Pop(vm);                           /* ICAL, A */
                    if (n > 0xffff)
                      n=(v & 1) ? (v >> 1) | 0x80000000 : v >> 1;
                    else 
                      n=(v & 1) ? (v >> 1) | 0x8000 : v >> 1;
                    v &= n;
                    Push(vm,v);
                    break;
    case EX_ICAL+ 5:a=Pop(vm);                           /* ICAL, F */
                    if (a<0) {
                      Reflect(vm);
                      return;
                      }
                    if (a == 0) return;
                    if (a > vm->IPs[cip].NextCount) {
                      vm->IPs[cip].NextCount = 0;
                      return;
                      }
                    vm->IPs[cip].NextCount -= a;
                    break;
    case EX_ICAL+ 8:b=Pop(vm);                           /* ICAL, I */
                    a=Pop(vm);
                    a &= 0xffff;
                    b &= 0xffff;
                    v = 0;
                    n = 1;
                    for (i=0; i<16; i++) {
                      if (b & 1) v |= n;
                      n <<= 1;
                      if (a & 1) v |= n;
                      n <<= 1;
                      a >>= 1;
                      b >>= 1;
                      }
                    Push(vm,v);
                    break;
    case EX_ICAL+13:vec = Pop_Vector(vm);                /* ICAL, N */
                    if (vm->IPs[cip].NextCount == 80) {
                      Reflect(vm);
                      return;
                      }
                    vm->IPs[cip].NextStack[vm->IPs[cip].NextCount].x =
                        vm->IPs[cip].x;
                    vm->IPs[cip].NextStack[vm->IPs[cip].NextCount].y =
                        vm->IPs[cip].y;
                    vm->IPs[cip].NextStack[vm->IPs[cip].NextCount].z =
                        vm->IPs[cip].z;
                    vm->IPs[cip].NextCount++;
                    vm->IPs[cip].x = vec.x;
                    vm->IPs[cip].y = vec.y;
                    vm->IPs[cip].z = vec.z;
                    Sub_Delta(vm);
                    break;
    case EX_ICAL+14:v=Pop(vm);                           /* ICAL, O */
                    if (n > 0xffff)
                      n=(v & 1) ? (v >> 1) | 0x80000000 : v >> 1;
                    else 
                      n=(v & 1) ? (v >> 1) | 0x8000 : v >> 1;
                    v |= n;
                    Push(vm,v);
                    break;
    case EX_ICAL+17:a=Pop(vm);                           /* ICAL, R */
                    if (a<0) {
                      Reflect(vm);
                      return;
                      }
                    if (a == 0) return;
                    if (a > vm->IPs[cip].NextCount) {
                      vm->IPs[cip].NextCount = 0;
                      return;
                      }
                    vm->IPs[cip].NextCount -= a;
                    vm->IPs[cip].x =
                        vm->IPs[cip].NextStack[vm->IPs[cip].NextCount].x;
                    vm->IPs[cip].y =
                        vm->IPs[cip].NextStack[vm->IPs[cip].NextCount].y;
                    vm->IPs[cip].z =
                        vm->IPs[cip].NextStack[vm->IPs[cip].NextCount].z;
                    break;
    case EX_ICAL+18:b=Pop(vm);                           /* ICAL, S */
                    a=Pop(vm);
                    v = 0;
                    n = 1;
                    for (i=0; i<32; i++) {
                      if (b & 1) {
                        if (a & 1) v |= n;
                        n <<= 1;
                        }
                      a >>= 1;
                      b >>= 1;
                      }
                    Push(vm,v);
                    break;
    case EX_ICAL+23:v=Pop(vm);                           /* ICAL, X */
                    if (n > 0xffff)
                      n=(v & 1) ? (v >> 1) | 0x80000000 : v >> 1;
                    else 
                      n=(v & 1) ? (v >> 1) | 0x8000 : v >> 1;
                    v ^= n;
                    Push(vm,v);
                    break;
    }
}
#endif

