/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef PERL
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "funge.h"

void Load_PERL(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[4][vm->IPs[cip].NumOvers]=EX_PERL+01;   /* E */
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_PERL+02;   /* I */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_PERL+00;  /* S */
}

void Unload_PERL(VM* vm) {
  Unload_Semantic(vm,4);
  Unload_Semantic(vm,8);
  Unload_Semantic(vm,18);
  }

int exec_perl(VM* vm,char* ret) {
  INT a;
  size_t sz;
  int file;
  char Buffer[1000];
  char Buffer1[1000];
  Pop_String(vm,Buffer1);
  strcpy(Buffer,"print eval(");
  strcat(Buffer,Buffer1);
  strcat(Buffer,");");
  file = open("PERL_E.pl",O_CREAT|O_TRUNC|O_WRONLY,0666);
  if (file < 0) {
    Reflect(vm);
    return -1;
    }
  write(file,Buffer,strlen(Buffer));
  close(file);
  strcpy(Buffer,"perl PERL_E.pl > PERL_E.ZZZ");
  a=system(Buffer);
  if (a != 0) {
    sprintf(Buffer,"%d",a);
    Push_String(vm,Buffer);
    unlink("PERL_E.pl");
    unlink("PERL_E.ZZZ");
    return -1;
    }
  file = open("PERL_E.ZZZ",O_RDONLY);
  if (file < 0) {
    Reflect(vm);
    unlink("PERL_E.pl");
    unlink("PERL_E.ZZZ");
    return -1;
    }
  sz = read(file,Buffer,1000);
  Buffer[sz] = 0;
  strcpy(ret,Buffer);
  unlink("PERL_E.pl");
  unlink("PERL_E.ZZZ");
  return 0;
  }

void Do_PERL(VM* vm,int Cmd)
{
  INT a;
  char Buffer[1000];
  char Buffer1[1000];
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_PERL+00:Push(vm,1); break;                    /* PERL, S */
    case EX_PERL+01:a = exec_perl(vm,Buffer);             /* PERL, E */
                    Push_String(vm,Buffer);
                    break;
    case EX_PERL+02:a = exec_perl(vm,Buffer);             /* PERL, I */
                    Push(vm,atoi(Buffer));
                    break;
    }
}
#endif

