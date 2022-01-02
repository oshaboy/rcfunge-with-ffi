/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef FING
#include <time.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

int Get_Semantic(VM* vm,int sem,int* pos) {
  int i;
  int cip;
  cip = vm->cip;
  i = vm->IPs[cip].NumOvers;
  while (i >= 0 && vm->IPs[cip].Overloads[sem][i] == 0) i--;
  *pos = i;
  if (i < 0) return(1);
    else return(vm->IPs[cip].Overloads[sem][i]);
  }

void Load_FING(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[23][vm->IPs[cip].NumOvers]=EX_FING+23;  /* X */
  vm->IPs[cip].Overloads[24][vm->IPs[cip].NumOvers]=EX_FING+24;  /* Y */
  vm->IPs[cip].Overloads[25][vm->IPs[cip].NumOvers]=EX_FING+25;  /* Z */
}

void Unload_FING(VM* vm) {
  Unload_Semantic(vm,23);
  Unload_Semantic(vm,24);
  Unload_Semantic(vm,25);
  }

void Do_FING(VM* vm,int Cmd)
{
  int i,s,d,o,o2;
  int pos,pos2;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_FING+23:s=Pop(vm);                           /* FING, X */
                    if (s >= 'A' && s <= 'Z') s -= 'A';
                    if (s < 0 || s > 25) {
                      Reflect(vm);
                      return;
                      }
                    d=Pop(vm);
                    if (d >= 'A' && d <= 'Z') d -= 'A';
                    if (d < 0 || d > 25) {
                      Reflect(vm);
                      return;
                      }
                    o = Get_Semantic(vm,s,&pos);
                    o2 = Get_Semantic(vm,d,&pos2);

Push_Semantic(vm,s,o2);
Push_Semantic(vm,d,o);
/*
                    if (pos < 1 || pos2 < 1) {
                      Reflect(vm);
                      return;
                      }
                    vm->IPs[cip].Overloads[s][pos] = o2;
                    vm->IPs[cip].Overloads[d][pos2] = o;
*/
                    break;
    case EX_FING+24:i=Pop(vm);                           /* FING, Y */
                    if (i>=0 && i<=25) {
                      if (Unload_Semantic(vm,i) < 0) {
                        Reflect(vm);
                        return;
                        }
                      return;
                      }
                    if (i>='A' && i <= 'Z') {
                      if (Unload_Semantic(vm,i-'A') < 0) {
                        Reflect(vm);
                        return;
                        }
                      return;
                      }
                    Reflect(vm);
                    break;
    case EX_FING+25:d=Pop(vm);                           /* FING, Z */
                    if (d >= 'A' && d <= 'Z') d -= 'A';
                    if (d < 0 || d > 25) {
                      Reflect(vm);
                      return;
                      }
                    s=Pop(vm);
                    if (s >= 'A' && s <= 'Z') s -= 'A';
                    if (s < 0 || s > 25) {
                      Reflect(vm);
                      return;
                      }
                    o = Get_Semantic(vm,s,&pos);
                    vm->IPs[cip].NumOvers++;
                    for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
                    vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=0xffff;
                    vm->IPs[cip].Overloads[d][vm->IPs[cip].NumOvers]=o;
                    break;
    }
}
#endif

