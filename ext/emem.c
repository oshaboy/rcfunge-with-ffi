/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef EMEM
#include <time.h>
#include <string.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_EMEM(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_EMEM+00;    /* A */
  vm->IPs[cip].Overloads[5][vm->IPs[cip].NumOvers]=EX_EMEM+05;    /* F */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_EMEM+ 6;    /* G */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_EMEM+15;   /* P */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_EMEM+17;   /* R */
}

void Unload_EMEM(VM* vm) {
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,5);
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,15);
  Unload_Semantic(vm,17);
  }

void Do_EMEM(VM* vm,int Cmd)
{
  INT i,slot,cnt,addr;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_EMEM+ 0:slot = -1;                            /* EMEM, A */
                    for (i=0; i<MAX_EMEM; i++)
                      if (vm->emems[i] == NULL) {
                        slot = i;
                        i = MAX_EMEM;
                        }
                    if (slot == -1) {
                      Reflect(vm);
                      return;
                      }
                    i = Pop(vm);
                    if (i <= 0) {
                      Reflect(vm);
                      return;
                      }
                    vm->emems[slot] = (byte*)malloc(i);
                    if (vm->emems[slot] == NULL) {
                      Reflect(vm);
                      return;
                      }
                    vm->ememSizes[slot] = i;
                    Push(vm,slot);
                    break;
    case EX_EMEM+ 5:slot = Pop(vm);                      /* EMEM, F */
                    if (slot <0 || slot >= MAX_EMEM || vm->emems[slot] == NULL) {
                      Reflect(vm);
                      return;
                      }
                    free(vm->emems[slot]);
                    vm->emems[slot] = NULL;
                    break;
    case EX_EMEM+ 6:addr = Pop(vm);                      /* EMEM, G */
                    cnt = Pop(vm);
                    slot = Pop(vm);
                    if (slot <0 || slot >= MAX_EMEM || vm->emems[slot] == NULL) {
                      Reflect(vm);
                      return;
                      }
                    if (cnt < 0) {
                      Reflect(vm);
                      return;
                      }
                    if (addr < 0 || addr+cnt >=vm->ememSizes[slot]) {
                      Reflect(vm);
                      return;
                      }
                    for (i=cnt-1; i>=0; i--)
                      Push(vm,vm->emems[slot][addr+i]);
                    break;
    case EX_EMEM+15:addr = Pop(vm);                      /* EMEM, P */
                    cnt = Pop(vm);
                    slot = Pop(vm);
                    if (slot <0 || slot >= MAX_EMEM || vm->emems[slot] == NULL) {
                      Reflect(vm);
                      return;
                      }
                    if (cnt < 0) {
                      Reflect(vm);
                      return;
                      }
                    if (addr < 0 || addr+cnt >=vm->ememSizes[slot]) {
                      Reflect(vm);
                      return;
                      }
                    for (i=0; i<cnt; i++)
                      vm->emems[slot][addr+i] = Pop(vm);
                    break;
    case EX_EMEM+17:cnt = Pop(vm);                       /* EMEM, R */
                    slot = Pop(vm);
                    if (slot <0 || slot >= MAX_EMEM || vm->emems[slot] == NULL) {
                      Reflect(vm);
                      return;
                      }
                    if (cnt <= 0) {
                      Reflect(vm);
                      return;
                      }
                    vm->emems[slot]=(byte*)realloc(vm->emems[slot],cnt);
                    if (vm->emems[slot] == NULL) {
                      Reflect(vm);
                      return;
                      }
                    vm->ememSizes[slot] = cnt;
                    break;
    } 
}
#endif

