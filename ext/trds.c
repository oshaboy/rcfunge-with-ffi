/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef TRDS
#include "funge.h"
/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */


void Load_TRDS(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_TRDS+8;    /* C */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_TRDS+03;   /* D */
  vm->IPs[cip].Overloads[4][vm->IPs[cip].NumOvers]=EX_TRDS+05;   /* E */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_TRDS+02;   /* G */
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_TRDS+11;   /* I */
  vm->IPs[cip].Overloads[9][vm->IPs[cip].NumOvers]=EX_TRDS+04;   /* J */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_TRDS+00;  /* P */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_TRDS+01;  /* R */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_TRDS+07;  /* S */
  vm->IPs[cip].Overloads[19][vm->IPs[cip].NumOvers]=EX_TRDS+9;   /* T */
  vm->IPs[cip].Overloads[20][vm->IPs[cip].NumOvers]=EX_TRDS+10;  /* U */
  vm->IPs[cip].Overloads[21][vm->IPs[cip].NumOvers]=EX_TRDS+06;  /* V */
}

void Unload_TRDS(VM* vm) {
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,4);
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,8);
  Unload_Semantic(vm,9);
  Unload_Semantic(vm,15);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,19);
  Unload_Semantic(vm,20);
  Unload_Semantic(vm,21);
  }

void past(VM* vm) {
  int i,j;
  int cip;
  cip = vm->cip;
  IP  tmpIP;
  vm->TimeJumped=1;
/* ********************************************************************** */
/* ***** If jump before beginning of time, set to beginning of time ***** */
/* ********************************************************************** */
  if (vm->IPs[cip].TTime < 0) {
    vm->IPs[cip].TTime = 0;
    }
/* ***************************************************** */
/* ***** Search jump table to see if this jump has ***** */
/* ***** already been taken                        ***** */
/* ***************************************************** */
  j=0;
  for (i=0; i<vm->NumJumps; i++) {
    if (vm->Jumps[i].uid == vm->IPs[cip].uid &&
        vm->Jumps[i].RTSpX == vm->IPs[cip].RTSpX &&
        vm->Jumps[i].RTSpY == vm->IPs[cip].RTSpY &&
        vm->Jumps[i].RTSpZ == vm->IPs[cip].RTSpZ &&
        vm->Jumps[i].x == vm->IPs[cip].x &&
        vm->Jumps[i].y == vm->IPs[cip].y &&
        vm->Jumps[i].z == vm->IPs[cip].z &&
        vm->Jumps[i].serial == vm->IPs[cip].serial &&
        abs(vm->Jumps[i].RTTime - vm->Jumps[i].RTTime)<2 &&
        vm->Jumps[i].TTime == vm->IPs[cip].TTime) j=1;
    }
/* ******************************************************** */
/* ***** If jump was already in jump table, then this ***** */
/* ***** is a repeated jump and should not be taken   ***** */
/* ******************************************************** */
  if (j==1) {
    vm->IPs[cip].uid = -1;
    vm->TimeJumped=0;
    }
/* ******************************************************* */
/* ***** Process a new jump                          ***** */
/* ***** First remove all IPs except the current one ***** */
/* ******************************************************* */
  else {
    for (i=0;i<vm->NumIPs;i++) if (i!=cip) {
      Del_IP(&(vm->IPs[i]));
      }
/* ****************************************************** */
/* ***** Remove jump table entries that occur after ***** */
/* ***** the arrival time of the new jump.  The     ***** */
/* ***** future does not exist beyond this point    ***** */
/* ***** and there fore these jumps can recur       ***** */
/* ****************************************************** */
    i=0;
    while (i<vm->NumJumps) {
      if (vm->Jumps[i].TTime > vm->IPs[cip].TTime) {
        for (j=i; j<vm->NumJumps-1; j++) vm->Jumps[j] = vm->Jumps[j+1];
        vm->NumJumps--;
        if (vm->NumJumps == 0) {
          free(vm->Jumps);
          vm->Jumps = NULL;
          }
        else vm->Jumps=(IP*)realloc(vm->Jumps,sizeof(IP)*vm->NumJumps);
        }
      else i++;
      }
/* ****************************************************** */
/* ***** Insert new jump into jump table to prevent ***** */
/* ***** its recurrance                             ***** */
/* ****************************************************** */
    vm->NumJumps++;
    if (vm->NumJumps == 1) vm->Jumps=(IP*)malloc(sizeof(IP));
      else vm->Jumps=(IP*)realloc(vm->Jumps,sizeof(IP)*vm->NumJumps);
    vm->IPs[cip].RunTime=vm->IPs[cip].TTime;
    vm->IPs[cip].Jumped=vm->CycleCount;
    vm->Jumps[vm->NumJumps-1] = vm->IPs[cip];
/* ****************************************** */
/* ***** Reset VM to run from beginning ***** */
/* ****************************************** */
    Reset_VM(vm);
    vm->uid=0;
    vm->PrintTime=vm->IPs[cip].TTime;
    vm->IPs[cip].serial++;
    vm->CycleCount=0;
    vm->StopTime=-1;
    vm->NumIPs = 0;
    Insert_IP(vm,New_IP(vm));
/* ****************************************** */
/* ***** Now insert time-travelling IPs ***** */
/* ****************************************** */
    vm->NumIPs += vm->NumJumps;
    vm->IPs = (IP*)realloc(vm->IPs,sizeof(IP)*vm->NumIPs);
    for (i=0; i<vm->NumJumps; i++) {
      vm->IPs[i+1] = Dup_IP(vm->Jumps[i]);
      vm->IPs[i+1].serial++;
      vm->cip = i+1;
      Add_Delta(vm);
      vm->cip = cip;
      }
    }
  }




void Do_TRDS(VM* vm,int Cmd)
{
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_TRDS+00:Push(vm,0); break;                               /*  P */
    case EX_TRDS+01:vm->IPs[cip].SpMode='D';                              /*  R */
                    vm->IPs[cip].VMode='D';
                    vm->IPs[cip].TMode='D';
                    vm->IPs[cip].TTime=0;
                    vm->IPs[cip].TvX=0; vm->IPs[cip].TvY=0; vm->IPs[cip].TvZ=0;
                    vm->IPs[cip].TSpX=0; vm->IPs[cip].TSpY=0; vm->IPs[cip].TSpZ=0;
                    break;
    case EX_TRDS+02:Push(vm,vm->CycleCount); break;                /*  G */
    case EX_TRDS+03:vm->IPs[cip].SpMode='A';                              /*  D */
                    if (vm->Mode>2) vm->IPs[cip].TSpZ=Pop(vm); else vm->IPs[cip].TSpZ=0;
                    if (vm->Mode>1) vm->IPs[cip].TSpY=Pop(vm); else vm->IPs[cip].TSpY=0;
                    vm->IPs[cip].TSpX=Pop(vm); break;
    case EX_TRDS+04:                                                  /*  J */
                    /* *********************************** */
                    /* ***** Setup return coodinates ***** */
                    /* *********************************** */
                    Add_Delta(vm);
                    vm->IPs[cip].RTSpX=vm->IPs[cip].x;
                    vm->IPs[cip].RTSpY=vm->IPs[cip].y;
                    vm->IPs[cip].RTSpZ=vm->IPs[cip].z;
                    vm->IPs[cip].RTvX=vm->IPs[cip].DeltaX;
                    vm->IPs[cip].RTvY=vm->IPs[cip].DeltaY;
                    vm->IPs[cip].RTvZ=vm->IPs[cip].DeltaZ;
                    vm->IPs[cip].RTTime=vm->CycleCount;
                    Sub_Delta(vm);
                    /* *************************************** */
                    /* ***** Process absolute space jump ***** */
                    /* *************************************** */
                    if (vm->IPs[cip].SpMode=='A') {
                      vm->IPs[cip].x=vm->IPs[cip].TSpX;
                      vm->IPs[cip].y=vm->IPs[cip].TSpY;
                      vm->IPs[cip].z=vm->IPs[cip].TSpZ;
                      Sub_Delta(vm);
                      }
                    /* *************************************** */
                    /* ***** Process relative space jump ***** */
                    /* *************************************** */
                    if (vm->IPs[cip].SpMode=='R') {
                      vm->IPs[cip].x+=vm->IPs[cip].TSpX;
                      vm->IPs[cip].y+=vm->IPs[cip].TSpY;
                      vm->IPs[cip].z+=vm->IPs[cip].TSpZ;
                      Sub_Delta(vm);
                      }
                    /* ************************************** */
                    /* ***** Process destination vector ***** */
                    /* ************************************** */
                    if (vm->IPs[cip].VMode=='Y') {
                      Add_Delta(vm);
                      vm->IPs[cip].DeltaX=vm->IPs[cip].TvX;
                      vm->IPs[cip].DeltaY=vm->IPs[cip].TvY;
                      vm->IPs[cip].DeltaZ=vm->IPs[cip].TvZ;
                      Sub_Delta(vm);
                      }
                    /* ************************************** */
                    /* ***** Process relative time jump ***** */
                    /* ************************************** */
                    if (vm->IPs[cip].TMode=='R') {
                      /* ***** To the future ***** */
                      if (vm->IPs[cip].TTime >= 0) {
                        vm->IPs[cip].TTime = vm->CycleCount+vm->IPs[cip].TTime;
                        vm->IPs[cip].RunTime = vm->IPs[cip].TTime;
                        }
                      /* ***** to the past ***** */
                      else {
                        vm->IPs[cip].TTime = vm->CycleCount+vm->IPs[cip].TTime;
                        past(vm);
                        return;
                        }
                      }
                    /* ************************************** */
                    /* ***** Process absolute time jump ***** */
                    /* ************************************** */
                    else if (vm->IPs[cip].TMode=='A') {
                      /* ***** To the future ***** */
                      if (vm->IPs[cip].TTime>=vm->CycleCount) {
                        vm->IPs[cip].RunTime=vm->IPs[cip].TTime;
                        }
                      /* ***** to the past ***** */
                      else {
                        past(vm);
                        }
                      }
                    break;
    case EX_TRDS+05:vm->IPs[cip].SpMode='R';                              /*  E */
                    if (vm->Mode>2) vm->IPs[cip].TSpZ=Pop(vm); else vm->IPs[cip].TSpZ=0;
                    if (vm->Mode>1) vm->IPs[cip].TSpY=Pop(vm); else vm->IPs[cip].TSpY=0;
                    vm->IPs[cip].TSpX=Pop(vm); break;
    case EX_TRDS+06:vm->IPs[cip].VMode='Y';                               /*  V */
                    if (vm->Mode>2) vm->IPs[cip].TvZ=Pop(vm); else vm->IPs[cip].TvZ=0;
                    if (vm->Mode>1) vm->IPs[cip].TvY=Pop(vm); else vm->IPs[cip].TvY=0;
                    vm->IPs[cip].TvX=Pop(vm); break;
    case EX_TRDS+07:vm->StopTime=cip; break;                              /*  S */
    case EX_TRDS+8 :vm->StopTime=-1; break;                               /*  C */
    case EX_TRDS+9 :vm->IPs[cip].TMode='A';                               /*  T */
                    vm->IPs[cip].TTime=Pop(vm); break;
    case EX_TRDS+10:vm->IPs[cip].TMode='R';                               /*  U */
                    vm->IPs[cip].TTime=Pop(vm);
                    break;
    case EX_TRDS+11:vm->IPs[cip].SpMode='A';                              /*  I */
                    vm->IPs[cip].VMode='Y';
                    if (vm->IPs[cip].TMode != 'D') vm->IPs[cip].TMode='A';
                    vm->IPs[cip].TSpX=vm->IPs[cip].RTSpX;
                    vm->IPs[cip].TSpY=vm->IPs[cip].RTSpY;
                    vm->IPs[cip].TSpZ=vm->IPs[cip].RTSpZ;
                    vm->IPs[cip].TvX=vm->IPs[cip].RTvX;
                    vm->IPs[cip].TvY=vm->IPs[cip].RTvY;
                    vm->IPs[cip].TvZ=vm->IPs[cip].RTvZ;
                    vm->IPs[cip].TTime=vm->IPs[cip].RTTime;
                    break;
    }
}
#endif

