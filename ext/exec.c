/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef EXEC
#include <time.h>
#include <string.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_EXEC(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_EXEC+00;    /* A */
  vm->IPs[cip].Overloads[1][vm->IPs[cip].NumOvers]=EX_EXEC+01;    /* B */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_EXEC+ 6;    /* G */
  vm->IPs[cip].Overloads[10][vm->IPs[cip].NumOvers]=EX_EXEC+10;   /* K */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_EXEC+17;   /* R */
  vm->IPs[cip].Overloads[23][vm->IPs[cip].NumOvers]=EX_EXEC+23;   /* X */
}

void Unload_EXEC(VM* vm) {
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,1);
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,10);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,23);
  }

void Do_EXEC(VM* vm,int Cmd)
{
  INT i,n,cmnd,x,y,z,ox,oy,oz,b,ix,iy,iz,odx,ody,odz;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_EXEC+ 0:n=Pop(vm);                           /* EXEC, A */
                    if (vm->Mode>2) z=Pop(vm); else z=0;
                    if (vm->Mode>1) y=Pop(vm); else y=0;
                    x=Pop(vm);
                    cmnd=Get_Funge(vm,x,y,z);
                    for (i=0;i<n;i++) Exec(vm,cmnd,0);
                    break;
    case EX_EXEC+ 1:n=Pop(vm);                           /* EXEC, B */
                    if (vm->Mode>2) z=Pop(vm); else z=0;
                    if (vm->Mode>1) y=Pop(vm); else y=0;
                    x=Pop(vm);
                    cmnd=Get_Funge(vm,x,y,z);
                    ox = vm->IPs[cip].x;
                    oy = vm->IPs[cip].y;
                    oz = vm->IPs[cip].z;
                    for (i=0;i<n;i++) {
                      vm->IPs[cip].x =ox;
                      vm->IPs[cip].y =oy;
                      vm->IPs[cip].z =oz;
                      Exec(vm,cmnd,0);
                      }
                    break;
    case EX_EXEC+ 6:if (vm->Mode>2) z=Pop(vm); else z=0;     /* EXEC, G */
                    if (vm->Mode>1) y=Pop(vm); else y=0;
                    x=Pop(vm);
                    vm->IPs[cip].x =x;
                    vm->IPs[cip].y =y;
                    vm->IPs[cip].z =z;
                    Sub_Delta(vm);
                    break;
    case EX_EXEC+10:n=Pop(vm);                           /* EXEC, K */
                    ox = vm->IPs[cip].x;
                    oy = vm->IPs[cip].y;
                    oz = vm->IPs[cip].z;
                    odx = vm->IPs[cip].DeltaX;
                    ody = vm->IPs[cip].DeltaY;
                    odz = vm->IPs[cip].DeltaZ;
                    Add_Delta(vm);
                    b=Get_Cell(vm);
                    while (b==' ' || b== ';') {
                      if (b==' ') {
                        Add_Delta(vm);
                        b=Get_Cell(vm);
                        }
                      if (b==';') {
                        Add_Delta(vm);
                        while (Get_Cell(vm) != ';') Add_Delta(vm);
                        Add_Delta(vm);
                        b=Get_Cell(vm);
                        }
                      }
                    ix = vm->IPs[cip].x;
                    iy = vm->IPs[cip].y;
                    iz = vm->IPs[cip].z;
                    vm->IPs[cip].x = ox;
                    vm->IPs[cip].y = oy;
                    vm->IPs[cip].z = oz;
                    for (i=0;i<n;i++) Exec(vm,b,0);
                    if (vm->IPs[cip].x==ox && vm->IPs[cip].y==oy && vm->IPs[cip].z==oz &&
                        vm->IPs[cip].DeltaX==odx && vm->IPs[cip].DeltaY==ody &&
                        vm->IPs[cip].DeltaZ==odz) {
                      vm->IPs[cip].x = ix;
                      vm->IPs[cip].y = iy;
                      vm->IPs[cip].z = iz;
                      }
                    break;
    case EX_EXEC+17:n=Pop(vm);                           /* EXEC, R */
                    ox = vm->IPs[cip].x;
                    oy = vm->IPs[cip].y;
                    oz = vm->IPs[cip].z;
                    odx = vm->IPs[cip].DeltaX;
                    ody = vm->IPs[cip].DeltaY;
                    odz = vm->IPs[cip].DeltaZ;
                    Add_Delta(vm);
                    b=Get_Cell(vm);
                    while (b==' ' || b== ';') {
                      if (b==' ') {
                        Add_Delta(vm);
                        b=Get_Cell(vm);
                        }
                      if (b==';') {
                        Add_Delta(vm);
                        while (Get_Cell(vm) != ';') Add_Delta(vm);
                        Add_Delta(vm);
                        b=Get_Cell(vm);
                        }
                      }
                    ix = vm->IPs[cip].x;
                    iy = vm->IPs[cip].y;
                    iz = vm->IPs[cip].z;
                    vm->IPs[cip].x = ox;
                    vm->IPs[cip].y = oy;
                    vm->IPs[cip].z = oz;
                    for (i=0;i<n;i++) {
                      Exec(vm,b,0);
                      vm->IPs[cip].x =ox;
                      vm->IPs[cip].y =oy;
                      vm->IPs[cip].z =oz;
                      }
                    if (vm->IPs[cip].x==ox && vm->IPs[cip].y==oy && vm->IPs[cip].z==oz &&
                        vm->IPs[cip].DeltaX==odx && vm->IPs[cip].DeltaY==ody &&
                        vm->IPs[cip].DeltaZ==odz) {
                      vm->IPs[cip].x = ix;
                      vm->IPs[cip].y = iy;
                      vm->IPs[cip].z = iz;
                      }
                    break;
    case EX_EXEC+23:n=Pop(vm);                           /* EXEC, X */
                    cmnd=Pop(vm);
                    for (i=0;i<n;i++) Exec(vm,cmnd,0);
                    break;

    }
}
#endif

