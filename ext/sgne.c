/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef SGNE
#include <time.h>
#include <signal.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_SGNE(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_SGNE+ 0;   /* A */
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_SGNE+ 8;   /* I */
  vm->IPs[cip].Overloads[11][vm->IPs[cip].NumOvers]=EX_SGNE+11;  /* L */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_SGNE+15;  /* P */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_SGNE+18;  /* S */
  vm->IPs[cip].Overloads[19][vm->IPs[cip].NumOvers]=EX_SGNE+19;  /* T */
}

void Unload_SGNE(VM* vm) {
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,8);
  Unload_Semantic(vm,11);
  Unload_Semantic(vm,15);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,19);
  }

void Do_SGNE(VM* vm,int Cmd) {
  int i;
  int cip;
  unsigned int u;
  struct sigaction action;
  VECTOR v;
  sigset_t set;
  cip = vm->cip;
  switch (Cmd) {
    case EX_SGNE+ 0:i=Pop(vm);                           /* SGNE, A */
                    i = alarm(i);
                    Push(vm,i);
                    break;
    case EX_SGNE+ 8:u=getpid();                          /* SGNE, I */
                    Push(vm,u);
                    break;
    case EX_SGNE+11:u = Pop(vm);                         /* SGNE, L */
                    u = sleep(u);
                    if (u != 0) {
                      Reflect(vm);
                      Push(vm,u);
                      }
                    break;
    case EX_SGNE+15:pause();                             /* SGNE, P */
                    break;
    case EX_SGNE+18:u = Pop(vm);                         /* SGNE, S */
                    u = raise(u);
                    if (u != 0) Reflect(vm);
                    break;
    case EX_SGNE+19:abort();                             /* SGNE, T */
                    break;
    }
}

#endif

