/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef STCK
#include <time.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_STCK(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip; 
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[1][vm->IPs[cip].NumOvers]=EX_STCK+01;   /* B */
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_STCK+02;   /* C */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_STCK+03;   /* D */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_STCK+06;   /* G */
  vm->IPs[cip].Overloads[10][vm->IPs[cip].NumOvers]=EX_STCK+10;  /* K */
  vm->IPs[cip].Overloads[13][vm->IPs[cip].NumOvers]=EX_STCK+13;  /* N */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_STCK+15;  /* P */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_STCK+17;  /* R */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_STCK+18;  /* S */
  vm->IPs[cip].Overloads[19][vm->IPs[cip].NumOvers]=EX_STCK+19;  /* T */
  vm->IPs[cip].Overloads[20][vm->IPs[cip].NumOvers]=EX_STCK+20;  /* U */
  vm->IPs[cip].Overloads[22][vm->IPs[cip].NumOvers]=EX_STCK+22;  /* W */
  vm->IPs[cip].Overloads[25][vm->IPs[cip].NumOvers]=EX_STCK+25;  /* Z */
}

void Unload_STCK(VM* vm) {
  Unload_Semantic(vm,1);
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,10);
  Unload_Semantic(vm,13);
  Unload_Semantic(vm,15);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,19);
  Unload_Semantic(vm,20);
  Unload_Semantic(vm,22);
  Unload_Semantic(vm,25);
  }

void Do_STCK(VM* vm,int Cmd)
{
  INT n,v,i,s,e,a,b,c,x,y,z,dx,dy,dz;
  INT *Temp;
  int cip; 
  cip = vm->cip;
  Temp = NULL;
  switch (Cmd) {
    case EX_STCK+01:n=Pop(vm);                           /* STCK, B */
                    v=Pop(vm);
                    if (n == 0) {
                      Push(vm,v);
                      return;
                      }
                    if (n < 0) { 
                      Push(vm,v);
                      while (n < 0) {
                        Push(vm,0);
                        n++;
                        }
                      return;
                      }
                    if (n>vm->IPs[cip].StackPtr) {
                      Reflect(vm);
                      return;
                      }
                    Temp=(INT*)malloc(sizeof(INT)*n);
                    for (i=0; i<n; i++) Temp[i] = Pop(vm);
                    Push(vm,v);
                    for (i=n-1; i>=0; i--) Push(vm,Temp[i]);
                    if (Temp != NULL) free(Temp);
                    break;
    case EX_STCK+ 2:n=vm->IPs[cip].StackPtr;                  /* STCK, C */
                    Push(vm,n);
                    break;
    case EX_STCK+03:n=Pop(vm);                           /* STCK, D */
                    Temp=(INT*)malloc(sizeof(INT)*n);
                    for (i=0; i<n; i++) Temp[i] = Pop(vm);
                    for (i=n-1; i>=0; i--) {
                      Push(vm,Temp[i]);
                      Push(vm,Temp[i]);
                      }
                    if (Temp != NULL) free(Temp);
                    break;
    case EX_STCK+ 6:if (vm->Mode > 2) z=Pop(vm);             /* STCK, G */
                      else z = 0;
                    if (vm->Mode > 1) y=Pop(vm);
                      else y = 0;
                    x=Pop(vm);
                    if (vm->Mode > 2) dz=Pop(vm);
                      else dz = 0;
                    if (vm->Mode > 1) dy=Pop(vm);
                      else dy = 0;
                    dx=Pop(vm);
                    n=Pop(vm);
                    if (n < 0) {
                      Reflect(vm);
                      }
                    x += (dx * n);
                    y += (dy * n);
                    z += (dz * n);
                    for (i=0; i<n; i++) {
                      x-=dx;
                      y-=dy;
                      z-=dz;
                      Push(vm,Get_Funge(vm,x,y,z));
                      }
                    break;
    case EX_STCK+10:e=Pop(vm)+1;                         /* STCK, K */
                    s=Pop(vm)+1;
                    if (e<=0 || s<=0) {
                      Reflect(vm);
                      return;
                      }
                    if (e>s) {
                      Reflect(vm);
                      return;
                      }
                    Temp=(INT*)malloc(sizeof(INT)*s);
                    for (i=0; i<s; i++) Temp[i] = Pop(vm);
                    for (i=e-2; i>=0; i--) Push(vm,Temp[i]);
                    for (i=s-1; i>=e-1; i--) Push(vm,Temp[i]);
                    if (Temp != NULL) free(Temp);
                    break;
    case EX_STCK+13:n=Pop(vm);                           /* STCK, N */
                    if (n < 0) {
                      Reflect(vm);
                      return;
                      }
                    Temp=(INT*)malloc(sizeof(INT)*n);
                    for (i=0; i<n; i++) Temp[i] = Pop(vm);
                    for (i=0; i<n; i++) Push(vm,Temp[i]);
                    if (Temp != NULL) free(Temp);
                    break;
    case EX_STCK+17:n=vm->IPs[cip].StackPtr;                  /* STCK, R */
                    Temp=(INT*)malloc(sizeof(INT)*n);
                    for (i=0; i<n; i++) Temp[i] = Pop(vm);
                    for (i=0; i<n; i++) Push(vm,Temp[i]);
                    if (Temp != NULL) free(Temp);
                    break;
    case EX_STCK+18:a=Pop(vm);                           /* STCK, S */
                    b=Pop(vm);
                    Push(vm,b);
                    Push(vm,b);
                    Push(vm,a);
                    break;
    case EX_STCK+19:a=Pop(vm);                           /* STCK, T */
                    b=Pop(vm);
                    c=Pop(vm);
                    Push(vm,b);
                    Push(vm,c);
                    Push(vm,a);
                    break;
    case EX_STCK+20:v=Pop(vm);                           /* STCK, U */
                    a=-1;
                    b=v+1;
                    while (v != b && vm->IPs[cip].StackPtr>0) {
                      b=Pop(vm);
                      a++;
                      }
                    if (vm->IPs[cip].StackPtr == 0) Reflect(vm);
                    else {
                      Push(vm,b);
                      Push(vm,a);
                      }
                    break;
    case EX_STCK+15:n=vm->IPs[cip].StackPtr;                  /* STCK, P */
                    Temp=(INT*)malloc(sizeof(INT)*n);
                    for (i=0; i<n; i++) Temp[i] = Pop(vm);
                    printf("(");
                    for (i=n-1; i>=0; i--) {
                      printf("%d ",Temp[i]);
                      Push(vm,Temp[i]);
                      }
                    printf(")\n");
                    if (Temp != NULL) free(Temp);
                    break;
    case EX_STCK+22:if (vm->Mode > 2) z=Pop(vm);             /* STCK, V */
                      else z = 0;
                    if (vm->Mode > 1) y=Pop(vm);
                      else y = 0;
                    x=Pop(vm);
                    if (vm->Mode > 2) dz=Pop(vm);
                      else dz = 0;
                    if (vm->Mode > 1) dy=Pop(vm);
                      else dy = 0;
                    dx=Pop(vm);
                    n=Pop(vm);
                    if (n < 0) {
                      Reflect(vm);
                      }
                    for (i=0; i<n; i++) {
                      a=Pop(vm);
                      Put_Funge(vm,x,y,z,a);
                      x+=dx;
                      y+=dy;
                      z+=dz;
                      }
                    break;
    case EX_STCK+25:i = 0;                                /* STCK, Z */
                    while ((a=Pop(vm)) != 0) {
                      i++;
                      if (i==1) Temp=(INT*)malloc(sizeof(INT));
                        else Temp=(INT*)realloc(Temp,sizeof(INT)*i);
                      Temp[i-1] = a;
                      }
                    Push(vm,0);
                    for (a=0; a<i; a++) Push(vm,Temp[a]);
                    if (Temp != NULL) free(Temp);
                    break;
    }
}
#endif

