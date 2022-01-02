/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef FPSP
#include <time.h>
#include "funge.h"

void Load_FPSP(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_FPSP+02;   /* A */
  vm->IPs[cip].Overloads[1][vm->IPs[cip].NumOvers]=EX_FPSP+03;   /* B */
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_FPSP+04;   /* C */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_FPSP+05;   /* D */
  vm->IPs[cip].Overloads[4][vm->IPs[cip].NumOvers]=EX_FPSP+06;   /* E */
  vm->IPs[cip].Overloads[5][vm->IPs[cip].NumOvers]=EX_FPSP+07;   /* F */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_FPSP+8;    /* G */
  vm->IPs[cip].Overloads[7][vm->IPs[cip].NumOvers]=EX_FPSP+9;    /* H */
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_FPSP+10;   /* I */
  vm->IPs[cip].Overloads[10][vm->IPs[cip].NumOvers]=EX_FPSP+11;  /* K */
  vm->IPs[cip].Overloads[11][vm->IPs[cip].NumOvers]=EX_FPSP+12;  /* L */
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_FPSP+13;  /* M */
  vm->IPs[cip].Overloads[13][vm->IPs[cip].NumOvers]=EX_FPSP+14;  /* N */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_FPSP+00;  /* P */
  vm->IPs[cip].Overloads[16][vm->IPs[cip].NumOvers]=EX_FPSP+15;  /* Q */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_FPSP+01;  /* R */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_FPSP+16;  /* S */
  vm->IPs[cip].Overloads[19][vm->IPs[cip].NumOvers]=EX_FPSP+17;  /* T */
  vm->IPs[cip].Overloads[21][vm->IPs[cip].NumOvers]=EX_FPSP+18;  /* V */
  vm->IPs[cip].Overloads[23][vm->IPs[cip].NumOvers]=EX_FPSP+19;  /* X */
  vm->IPs[cip].Overloads[24][vm->IPs[cip].NumOvers]=EX_FPSP+20;  /* Y */
}

void Unload_FPSP(VM* vm) {
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,1);
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,4);
  Unload_Semantic(vm,5);
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,7);
  Unload_Semantic(vm,8);
  Unload_Semantic(vm,10);
  Unload_Semantic(vm,11);
  Unload_Semantic(vm,12);
  Unload_Semantic(vm,13);
  Unload_Semantic(vm,15);
  Unload_Semantic(vm,16);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,19);
  Unload_Semantic(vm,21);
  Unload_Semantic(vm,23);
  Unload_Semantic(vm,24);
  }

void Do_FPSP(VM* vm,int Cmd)
{
  INT a;
  float fa,fb;
  char Buffer[1000];
  union {
    float f;
    long int i;
    } FpSp;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_FPSP+00:FpSp.i=Pop(vm);                           /* FPSP, P */
                    printf("%f ",FpSp.f); break;
    case EX_FPSP+01:Pop_String(vm,Buffer);                    /* FPSP, R */
                    sscanf(Buffer,"%f",&FpSp.f);
                    Push(vm,FpSp.i); break;
    case EX_FPSP+02:FpSp.i=Pop(vm); fb=FpSp.f;                /* FPSP, A */
                    FpSp.i=Pop(vm); fa=FpSp.f;
                    FpSp.f=fa+fb;
                    Push(vm,FpSp.i); break;
    case EX_FPSP+03:FpSp.i=Pop(vm); fb=FpSp.f;                /* FPSP, B */
                    FpSp.f=sin(fb);
                    Push(vm,FpSp.i); break;
    case EX_FPSP+04:FpSp.i=Pop(vm); fb=FpSp.f;                /* FPSP, C */
                    FpSp.f=cos(fb);
                    Push(vm,FpSp.i); break;
    case EX_FPSP+05:FpSp.i=Pop(vm); fb=FpSp.f;                /* FPSP, D */
                    FpSp.i=Pop(vm); fa=FpSp.f;
                    FpSp.f=fa/fb;
                    Push(vm,FpSp.i); break;
    case EX_FPSP+06:FpSp.i=Pop(vm); fb=FpSp.f;                /* FPSP, E */
                    FpSp.f=acos(fb);
                    Push(vm,FpSp.i); break;
    case EX_FPSP+07:a=Pop(vm); FpSp.f=a;                      /* FPSP, F */
                    Push(vm,FpSp.i); break;
    case EX_FPSP+8 :FpSp.i=Pop(vm); fb=FpSp.f;                /* FPSP, G */
                    FpSp.f=atan(fb);
                    Push(vm,FpSp.i); break;
    case EX_FPSP+9 :FpSp.i=Pop(vm); fb=FpSp.f;                /* FPSP, H */
                    FpSp.f=acos(fb);
                    Push(vm,FpSp.i); break;
    case EX_FPSP+10:FpSp.i=Pop(vm); fb=FpSp.f;                /* FPSP, I */
                    Push(vm,floor(fb)); break;
    case EX_FPSP+11:FpSp.i=Pop(vm); fb=FpSp.f;                /* FPSP, K */
                    FpSp.f=log(fb);
                    Push(vm,FpSp.i); break;
    case EX_FPSP+12:FpSp.i=Pop(vm); fb=FpSp.f;                /* FPSP, L */
                    FpSp.f=log10(fb);
                    Push(vm,FpSp.i); break;
    case EX_FPSP+13:FpSp.i=Pop(vm); fb=FpSp.f;                /* FPSP, M */
                    FpSp.i=Pop(vm); fa=FpSp.f;
                    FpSp.f=fa*fb;
                    Push(vm,FpSp.i); break;
    case EX_FPSP+14:FpSp.i=Pop(vm); fb=FpSp.f;                /* FPSP, N */
                    FpSp.f=0-fb;
                    Push(vm,FpSp.i); break;
    case EX_FPSP+15:FpSp.i=Pop(vm); fb=FpSp.f;                /* FPSP, Q */
                    FpSp.f=sqrt(fb);
                    Push(vm,FpSp.i); break;
    case EX_FPSP+16:FpSp.i=Pop(vm); fb=FpSp.f;                /* FPSP, S */
                    FpSp.i=Pop(vm); fa=FpSp.f;
                    FpSp.f=fa-fb;
                    Push(vm,FpSp.i); break;
    case EX_FPSP+17:FpSp.i=Pop(vm); fb=FpSp.f;                /* FPSP, T */
                    FpSp.f=tan(fb);
                    Push(vm,FpSp.i); break;
    case EX_FPSP+18:FpSp.i=Pop(vm); fb=FpSp.f;                /* FPSP, V */
                    FpSp.f=fabs(fb);
                    Push(vm,FpSp.i); break;
    case EX_FPSP+19:FpSp.i=Pop(vm); fb=FpSp.f;                /* FPSP, X */
                    FpSp.f=exp(fb);
                    Push(vm,FpSp.i); break;
    case EX_FPSP+20:FpSp.i=Pop(vm); fb=FpSp.f;                /* FPSP, Z */
                    FpSp.i=Pop(vm); fa=FpSp.f;
                    FpSp.f=pow(fa,fb);
                    Push(vm,FpSp.i); break;

    }
}
#endif

