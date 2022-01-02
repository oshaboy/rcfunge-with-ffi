/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef TIME
#include <time.h>
#include "funge.h"
/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */


void Load_TIME(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_TIME+00;     /* D */
  vm->IPs[cip].Overloads[5][vm->IPs[cip].NumOvers]=EX_TIME+01;     /* F */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_TIME+9 ;     /* G */
  vm->IPs[cip].Overloads[7][vm->IPs[cip].NumOvers]=EX_TIME+02;     /* H */
  vm->IPs[cip].Overloads[11][vm->IPs[cip].NumOvers]=EX_TIME+8 ;    /* L */
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_TIME+03;    /* M */
  vm->IPs[cip].Overloads[14][vm->IPs[cip].NumOvers]=EX_TIME+04;    /* O */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_TIME+05;    /* S */
  vm->IPs[cip].Overloads[22][vm->IPs[cip].NumOvers]=EX_TIME+06;    /* W */
  vm->IPs[cip].Overloads[24][vm->IPs[cip].NumOvers]=EX_TIME+07;    /* Y */
}

void Unload_TIME(VM* vm) {
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,5);
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,7);
  Unload_Semantic(vm,11);
  Unload_Semantic(vm,12);
  Unload_Semantic(vm,14);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,22);
  Unload_Semantic(vm,24);
  }

void Do_TIME(VM* vm,int Cmd)
{
  struct tm *Tm;
  time_t t;
  int cip;
  cip = vm->cip;
  t=time(NULL);
  if (vm->IPs[cip].TimeMode=='G') Tm=gmtime(&t);
    else Tm=localtime(&t);
  switch (Cmd) {
    case EX_TIME+00:Push(vm,Tm->tm_mday); break;                /*  D */
    case EX_TIME+01:Push(vm,Tm->tm_yday); break;                /*  F */
    case EX_TIME+02:Push(vm,Tm->tm_hour); break;                /*  H */
    case EX_TIME+03:Push(vm,Tm->tm_min); break;                 /*  M */
    case EX_TIME+04:Push(vm,Tm->tm_mon+1); break;               /*  O */
    case EX_TIME+05:Push(vm,Tm->tm_sec); break;                 /*  S */
    case EX_TIME+06:Push(vm,Tm->tm_wday+1); break;              /*  W */
    case EX_TIME+07:Push(vm,Tm->tm_year+1900); break;           /*  Y */
    case EX_TIME+8 :vm->IPs[cip].TimeMode='L'; break;                /*  L */
    case EX_TIME+9 :vm->IPs[cip].TimeMode='G'; break;                /*  G */
    }
}
#endif

