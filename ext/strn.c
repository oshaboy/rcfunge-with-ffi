/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef STRN
#include <time.h>
#include <string.h>
#include "funge.h"

void rcs_strncpy(char* dest,char* src,int n) {
  while (n>0 && *src != 0) {
    *dest++ = *src++;
    n--;
    }
  *dest = 0;
  }

void Load_STRN(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_STRN+06;    /* A */
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_STRN+11;    /* C */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_STRN+03;    /* D */
  vm->IPs[cip].Overloads[5][vm->IPs[cip].NumOvers]=EX_STRN+8;     /* F */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_STRN+01;    /* G */
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_STRN+12;    /* I */
  vm->IPs[cip].Overloads[11][vm->IPs[cip].NumOvers]=EX_STRN+02;   /* L */
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_STRN+05;   /* M */
  vm->IPs[cip].Overloads[13][vm->IPs[cip].NumOvers]=EX_STRN+07;   /* N */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_STRN+00;   /* P */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_STRN+04;   /* R */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_STRN+10;   /* S */
  vm->IPs[cip].Overloads[21][vm->IPs[cip].NumOvers]=EX_STRN+9;    /* V */
}

void Unload_STRN(VM* vm) {
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,5);
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,8);
  Unload_Semantic(vm,11);
  Unload_Semantic(vm,12);
  Unload_Semantic(vm,13);
  Unload_Semantic(vm,15);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,21);
  }

void Do_STRN(VM* vm,int Cmd)
{
  char Buffer[1000];
  char Buffer1[1000];
  char *Pchar;
  INT x,y,z,a,b;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_STRN+00:if (vm->Mode>2) z=Pop(vm); else z=0;     /* STRN, P */
               if (vm->Mode>1) y=Pop(vm); else y=0;
               x=Pop(vm);
               a=1;
               while (a!=0) {
                 a=Pop(vm); Put_Funge(vm,x,y,z,a); x++;
                 }
               break;
    case EX_STRN+01:if (vm->Mode>2) z=Pop(vm); else z=0;     /* STRN, G */
               if (vm->Mode>1) y=Pop(vm); else y=0;
               x=Pop(vm);
               a=1; b=0;
               while (a!=0 && b<998) {
                 a=Get_Funge(vm,x,y,z); x++; Buffer[b++]=a;
                 }
               if (b==998) Buffer[b] = 0;
               Push_String(vm,Buffer);
               break;
    case EX_STRN+02:a=Pop(vm);                           /* STRN, L */
               if (a<0) {
                 Reflect(vm);
                 return;
                 }
               if (a < 0) a=0;
               Pop_String(vm,Buffer);
               rcs_strncpy(Buffer1,Buffer,a);
               Push_String(vm,Buffer1);
               break;
    case EX_STRN+03:Pop_String(vm,Buffer);               /* STRN, D */
               printf("%s",Buffer);
               break;
    case EX_STRN+04:a=Pop(vm);                           /* STRN, R */
               if (a<0) {
                 Reflect(vm);
                 return;
                 }
               if (a<0) a=0;
               Pop_String(vm,Buffer);
               b=strlen(Buffer)-a;
               if (b<0) b=0;
               rcs_strncpy(Buffer1,&Buffer[b],a);
               Push_String(vm,Buffer1);
               break;
    case EX_STRN+05:a=Pop(vm); b=Pop(vm);               /* STRN, M */
               if (a<0 || b<0) {
                 Reflect(vm);
                 return;
                 }
               Pop_String(vm,Buffer);
               if (b >= strlen(Buffer)) {
                 Push_String(vm,Buffer);
                 Reflect(vm);
                 return;
                 }
               rcs_strncpy(Buffer1,&Buffer[b],a);
               Push_String(vm,Buffer1);
               break;
    case EX_STRN+06:Pop_String(vm,Buffer);               /* STRN, A */
               Pop_String(vm,Buffer1);
               strcat(Buffer,Buffer1);
               Push_String(vm,Buffer);
               break;
    case EX_STRN+07:Pop_String(vm,Buffer);               /* STRN, N */
               Push_String(vm,Buffer);
               Push(vm,strlen(Buffer));
               break;
    case EX_STRN+8 :Pop_String(vm,Buffer);               /* STRN, F */
               Pop_String(vm,Buffer1);
               Pchar=(char*)strstr(Buffer,Buffer1);
               if (Pchar != NULL) Push_String(vm,Pchar);
               else Push(vm,0);
               break;
    case EX_STRN+9 :Pop_String(vm,Buffer);               /* STRN, V */
               sscanf(Buffer,"%d",&a);
               Push(vm,a); break;
    case EX_STRN+10:a=Pop(vm);                           /* STRN, S */
               sprintf(Buffer,"%d",a);
               Push_String(vm,Buffer); break;
    case EX_STRN+11:Pop_String(vm,Buffer);               /* STRN, C */
               Pop_String(vm,Buffer1);
               Push(vm,strcmp(Buffer,Buffer1));
               break;
    case EX_STRN+12:gets(Buffer);                         /* STRN, I */
               Push_String(vm,Buffer); break;

    }
}
#endif

