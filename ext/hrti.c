/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef HRTI
#include <time.h>
#include <sys/time.h>
#include "funge.h"

void Load_HRTI(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  vm->IPs[cip].Overloads[4][vm->IPs[cip].NumOvers]=EX_HRTI+03;   /* E */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_HRTI+00;   /* G */
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_HRTI+01;  /* M */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_HRTI+04;  /* S */
  vm->IPs[cip].Overloads[19][vm->IPs[cip].NumOvers]=EX_HRTI+02;  /* T */
  Push(vm,FingerPrint); Push(vm,1);
}

void Unload_HRTI(VM* vm) {
  Unload_Semantic(vm,4);
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,12);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,19);
  }

void Do_HRTI(VM* vm,int Cmd)
{
  struct timeval tv;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case  EX_HRTI+00:Push(vm,1000000/CLOCKS_PER_SEC);     /* HRTI, G */
                     break;
    case  EX_HRTI+01:                                      /* HRTI, M */
                     gettimeofday(&tv,NULL);
                     vm->IPs[cip].Timer = tv.tv_usec+tv.tv_sec*1000000;
/*                   vm->IPs[cip].Timer=clock(); break; */
                     break;
    case  EX_HRTI+02:if (vm->IPs[cip].Timer== -1) Reflect(vm);/* HRTI, T */
                     else {
                       gettimeofday(&tv,NULL);
                       Push(vm,(tv.tv_usec+tv.tv_sec*1000000)-vm->IPs[cip].Timer);
/*
                       Push(vm,clock()-vm->IPs[cip].Timer*
                           (1000000/CLOCKS_PER_SEC));
*/
                       }
                     break;
    case  EX_HRTI+03:vm->IPs[cip].Timer=-1; break;             /* HRTI, E */
    case  EX_HRTI+04:                                      /* HRTI, S */
                     gettimeofday(&tv,NULL);
                     Push(vm,tv.tv_usec);
/* Push(vm,clock()*(1000000/CLOCKS_PER_SEC)); */
                     break;



if (vm->IPs[cip].Timer== -1) Reflect(vm);
                     else {
                       Push(vm,(clock()-vm->IPs[cip].Timer*(1000000/CLOCKS_PER_SEC))
                            % CLOCKS_PER_SEC);
                       }
                     break;
    }
}
#endif

