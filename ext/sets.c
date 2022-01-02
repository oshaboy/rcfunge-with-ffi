/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef SETS
#include <time.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_SETS(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_SETS+00;   /* A */
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_SETS+02;   /* C */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_SETS+03;   /* D */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_SETS+ 6;   /* G */
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_SETS+ 8;   /* I */
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_SETS+12;  /* M */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_SETS+15;  /* P */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_SETS+17;  /* R */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_SETS+18;  /* S */
  vm->IPs[cip].Overloads[20][vm->IPs[cip].NumOvers]=EX_SETS+20;  /* U */
  vm->IPs[cip].Overloads[22][vm->IPs[cip].NumOvers]=EX_SETS+22;  /* W */
  vm->IPs[cip].Overloads[23][vm->IPs[cip].NumOvers]=EX_SETS+23;  /* X */
  vm->IPs[cip].Overloads[25][vm->IPs[cip].NumOvers]=EX_SETS+25;  /* Z */
}

void Unload_SETS(VM* vm) {
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,8);
  Unload_Semantic(vm,12);
  Unload_Semantic(vm,15);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,20);
  Unload_Semantic(vm,22);
  Unload_Semantic(vm,23);
  Unload_Semantic(vm,25);
  }

INT* Pop_Set(VM* vm,INT* count) {
  int  i;
  INT* set;
  int cip;
  cip = vm->cip;
  *count = Pop(vm);
  if (*count > vm->IPs[cip].StackPtr) {
    Push(vm,*count);
    *count = -1;
    return NULL;
    }
  set = (INT*)malloc(sizeof(INT)*(*count));
  for (i=0; i<*count; i++) set[i] = Pop(vm);
  return set;
  }

void Push_Set(VM* vm,INT* set,INT count) {
  int i;
  int cip;
  cip = vm->cip;
  for (i=0; i<count; i++) Push(vm,set[i]);
  Push(vm,count);
  }

void Do_SETS(VM* vm,int Cmd)
{
  int i,j,v,x,y,z,dx,dy,dz,flag;
  int count,count2,count3;
  INT* set;
  INT* set2;
  INT* set3;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_SETS+ 0:v = Pop(vm);                       /* SETS, A */
                    set = Pop_Set(vm,&count);
                    if (count < 0) {
                      Reflect(vm);
                      Push(vm,v);
                      return;
                      }
                    for (i=0; i<count; i++) {
                      if (set[i] == v) {
                        Push_Set(vm,set,count);
                        if (set != NULL) free(set);
                        return;
                        }
                      }
                    count++;
                    if (count == 1) set=(INT*)malloc(sizeof(INT));
                      else set=(INT*)realloc(set,sizeof(INT)*count);
                    set[count-1] = v;
                    Push_Set(vm,set,count);
                    if (set != NULL) free(set);
                    break;
    case EX_SETS+ 2:set = Pop_Set(vm,&count);          /* SETS, C */
                    if (count < 0) {
                      Reflect(vm);
                      return;
                      }
                    Push_Set(vm,set,count);
                    Push(vm,count);
                    if (set != NULL) free(set);
                    break;
    case EX_SETS+ 3:set = Pop_Set(vm,&count);          /* SETS, D */
                    if (count < 0) {
                      Reflect(vm);
                      return;
                      }
                    Push_Set(vm,set,count);
                    Push_Set(vm,set,count);
                    if (set != NULL) free(set);
                    break;
    case EX_SETS+ 6:if (vm->Mode > 2) z=Pop(vm);           /* SETS, G */
                      else z=0;
                    if (vm->Mode > 1) y=Pop(vm);
                      else y=0;
                    x=Pop(vm);
                    if (vm->Mode > 2) dz=Pop(vm);
                      else dz=0;
                    if (vm->Mode > 1) dy=Pop(vm);
                      else dy=0;
                    dx=Pop(vm);
                    count = Get_Funge(vm,x,y,z);
                    if (count == 0) {
                      Push(vm,0);
                      return;
                      }
                    set = (INT*)malloc(sizeof(INT)*count);
                    for (i=0; i<count; i++) {
                      x += dx;
                      y += dy;
                      z += dz;
                      set[i] = Get_Funge(vm,x,y,z);
                      }
                    Push_Set(vm,set,count);
                    if (set != NULL) free(set);
                    break;
    case EX_SETS+ 8:set = Pop_Set(vm,&count);          /* SETS, I */
                    if (count < 0) {
                      Reflect(vm);
                      return;
                      }
                    set2 = Pop_Set(vm,&count2);
                    if (count2 < 0) {
                      Reflect(vm);
                      Push_Set(vm,set,count);
                      if (set != NULL) free(set);
                      return;
                      }
                    set3 = NULL;
                    count3 = 0;
                    for (i=0; i<count; i++) {
                      flag = 0;
                      for (j=0; j<count2; j++)
                        if (set[i] == set2[j]) flag = 1;
                      if (flag == 1) {
                        count3++;
                        if (count3==1) set3=(INT*)malloc(sizeof(INT));
                          else set3=(INT*)realloc(set3,sizeof(INT)*count3);
                        set3[count3-1] = set[i];
                        }
                      }
                    Push_Set(vm,set2,count2);
                    Push_Set(vm,set,count);
                    Push_Set(vm,set3,count3);
                    if (set != NULL) free(set);
                    if (set2 != NULL) free(set2);
                    if (set3 != NULL) free(set3);
                    break;
    case EX_SETS+12:v = Pop(vm);                       /* SETS, M */
                    set = Pop_Set(vm,&count);
                    if (count < 0) {
                      Reflect(vm);
                      Push(vm,v);
                      return;
                      }
                    Push_Set(vm,set,count);
                    for (i=0; i<count; i++) {
                      if (v == set[i]) {
                        Push(vm,1);
                        if (set != NULL) free(set);
                        return;
                        }
                      }
                    Push(vm,0);
                    if (set != NULL) free(set);
                    break;
    case EX_SETS+15:if (vm->IPs[cip].StackPtr == 0) {       /* SETS, P */
                      Reflect(vm);
                      return;
                      }
                    set = Pop_Set(vm,&count);
                    if (count < 0) {
                      Reflect(vm);
                      return;
                      }
                    printf("(");
                    for (i=0; i<count; i++) {
                      if (i>0) printf(" ");
                      printf("%d",set[i]);
                      }
                    printf(")");
                    Push_Set(vm,set,count);
                    if (set != NULL) free(set);
                    break;
    case EX_SETS+17:v = Pop(vm);                       /* SETS, R */
                    set = Pop_Set(vm,&count);
                    if (count < 0) {
                      Reflect(vm);
                      Push(vm,v);
                      return;
                      }
                    flag = -1;
                    for (i=0; i<count; i++)
                      if (set[i] == v) flag = i;
                    if (flag != -1) {
                      for (i=flag; i<count-1; i++)
                        set[i] = set[i+1];
                      count--;
                      }
                    Push_Set(vm,set,count);
                    if (set != NULL) free(set);
                    break;
    case EX_SETS+18:set2 = Pop_Set(vm,&count2);          /* SETS, S */
                    if (count < 0) {
                      Reflect(vm);
                      return;
                      }
                    set = Pop_Set(vm,&count);
                    if (count < 0) {
                      Reflect(vm);
                      Push_Set(vm,set2,count);
                      if (set != NULL) free(set);
                      return;
                      }
                    for (i=0; i<count2; i++) {
                      flag = -1;
                      for (j=0; j<count; j++)
                        if (set[j] == set2[i]) flag = j;
                      if (flag != -1) {
                        for (j=flag; j<count-1; j++)
                          set[j] = set[j+1];
                        count--;
                        }
                      }
                    Push_Set(vm,set,count);
                    if (set != NULL) free(set);
                    break;
    case EX_SETS+20:set = Pop_Set(vm,&count);          /* SETS, U */
                    if (count < 0) {
                      Reflect(vm);
                      return;
                      }
                    set2 = Pop_Set(vm,&count2);
                    if (count2 < 0) {
                      Reflect(vm);
                      Push_Set(vm,set,count);
                      if (set != NULL) free(set);
                      return;
                      }
                    set3 = NULL;
                    count3 = 0;
                    for (i=0; i<count; i++) {
                      count3++;
                      if (count3==1) set3=(INT*)malloc(sizeof(INT));
                        else set3=(INT*)realloc(set3,sizeof(INT)*count3);
                      set3[count3-1] = set[i];
                      }
                    for (i=0; i<count2; i++) {
                      flag = 0;
                      for (j=0; j<count; j++)
                        if (set2[i] == set[j]) flag = 1;
                      if (flag != 1) {
                        count3++;
                        if (count3==1) set3=(INT*)malloc(sizeof(INT));
                          else set3=(INT*)realloc(set3,sizeof(INT)*count3);
                        set3[count3-1] = set2[i];
                        }
                      }
                    Push_Set(vm,set2,count2);
                    Push_Set(vm,set,count);
                    Push_Set(vm,set3,count3);
                    if (set != NULL) free(set);
                    if (set2 != NULL) free(set2);
                    if (set3 != NULL) free(set3);
                    break;
    case EX_SETS+22:if (vm->Mode > 2) z=Pop(vm);           /* SETS, W */
                      else z=0;
                    if (vm->Mode > 1) y=Pop(vm);
                      else y=0;
                    x=Pop(vm);
                    if (vm->Mode > 2) dz=Pop(vm);
                      else dz=0;
                    if (vm->Mode > 1) dy=Pop(vm);
                      else dy=0;
                    dx=Pop(vm);
                    set = Pop_Set(vm,&count);
                    if (count < 0) {
                      Reflect(vm);
                      return;
                      }
                    Put_Funge(vm,x,y,z,count);
                    for (i=0; i<count; i++) {
                      x += dx;
                      y += dy;
                      z += dz;
                      Put_Funge(vm,x,y,z,set[i]);
                      }
                    if (set != NULL) free(set);
                    break;
    case EX_SETS+23:set = Pop_Set(vm,&count);          /* SETS, X */
                    if (count < 0) {
                      Reflect(vm);
                      return;
                      }
                    set2 = Pop_Set(vm,&count2);
                    if (count2 < 0) {
                      Reflect(vm);
                      Push_Set(vm,set,count);
                      if (set != NULL) free(set);
                      return;
                      }
                    Push_Set(vm,set,count);
                    Push_Set(vm,set2,count);
                    if (set != NULL) free(set);
                    if (set2 != NULL) free(set2);
                    break;
    case EX_SETS+25:set = Pop_Set(vm,&count);          /* SETS, Z */
                    if (count < 0) {
                      Reflect(vm);
                      return;
                      }
                    if (set != NULL) free(set);
                    break;
    }
}
#endif

