/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef DIRF
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "funge.h"
/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */


void Load_DIRF(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_DIRF+01;   /* C */
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_DIRF+00;  /* M */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_DIRF+02;  /* R */
}

void Unload_DIRF(VM* vm) {
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,12);
  Unload_Semantic(vm,17);
  }


void Do_DIRF(VM* vm,int Cmd)
{
  char Buffer[1000];
  switch (Cmd) {
    case EX_DIRF+00:Pop_String(vm,Buffer);                           /*  M */
                    if (mkdir(Buffer,0700)!=0) Reflect(vm);
                    break;
    case EX_DIRF+01:Pop_String(vm,Buffer);                           /*  C */
                    if (chdir(Buffer)!=0) Reflect(vm);
                    break;
    case EX_DIRF+02:Pop_String(vm,Buffer);                           /*  R */
                    if (rmdir(Buffer)!=0) Reflect(vm);
                    break;
    }
}
#endif

