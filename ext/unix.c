/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef UNIX
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_UNIX(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_UNIX+ 0;   /* A */
  vm->IPs[cip].Overloads[1][vm->IPs[cip].NumOvers]=EX_UNIX+ 1;   /* B */
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_UNIX+ 2;   /* C */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_UNIX+ 3;   /* D */
  vm->IPs[cip].Overloads[4][vm->IPs[cip].NumOvers]=EX_UNIX+ 4;   /* E */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_UNIX+ 6;   /* G */
  vm->IPs[cip].Overloads[7][vm->IPs[cip].NumOvers]=EX_UNIX+ 7;   /* H */
  vm->IPs[cip].Overloads[10][vm->IPs[cip].NumOvers]=EX_UNIX+10;  /* K */
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_UNIX+12;  /* M */
  vm->IPs[cip].Overloads[13][vm->IPs[cip].NumOvers]=EX_UNIX+13;  /* N */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_UNIX+15;  /* P */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_UNIX+17;  /* R */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_UNIX+18;  /* S */
  vm->IPs[cip].Overloads[19][vm->IPs[cip].NumOvers]=EX_UNIX+19;  /* T */
  vm->IPs[cip].Overloads[20][vm->IPs[cip].NumOvers]=EX_UNIX+20;  /* U */
}

void Unload_UNIX(VM* vm) {
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,1);
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,4);
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,7);
  Unload_Semantic(vm,10);
  Unload_Semantic(vm,12);
  Unload_Semantic(vm,13);
  Unload_Semantic(vm,15);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,19);
  Unload_Semantic(vm,20);
  }

void Do_UNIX(VM* vm,int Cmd) {
  int i;
  int gid,uid;
  int cip;
  char buffer[1000];
  cip = vm->cip;
  switch (Cmd) {
    case EX_UNIX+ 0:i = Pop(vm);                         /* UNIX, A */
                    i = seteuid(i);
                    if (i < 0) Reflect(vm);
                    break;
    case EX_UNIX+ 1:i = Pop(vm);                         /* UNIX, B */
                    i = setegid(i);
                    if (i < 0) Reflect(vm);
                    break;
    case EX_UNIX+ 2:gid = Pop(vm);                       /* UNIX, C */
                    uid = Pop(vm);
                    Pop_String(vm,buffer);
                    i = chown(buffer,uid,gid);
                    if (i < 0) Reflect(vm);
                    break;
    case EX_UNIX+ 3:i = getdomainname(buffer,999);       /* UNIX, D */
                    if (i < 0) Reflect(vm);
                    else Push_String(vm,buffer);
                    break;
    case EX_UNIX+ 4:i = geteuid();                       /* UNIX, E */
                    if (i < 0) Reflect(vm);
                    else Push(vm,i);
                    break;
    case EX_UNIX+ 6:i = getgid();                        /* UNIX, G */
                    if (i < 0) Reflect(vm);
                    else Push(vm,i);
                    break;
    case EX_UNIX+ 7:i = gethostid();                     /* UNIX, H */
                    if (i < 0) Reflect(vm);
                    else Push(vm,i);
                    break;
    case EX_UNIX+10:i = Pop(vm);                         /* UNIX, K */
                    i = umask(i);
                    if (i < 0) Reflect(vm);
                    else Push(vm,i);
                    break;
    case EX_UNIX+12:i = Pop(vm);                         /* UNIX, M */
                    Pop_String(vm,buffer);
                    i = chmod(buffer,i);
                    if (i < 0) Reflect(vm);
                    break;
    case EX_UNIX+13:i = gethostname(buffer,999);         /* UNIX, N */
                    if (i < 0) Reflect(vm);
                    else Push_String(vm,buffer);
                    break;
    case EX_UNIX+15:i = getpid();                        /* UNIX, P */
                    if (i < 0) Reflect(vm);
                    else Push(vm,i);
                    break;
    case EX_UNIX+17:i = getegid();                       /* UNIX, R */
                    if (i < 0) Reflect(vm);
                    else Push(vm,i);
                    break;
    case EX_UNIX+18:i = Pop(vm);                         /* UNIX, S */
                    i = setuid(i);
                    if (i < 0) Reflect(vm);
                    break;
    case EX_UNIX+19:i = Pop(vm);                         /* UNIX, T */
                    i = setgid(i);
                    if (i < 0) Reflect(vm);
                    break;
    case EX_UNIX+20:i = getuid();                        /* UNIX, U */
                    if (i < 0) Reflect(vm);
                    else Push(vm,i);
                    break;
    }
}
#endif

