/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#include <string.h>
#ifdef EVAR
#include "funge.h"
/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */
void Load_EVAR(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_EVAR+00;   /* G */
  vm->IPs[cip].Overloads[13][vm->IPs[cip].NumOvers]=EX_EVAR+02;  /* N */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_EVAR+01;  /* P */
  vm->IPs[cip].Overloads[21][vm->IPs[cip].NumOvers]=EX_EVAR+03;  /* V */
}

void Unload_EVAR(VM* vm) {
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,13);
  Unload_Semantic(vm,15);
  Unload_Semantic(vm,21);
  }

void Do_EVAR(VM* vm,int Cmd)
{
  int i,j;
  char Buffer[1000];
  char *Pchar;
  switch (Cmd) {
    case EX_EVAR+00:Pop_String(vm,Buffer);                           /*  G */
                    Pchar=getenv(Buffer);
                    if (Pchar != NULL) Push_String(vm,Pchar);
                      else Push(vm,0);
                    break;
    case EX_EVAR+01:Pop_String(vm,Buffer);                           /*  P */
                    Pchar=(char *)malloc(strlen(Buffer)+1);
                    if (Pchar == NULL) {
                      printf("EVAR: could not allocate temp memory\n");
                      exit(-1);
                      }
                    strcpy(Pchar,Buffer);
                    putenv(Pchar);
                    break;
    case EX_EVAR+02:i=0;                                              /*  N */
                    while (Envp[i] != NULL) i++;
                    Push(vm,i); break;
    case EX_EVAR+03:i=Pop(vm);                                        /*  V */
                    j=0;                                              /*  N */
                    while (Envp[j] != NULL) j++;
                    if (i>=j) Reflect(vm);
                    else {
                      if (Envp[i]!=NULL) Push_String(vm,Envp[i]);
                      else Push(vm,0);
                      }
                    break;
    }
}
#endif

