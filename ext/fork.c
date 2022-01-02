/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef FORK
#include <time.h>
#include <unistd.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_FORK(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[19][vm->IPs[cip].NumOvers]=EX_FORK+19;   /* I */
}

void Unload_FORK(VM* vm) {
  Unload_Semantic(vm,19);
  }

void Do_FORK(VM* vm,int Cmd)
{
  int cip;
  pid_t pid;
  pid_t child;
  cip = vm->cip;
  switch (Cmd) {
    case EX_FORK+19:pid = getpid();                      /* FORK, T */
                    child = fork();
                    if (child == 0) {
                      Push(vm,pid);
                      Push(vm,1);
                      Reflect(vm);
                      return;
                      }
                    if (child == -1) {
                      Push(vm,-1);
                      return;
                      }
                    Push(vm,child);
                    Push(vm,0);
                    break;
    }
}
#endif

