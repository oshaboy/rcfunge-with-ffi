/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef MVRS
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_MVRS(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[1][vm->IPs[cip].NumOvers]=EX_MVRS+ 1;   /* B */
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_MVRS+ 2;   /* C */
  vm->IPs[cip].Overloads[5][vm->IPs[cip].NumOvers]=EX_MVRS+ 5;   /* F */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_MVRS+ 6;   /* G */
  vm->IPs[cip].Overloads[9][vm->IPs[cip].NumOvers]=EX_MVRS+ 9;   /* J */
  vm->IPs[cip].Overloads[13][vm->IPs[cip].NumOvers]=EX_MVRS+13;  /* N */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_MVRS+15;  /* P */
}

void Unload_MVRS(VM* vm) {
  Unload_Semantic(vm,1);
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,5);
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,9);
  Unload_Semantic(vm,13);
  Unload_Semantic(vm,15);
  }

int MVRS_find(char* buffer) {
  int i;
  for (i=0; i<NumVMs; i++)
    if (strcmp(buffer,vms[i].ProgName) == 0) return i;
  return -1;
  }

void Do_MVRS(VM* vm,int Cmd)
{
  int cip;
  int flags;
  int dim;
  int lng;
  int i;
  int dx,dy,dz;
  int sx,sy,sz;
  int cx,cy,cz;
  int x,y,z;
  int dvm;
  IP  ip;
  char buffer[1000];
  cip = vm->cip;
  switch (Cmd) {
    case EX_MVRS+ 1:dim = Pop(vm);                            /* MVRS, B */
                    lng = Pop(vm);
                    flags = Pop(vm);
                    Pop_String(vm,buffer);
                    i=open(buffer,O_RDONLY);
                    if (i == -1) {
                      Reflect(vm);
                      return;
                      }
                    close(i);
                    NumVMs++;
                    vms = (VM*)realloc(vms,sizeof(VM)*NumVMs);
                    if (vms == NULL) {
                      printf("Could not allocate VM memory. Aborting.\n");
                      exit(-1);
                      }
                    switch(dim) {
                      case 1:vms[NumVMs-1].Mode = 1; break;
                      case 2:vms[NumVMs-1].Mode = 2; break;
                      case 3:vms[NumVMs-1].Mode = 3; break;
                      default:vms[NumVMs-1].Mode = vm->Mode; break;
                      }
                    switch(lng) {
                      case 1:vms[NumVMs-1].Language = 93; break;
                      case 2:vms[NumVMs-1].Language = 98; break;
                      case 3:vms[NumVMs-1].Language = 108; break;
                      default:vms[NumVMs-1].Language = vm->Language; break;
                      }
                    if (flags & 512) vms[NumVMs-1].ShowSummary = 0;
                    if (flags & 1024) vms[NumVMs-1].Debugger = 1;
                    if (flags & 2048) vms[NumVMs-1].TraceMode = 1;
                    if (flags & 4096) vms[NumVMs-1].ModeY=1;
                    vms[NumVMs-1] = New_VM();
                    Clear_Fs(&(vms[NumVMs-1]));
                    Insert_IP(&(vms[NumVMs-1]),New_IP(&(vms[NumVMs-1])));
                    Load_File(&(vms[NumVMs-1]),buffer,0,0,0);
                    vms[NumVMs-1].ProgName = (char*)malloc(strlen(buffer)+1);
                    if (vms[NumVMs-1].ProgName == NULL) {
                      printf("Could not allocate memory for vms[0].ProgName\n");
                      exit(-1);
                      }
                    strcpy(vms[NumVMs-1].ProgName,buffer);
                    break;
    case EX_MVRS+ 2:Push(vm,NumVMs); break;                   /* MVRS, C */
    case EX_MVRS+ 5:if (vm->Mode>2) cz=Pop(vm); else cz=1;    /* MVRS, F */
                    if (vm->Mode>1) cy=Pop(vm); else cy=1;
                    cx=Pop(vm);
                    sz=Pop(vm);
                    sy=Pop(vm);
                    sx=Pop(vm);
                    if (vm->Mode>2) dz=Pop(vm); else dz=0;
                    if (vm->Mode>1) dy=Pop(vm); else dy=0;
                    dx=Pop(vm);
                    Pop_String(vm,buffer);
                    dvm=MVRS_find(buffer);
                    if (dvm < 0) {
                      Reflect(vm);
                      return;
                      }
                    if (vms[dvm].Mode == 1) {
                      sy=0;
                      sz=0;
                      cz=1;
                      cy=1;
                      }
                    if (vms[dvm].Mode == 2) {
                      sz=0;
                      cz=1;
                      }
                    for (z=0; z<cz; z++)
                      for (y=0; y<cy; y++)
                        for (x=0; x<cx; x++) {
                          Put_Funge(vm,x+dx,y+dy,z+dz,
                            Get_Funge(&(vms[dvm]),x+sx,y+sy,z+sz));
                          }
                    break;
    case EX_MVRS+ 6:dz=Pop(vm);                               /* MVRS, G */
                    dy=Pop(vm);
                    dx=Pop(vm);
                    z=Pop(vm);
                    y=Pop(vm);
                    x=Pop(vm);
                    Pop_String(vm,buffer);
                    dvm=MVRS_find(buffer);
                    if (dvm < 0) {
                      Reflect(vm);
                      return;
                      }
                    if (vms[dvm].Mode == 1) {
                      dy=0;
                      dz=0;
                      z=0;
                      y=0;
                      }
                    if (vms[dvm].Mode == 2) {
                      dz=0;
                      cz=0;
                      }
                    ip = Dup_IP(vm->IPs[cip]);
                    ip.DeltaX = dx;
                    ip.DeltaY = dy;
                    ip.DeltaZ = dz;
                    ip.x = x;
                    ip.y = y;
                    ip.z = z;
                    Insert_IP(&(vms[dvm]),ip);
                    vm->IPs[vm->cip].uid = -1;
                    break;
    case EX_MVRS+ 9:Pop_String(vm,buffer);                    /* MVRS, J */
                    dvm=MVRS_find(buffer);
                    if (dvm < 0) {
                      Reflect(vm);
                      return;
                      }
                    if (vms[dvm].Mode == 1) {
                      vm->IPs[cip].DeltaY = 0;
                      vm->IPs[cip].DeltaZ = 0;
                      vm->IPs[cip].y = 0;
                      vm->IPs[cip].z = 0;
                      }
                    if (vms[dvm].Mode == 2) {
                      vm->IPs[cip].DeltaZ = 0;
                      vm->IPs[cip].z = 0;
                      }
                    ip = Dup_IP(vm->IPs[cip]);
                    Insert_IP(&(vms[dvm]),ip);
                    vm->IPs[vm->cip].uid = -1;
                    break;
    case EX_MVRS+13:Push_String(vm,vm->ProgName); break;      /* MVRS, N */
    case EX_MVRS+15:if (vm->Mode>2) cz=Pop(vm); else cz=1;    /* MVRS, P */
                    if (vm->Mode>1) cy=Pop(vm); else cy=1;
                    cx=Pop(vm);
                    if (vm->Mode>2) sz=Pop(vm); else sz=0;
                    if (vm->Mode>1) sy=Pop(vm); else sy=0;
                    sx=Pop(vm);
                    dz=Pop(vm);
                    dy=Pop(vm);
                    dx=Pop(vm);
                    Pop_String(vm,buffer);
                    dvm=MVRS_find(buffer);
                    if (dvm < 0) {
                      Reflect(vm);
                      return;
                      }
                    if (vms[dvm].Mode == 1) {
                      dy=0;
                      dz=0;
                      cz=1;
                      cy=1;
                      }
                    if (vms[dvm].Mode == 2) {
                      dz=0;
                      cz=1;
                      }
                    for (z=0; z<cz; z++)
                      for (y=0; y<cy; y++)
                        for (x=0; x<cx; x++) {
                          Put_Funge(&(vms[dvm]),x+dx,y+dy,z+dz,
                            Get_Funge(vm,x+sx,y+sy,z+sz));
                          }
                    break;
    }
}
#endif

