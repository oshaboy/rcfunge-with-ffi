/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef FOBJ
#include <time.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_FOBJ(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_FOBJ+ 3;   /* D */
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_FOBJ+ 8;   /* I */
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_FOBJ+12;  /* M */
  vm->IPs[cip].Overloads[13][vm->IPs[cip].NumOvers]=EX_FOBJ+13;  /* N */
}

void Unload_FOBJ(VM* vm) {
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,8);
  Unload_Semantic(vm,12);
  Unload_Semantic(vm,13);
  }

void Do_FOBJ(VM* vm,int Cmd)
{
  int i;
  int f;
  int m;
  int ref;
  int n;
  IP ip;
  int cip;
  char buffer[1000];
  INT* temp;
  VM  v;
  cip = vm->cip;
  switch (Cmd) {
    case EX_FOBJ+ 3:i=Pop(vm);                           /* FOBJ, D */
                    if (i>=vm->NumObjs) {
                      Reflect(vm);
                      return;
                      }
                    if (vm->objs[i] == NULL) {
                      Reflect(vm);
                      return;
                      }
                    Del_VM(vm->objs[i]);
                    free(vm->objs[i]);
                    vm->objs[i] = NULL;
                    break;
    case EX_FOBJ+ 8:Pop_String(vm,buffer);               /* FOBJ, I */
                    v = New_VM();
                    v.VmType = 'O';
                    v.Mode = 3;
                    Clear_Fs(&v);
                    v.cip=-1;
                    i = Load_File(&v,buffer,0,0,0);
                    if (i == 0) {
                      Reflect(vm);
                      Del_VM(&v);
                      return;
                      }
                    f=-1;
                    for (i=0; i<vm->NumObjs; i++)
                      if (vm->objs[i] == NULL) f = i;
                    if (f != -1) {
                      vm->objs[f] = (VM*)malloc(sizeof(VM));
                      *(vm->objs[f]) = v;
                      Push(vm,f);
                      return;
                      }
                    v.ProgName = (char*)malloc(strlen(buffer)+1);
                    strcpy(v.ProgName,buffer);
                    vm->NumObjs++;
                    if (vm->NumObjs == 1)
                      vm->objs = (VM**)malloc(sizeof(VM*));
                    else
                      vm->objs = (VM**)realloc(vm->objs,
                                               sizeof(VM*)*vm->NumObjs);
                    vm->objs[vm->NumObjs-1] = (VM*)malloc(sizeof(VM));
                    *(vm->objs[vm->NumObjs-1]) = v;
                    Push(vm,vm->NumObjs-1);
                    break;
    case EX_FOBJ+12:m=Pop(vm);                           /* FOBJ, M */
                    ref=Pop(vm);
                    n=Pop(vm);
                    if (n < 0) {
                      Reflect(vm);
                      return; 
                      }
                    if (ref>=vm->NumObjs) {
                      Reflect(vm);
                      return;
                      }
                    if (vm->objs[ref] == NULL) {
                      Reflect(vm);
                      return;
                      }
                    ip = New_IP(vm->objs[ref]);
                    ip.z = m;
                    Insert_IP(vm->objs[ref],ip);
                    vm->objs[ref]->cip = 0;
                    i = Get_Funge(vm->objs[ref],0,0,m);
                    if (i == 32) {
                      Reflect(vm);
                      Del_IP(&(vm->objs[ref]->IPs[0]));
                      free(vm->objs[ref]->IPs);
                      vm->objs[ref]->IPs = NULL;
                      vm->objs[ref]->NumIPs = 0;
                      return;
                      }
                    vm->objs[ref]->cip = 0;
                    if (n > 0) {
                      temp = (INT*)malloc(sizeof(INT)*n);
                      for (i=0; i<n; i++) temp[i] = Pop(vm);
                      for (i=n-1; i>=0; i--) Push(vm->objs[ref],temp[i]);
                      free(temp);
                      }
                    CycleSubVM(vm->objs[ref]);
                    vm->objs[ref]->cip = 0;
                    n = Pop(vm->objs[ref]);
                    if (n > 0) {
                      temp = (INT*)malloc(sizeof(INT)*n);
                      for (i=0; i<n; i++) temp[i] = Pop(vm->objs[ref]);
                      for (i=n-1; i>=0; i--) Push(vm,temp[i]);
                      free(temp);
                      }
                    Push(vm,n);
                    Del_IP(&(vm->objs[ref]->IPs[0]));
                    free(vm->objs[ref]->IPs);
                    vm->objs[ref]->IPs = NULL;
                    vm->objs[ref]->NumIPs = 0;
                    break;
    case EX_FOBJ+13:i=Pop(vm);                           /* FOBJ, N */
                    if (i>=vm->NumObjs) {
                      Reflect(vm);
                      return;
                      }
                    if (vm->objs[i] == NULL) {
                      Reflect(vm);
                      return;
                      }
                    Push_String(vm,vm->objs[i]->ProgName);
                    break;
    }
}
#endif

