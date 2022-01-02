/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef FILS
#include <time.h>
#include "funge.h"

void Load_FILE(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_FILE+ 1;   /* C */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_FILE+ 8;   /* D */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_FILE+ 3;   /* G */
  vm->IPs[cip].Overloads[11][vm->IPs[cip].NumOvers]=EX_FILE+ 7;  /* L */
  vm->IPs[cip].Overloads[14][vm->IPs[cip].NumOvers]=EX_FILE+ 0;  /* O */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_FILE+ 2;  /* P */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_FILE+ 5;  /* R */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_FILE+ 6;  /* S */
  vm->IPs[cip].Overloads[22][vm->IPs[cip].NumOvers]=EX_FILE+ 4;  /* W */
}

void Unload_FILE(VM* vm) {
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,11);
  Unload_Semantic(vm,14);
  Unload_Semantic(vm,15);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,22);
  }


void Do_FILE(VM* vm,int Cmd)
{
  INT i;
  INT a,b,c;
  INT x,y,z;
  char* result;
  char Buffer[1000];
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_FILE+ 8:Pop_String(vm,Buffer);               /* FILE, D */
                    x = unlink(Buffer);
                    if (x<0) Reflect(vm);
                    break;
    case EX_FILE+00:Pop_String(vm,Buffer);               /* FILE, O */
                    a=Pop(vm);
                    if (vm->Mode>2) z=Pop(vm); else z=0;
                    if (vm->Mode>1) y=Pop(vm); else y=0;
                    x=Pop(vm);
                    i=0;
                    while (vm->Files[i].Handle!=NULL && i<MAX_FFILES) i++;
                    if (i==MAX_FFILES) Reflect(vm);
                    else {
                      switch(a) {
                        case 0:vm->Files[i].Handle=fopen(Buffer,"r"); break;
                        case 1:vm->Files[i].Handle=fopen(Buffer,"w"); break;
                        case 2:vm->Files[i].Handle=fopen(Buffer,"a"); break;
                        case 3:vm->Files[i].Handle=fopen(Buffer,"r+"); break;
                        case 4:vm->Files[i].Handle=fopen(Buffer,"w+"); break;
                        case 5:vm->Files[i].Handle=fopen(Buffer,"a+"); break;
                        }
                      if (vm->Files[i].Handle != NULL) {
                        vm->Files[i].BufferX=x;
                        vm->Files[i].BufferY=y;
                        vm->Files[i].BufferZ=z;
                        Push(vm,i);
                        } else Reflect(vm);
                      }
                    break;
    case EX_FILE+01:a=Pop(vm);                           /* FILE, C */
                    if (vm->Files[a].Handle!=NULL) {
                      fclose(vm->Files[a].Handle);
                      vm->Files[a].Handle = NULL;
                      }
                      else Reflect(vm);
                    break;
    case EX_FILE+02:Pop_String(vm,Buffer);               /* FILE, P */
                    a=Pop(vm);
                    if (vm->Files[a].Handle!=NULL) {
                      fputs(Buffer,vm->Files[a].Handle);
                      }
                      else Reflect(vm);
                    Push(vm,a);
                    break;
    case EX_FILE+03:a=Pop(vm);                           /* FILE, G */
                    Push(vm,a);
                    if (vm->Files[a].Handle!=NULL) {
                      result = fgets(Buffer,1000,vm->Files[a].Handle);
                      if (result == NULL) {
                        Push(vm,0);
                        Push(vm,0);
                        return;
                        }
                      b=strlen(Buffer);
                      if (b == 0) Push(vm,0);
                        else Push_String(vm,Buffer);
                      Push(vm,b);
                      }
                      else Reflect(vm);
                    break;
    case EX_FILE+04:b=Pop(vm);                           /* FILE, W */
                    a=Pop(vm);
                    Push(vm,a);
                    if (vm->Files[a].Handle!=NULL) {
                      x=vm->Files[a].BufferX;
                      y=vm->Files[a].BufferY;
                      z=vm->Files[a].BufferZ;
                      for (i=0;i<b;i++)
                        Buffer[i]=(char)Get_Funge(vm,x+i,y,z);
                      fwrite(Buffer,b,1,vm->Files[a].Handle);
                      }
                      else Reflect(vm);
                    break;
    case EX_FILE+05:b=Pop(vm);                           /* FILE, R */
                    a=Pop(vm);
                    Push(vm,a);
                    if (vm->Files[a].Handle!=NULL) {
                      x=vm->Files[a].BufferX;
                      y=vm->Files[a].BufferY;
                      z=vm->Files[a].BufferZ;
                      if (fread(Buffer,b,1,vm->Files[a].Handle) == 0) {
                        Push(vm,0);
                        Push(vm,0);
                        return;
                        }
                      for (i=0;i<b;i++)
                        Put_Funge(vm,x+i,y,z,Buffer[i]);
                      }
                      else Reflect(vm);
                    break;
    case EX_FILE+06:b=Pop(vm);                           /* FILE, S */
                    c=Pop(vm);
                    a=Pop(vm);
                    Push(vm,a);
                    if (vm->Files[a].Handle!=NULL) {
                      switch(c) {
                        case SEEK_SET:fseek(vm->Files[a].Handle,b,SEEK_SET); break;
                        case SEEK_CUR:fseek(vm->Files[a].Handle,b,SEEK_CUR); break;
                        case SEEK_END:fseek(vm->Files[a].Handle,b,SEEK_END); break;
                        }
                      }
                      else Reflect(vm);
                    break;
    case EX_FILE+07:a=Pop(vm);                           /* FILE, T */
                    Push(vm,a);
                    if (vm->Files[a].Handle!=NULL) {
                      Push(vm,ftell(vm->Files[a].Handle));
                      }
                      else Reflect(vm);
                    break;
    }
}
#endif

