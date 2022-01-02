/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef MACR
#include <time.h>
#include "funge.h"

void Load_MACR(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  for (i=0; i<26; i++) 
    vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=EX_MACR+i;
}

void Unload_MACR(VM* vm) {
  int i;
  for (i=0;i<26; i++)
    Unload_Semantic(vm,i);
  }

void Do_MACR(VM* vm,int Cmd)
{
  int flag;
  int c,i;
  int mx,my,mz;
  int dx,dy,dz;
  int rx,ry;
  int cip;
  cip = vm->cip;
  dx = 1;
  dy = 0;
  dz = 0;
    if (Cmd >= EX_MACR && Cmd <=EX_MACR+24) {             /* MACR, A-Y */
      mx = vm->IPs[cip].mx;
      my = vm->IPs[cip].my+(Cmd - EX_MACR);
      mz = vm->IPs[cip].mz;
      flag = 0;
      while (flag == 0) {
        c = Get_Funge(vm,mx,my,mz);
        if (c == 'B') Sub_Delta(vm);
        else if (c == 'G') {
          mx += dx;
          my += dy;
          mz += dz;
          Push(vm,Get_Funge(vm,mx,my,mz));
          }
        else if (c == 'F') Add_Delta(vm);
        else if (c == 'R') {
          rx = -dy;
          ry = dx;
          dx = rx;
          dy = ry;
          }
        else if (c == 'L') {
          rx = dy;
          ry = -dx;
          dx = rx;
          dy = ry;
          }
        else if (c == 'N') {
          dx = 0;
          dy = -1;
          dz = 0;
          }
        else if (c == 'S') {
          dx = 0;
          dy = 1;
          dz = 0;
          }
        else if (c == 'E') {
          dx = 1;
          dy = 0;
          dz = 0;
          }
        else if (c == 'W') {
          dx = -1;
          dy = 0;
          dz = 0;
          }
        else if (c == 'T') {
          mx += dx;
          my += dy;
          mz += dz;
          }
        else if (c == 'J') {
          i = Pop(vm);
          mx += dx*i;
          my += dy*i;
          mz += dz*i;
          }
        else if (c == 'I') {
          if (Pop(vm) == 0) {
            dx = 0;
            dy = 1;
            dz = 0;
            } else {
            dx = 0;
            dy = -1;
            dz = 0;
            }
          }
        else if (c == 'A') {
          if (Pop(vm) == 0) {
            dx = 1;
            dy = 0;
            dz = 0;
            } else {
            dx = -1;
            dy = 0;
            dz = 0;
            }
          }
        else if (c == '@') flag = 1;
        else if (c < 32) flag = 1;
        else if (c > 127) flag = 1;
        else {
          Exec(vm,c,0);
          }
        mx += dx;
        my += dy;
        mz += dz;
        }
      }
    if (Cmd == EX_MACR+25) {                              /* MACR, Z */
      if (vm->Mode>2) mz=Pop(vm); else mz=0;
      if (vm->Mode>1) my=Pop(vm); else my=0;
      mx=Pop(vm);
      vm->IPs[cip].mx = mx;
      vm->IPs[cip].my = my;
      vm->IPs[cip].mz = mz;
      }
}
#endif

