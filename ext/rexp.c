/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef REXP
#include <time.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_REXP(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_REXP+02;   /* C */
  vm->IPs[cip].Overloads[4][vm->IPs[cip].NumOvers]=EX_REXP+04;   /* E */
  vm->IPs[cip].Overloads[5][vm->IPs[cip].NumOvers]=EX_REXP+05;   /* F */
}

void Unload_REXP(VM* vm) {
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,4);
  Unload_Semantic(vm,5);
  }

void Do_REXP(VM* vm,int Cmd)
{
  int flags;
  int n;
  int i;
  char buffer[1000];
  char buffer2[1000];
  regmatch_t matches[100];
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_REXP+02:n=Pop(vm);                            /* REXP, C */
                    Pop_String(vm,buffer);
                    flags = 0;
                    if (n&1) flags |= REG_EXTENDED;
                    if (n&2) flags |= REG_ICASE;
                    if (n&4) flags |= REG_NOSUB;
                    if (n&8) flags |= REG_NEWLINE;
                    n = regcomp(&(vm->IPs[cip].preg),buffer,flags);
                    if (n == 0) return;
                    Reflect(vm);
                    switch (n) {
                      case REG_BADBR:Push(vm,1); break;
                      case REG_BADPAT:Push(vm,2); break;
                      case REG_BADRPT:Push(vm,3); break;
                      case REG_EBRACE:Push(vm,4); break;
                      case REG_EBRACK:Push(vm,5); break;
                      case REG_ECOLLATE:Push(vm,6); break;
                      case REG_ECTYPE:Push(vm,7); break;
#ifndef OSX
                      case REG_EEND:Push(vm,8); break;
#endif
                      case REG_EESCAPE:Push(vm,9); break;
                      case REG_EPAREN:Push(vm,10); break;
                      case REG_ERANGE:Push(vm,11); break;
#ifndef OSX
                      case REG_ESIZE:Push(vm,12); break;
#endif
                      case REG_ESPACE:Push(vm,13); break;
                      case REG_ESUBREG:Push(vm,14); break;
                      default:Push(vm,n+100); break;
                      }
                    break;
    case EX_REXP+04:n=Pop(vm);                            /* REXP, E */
                    Pop_String(vm,buffer);
                    flags = 0;
                    if (n&1) flags |= REG_NOTBOL;
                    if (n&2) flags |= REG_NOTEOL;
                    n = regexec(&(vm->IPs[cip].preg),buffer,100,matches,flags);
                    if (n != 0) {
                      Reflect(vm);
                      return;
                      }
                    n = 0;
                    for (i=99; i>=0; i--) {
                      if (matches[i].rm_so != -1 && matches[i].rm_eo != -1) {
                        n++;
                        strncpy(buffer2,buffer+matches[i].rm_so,
                          matches[i].rm_eo-matches[i].rm_so);
                        buffer2[matches[i].rm_eo-matches[i].rm_so] = 0;
                        Push_String(vm,buffer2);
                        }
                      }
                    Push(vm,n);
                    break;
    case EX_REXP+05:regfree(&(vm->IPs[cip].preg));             /* REXP, F */
                    break;
    }
}
#endif

