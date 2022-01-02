/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef SGNL
#include <time.h>
#include <signal.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

VECTOR *handlers;
int    numHandlers;
char   sgnlLoaded = 'N';
VM*    vMach;

void Load_SGNL(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[7][vm->IPs[cip].NumOvers]=EX_SGNL+ 7;   /* H */
  vm->IPs[cip].Overloads[10][vm->IPs[cip].NumOvers]=EX_SGNL+10;  /* K */
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_SGNL+12;  /* M */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_SGNL+17;  /* R */
  vm->IPs[cip].Overloads[23][vm->IPs[cip].NumOvers]=EX_SGNL+23;  /* X */
  vm->IPs[cip].Overloads[24][vm->IPs[cip].NumOvers]=EX_SGNL+24;  /* Y */
  if (sgnlLoaded == 'N') {
    sgnlLoaded = 'Y';
    numHandlers = 0;
    handlers = NULL;
    vMach = vm;
    }
}

void Unload_SGNL(VM* vm) {
  Unload_Semantic(vm,7);
  Unload_Semantic(vm,10);
  Unload_Semantic(vm,12);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,23);
  Unload_Semantic(vm,24);
  }

static void signalHandler(int signo,struct siginfo* info,void* x) {
  int i;
  int old;
  for (i=0; i<numHandlers; i++)
    if (handlers[i].Alloc == signo) {
      Insert_IP(vMach,New_IP(vMach));
      vMach->IPs[vMach->NumIPs-1].DeltaX=1;
      vMach->IPs[vMach->NumIPs-1].DeltaY=0;
      vMach->IPs[vMach->NumIPs-1].DeltaZ=0;
      vMach->IPs[vMach->NumIPs-1].x = handlers[i].x;
      vMach->IPs[vMach->NumIPs-1].y = handlers[i].y;
      vMach->IPs[vMach->NumIPs-1].z = handlers[i].z;
      old = vMach->cip;
      vMach->cip = vMach->NumIPs-1;
      if (info != NULL) Push(vMach,info->si_pid);
        else Push(vMach,0);
      Push(vMach,signo);
      vMach->cip = old;
    }
  return;
  }

void Do_SGNL(VM* vm,int Cmd) {
  int i;
  int p;
  int h;
  int cip;
  struct sigaction action;
  VECTOR v;
  sigset_t set;
  cip = vm->cip;
  switch (Cmd) {
    case EX_SGNL+ 7:p=Pop(vm);                           /* SGNL, H */
                    action.sa_sigaction = signalHandler;
                    sigemptyset(&action.sa_mask);
                    action.sa_flags = SA_SIGINFO;
#ifdef SA_RESTART
                    action.sa_flags |= SA_RESTART;
#endif
                    i=sigaction(p,&action,NULL);
                    v = Pop_Vector(vm);
                    v.Alloc = p;
                    numHandlers++;
                    if (numHandlers == 1)
                      handlers = (VECTOR*)malloc(sizeof(VECTOR));
                    else
                      handlers = (VECTOR*)realloc(handlers,sizeof(VECTOR)*numHandlers);
                    handlers[numHandlers-1] = v;
                    break;
    case EX_SGNL+10:i=Pop(vm);                           /* SGNL, K */
                    p=Pop(vm);
                    kill(p,i);
                    break;
    case EX_SGNL+12:i=Pop(vm);                           /* SGNL, M */
                    p=Pop(vm);
                    if (p < 0 || p > 2) {
                      Reflect(vm);
                      return;
                      }
                    sigemptyset(&set);
                    sigaddset(&set,i);
                    switch (p) {
                      case 0:h = SIG_BLOCK; break;
                      case 1:h = SIG_UNBLOCK; break;
                      case 2:h = SIG_SETMASK; break;
                      }
                    sigprocmask(h,&set,NULL);
                    break;
    case EX_SGNL+17:p=Pop(vm);                           /* SGNL, R */
                    action.sa_handler = SIG_DFL;
                    sigemptyset(&action.sa_mask);
                    action.sa_flags = 0;
                    sigaction(p,&action,NULL);
                    for (i=0; i<numHandlers; i++)
                      if (handlers[i].Alloc == p) {
                        numHandlers--;
                        for (h=i; h<numHandlers-1; h++)
                          handlers[h] = handlers[h+1];
                        if (numHandlers == 0) free(handlers);
                          else handlers = (VECTOR*)realloc(handlers,sizeof(VECTOR)*numHandlers);
                        }
                    break;
    case EX_SGNL+23:i=Pop(vm);                           /* SGNL, X */
                    Put_Funge(vm,vm->IPs[cip].x-vm->IPs[cip].OffsetX,
                                 vm->IPs[cip].y-vm->IPs[cip].OffsetY,
                                 vm->IPs[cip].z-vm->IPs[cip].OffsetZ,i);
                    break;
    case EX_SGNL+24:Sub_Delta(vm);                       /* SGNL, Y */
                    break;
    }
}

#endif

