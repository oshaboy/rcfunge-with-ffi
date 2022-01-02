/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef FPDP
#include <time.h>
#include "funge.h"

void Load_FPDP(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_FPDP+2;    /* A */
  vm->IPs[cip].Overloads[1][vm->IPs[cip].NumOvers]=EX_FPDP+3;    /* B */
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_FPDP+4;    /* C */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_FPDP+5;    /* D */
  vm->IPs[cip].Overloads[4][vm->IPs[cip].NumOvers]=EX_FPDP+6;    /* E */
  vm->IPs[cip].Overloads[5][vm->IPs[cip].NumOvers]=EX_FPDP+7;    /* F */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_FPDP+8;    /* G */
  vm->IPs[cip].Overloads[7][vm->IPs[cip].NumOvers]=EX_FPDP+9;    /* H */
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_FPDP+10;   /* I */
  vm->IPs[cip].Overloads[10][vm->IPs[cip].NumOvers]=EX_FPDP+11;  /* K */
  vm->IPs[cip].Overloads[11][vm->IPs[cip].NumOvers]=EX_FPDP+12;  /* L */
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_FPDP+13;  /* M */
  vm->IPs[cip].Overloads[13][vm->IPs[cip].NumOvers]=EX_FPDP+14;  /* N */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_FPDP+00;  /* P */
  vm->IPs[cip].Overloads[16][vm->IPs[cip].NumOvers]=EX_FPDP+15;  /* Q */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_FPDP+01;  /* R */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_FPDP+16;  /* S */
  vm->IPs[cip].Overloads[19][vm->IPs[cip].NumOvers]=7417;        /* T */
  vm->IPs[cip].Overloads[21][vm->IPs[cip].NumOvers]=7418;        /* V */
  vm->IPs[cip].Overloads[23][vm->IPs[cip].NumOvers]=7419;        /* X */
  vm->IPs[cip].Overloads[24][vm->IPs[cip].NumOvers]=7420;        /* Y */
}

void Unload_FPDP(VM* vm) {
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


void Do_FPDP(VM* vm,int Cmd)
{
  int a;
  double da,db;
  char Buffer[1000];
/*
  union {
    double f;
    struct { long int l; long int h; } i;
    } FpDp;
*/
  union {
    double f;
    struct { int l; int h; } i;
    } FpDp;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_FPDP+00:FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); /* FPSP, P */
                    printf("%f ",FpDp.f); break;
    case EX_FPDP+01:Pop_String(vm,Buffer);              /* FPDP, R */
                    sscanf(Buffer,"%lf",&FpDp.f);
                    Push(vm,FpDp.i.h); Push(vm,FpDp.i.l); break;
    case EX_FPDP+02:FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); /* FPDP, A */
                    db=FpDp.f;
                    FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); da=FpDp.f;
                    FpDp.f=da+db;
                    Push(vm,FpDp.i.h); Push(vm,FpDp.i.l); break;
    case EX_FPDP+03:FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); /* FPDP, B */
                    db=FpDp.f;
                    FpDp.f=sin(db);
                    Push(vm,FpDp.i.h); Push(vm,FpDp.i.l); break;
    case EX_FPDP+04:FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); /* FPDP, C */
                    db=FpDp.f;
                    FpDp.f=cos(db);
                    Push(vm,FpDp.i.h); Push(vm,FpDp.i.l); break;
    case EX_FPDP+05:FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); /* FPDP, D */
                    db=FpDp.f;
                    FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); da=FpDp.f;
                    FpDp.f=da/db;
                    Push(vm,FpDp.i.h); Push(vm,FpDp.i.l); break;
    case EX_FPDP+06:FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); /* FPDP, E */
                    db=FpDp.f;
                    FpDp.f=asin(db);
                    Push(vm,FpDp.i.h); Push(vm,FpDp.i.l); break;
    case EX_FPDP+07:a=Pop(vm); FpDp.f=a;                      /* FPDP, F */
                    Push(vm,FpDp.i.h); Push(vm,FpDp.i.l); break;
    case EX_FPDP+8 :FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); /* FPDP, G */
                    db=FpDp.f;
                    FpDp.f=atan(db);
                    Push(vm,FpDp.i.h); Push(vm,FpDp.i.l); break;
    case EX_FPDP+9 :FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); /* FPDP, H */
                    db=FpDp.f;
                    FpDp.f=acos(db);
                    Push(vm,FpDp.i.h); Push(vm,FpDp.i.l); break;
    case EX_FPDP+10:FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); /* FPDP, I */
                    db=FpDp.f;
                    Push(vm,floor(db)); break;
    case EX_FPDP+11:FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); /* FPDP, K */
                    db=FpDp.f;
                    FpDp.f=log(db);
                    Push(vm,FpDp.i.h); Push(vm,FpDp.i.l); break;
    case EX_FPDP+12:FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); /* FPDP, L */
                    db=FpDp.f;
                    FpDp.f=log10(db);
                    Push(vm,FpDp.i.h); Push(vm,FpDp.i.l); break;
    case EX_FPDP+13:FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); /* FPDP, M */
                    db=FpDp.f;
                    FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); da=FpDp.f;
                    FpDp.f=da*db;
                    Push(vm,FpDp.i.h); Push(vm,FpDp.i.l); break;
    case EX_FPDP+14:FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); /* FPDP, N */
                    db=FpDp.f;
                    FpDp.f=0-db;
                    Push(vm,FpDp.i.h); Push(vm,FpDp.i.l); break;
    case EX_FPDP+15:FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); /* FPDP, Q */
                    db=FpDp.f;
                    FpDp.f=sqrt(db);
                    Push(vm,FpDp.i.h); Push(vm,FpDp.i.l); break;
    case EX_FPDP+16:FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); /* FPDP, S */
                    db=FpDp.f;
                    FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); da=FpDp.f;
                    FpDp.f=da-db;
                    Push(vm,FpDp.i.h); Push(vm,FpDp.i.l); break;
    case EX_FPDP+17:FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); /* FPDP, T */
                    db=FpDp.f;
                    FpDp.f=tan(db);
                    Push(vm,FpDp.i.h); Push(vm,FpDp.i.l); break;
    case EX_FPDP+18:FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); /* FPDP, V */
                    db=FpDp.f;
                    FpDp.f=fabs(db);
                    Push(vm,FpDp.i.h); Push(vm,FpDp.i.l); break;
    case EX_FPDP+19:FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); /* FPDP, X */
                    db=FpDp.f;
                    FpDp.f=exp(db);
                    Push(vm,FpDp.i.h); Push(vm,FpDp.i.l); break;
    case EX_FPDP+20:FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); /* FPDP, Y */
                    db=FpDp.f;
                    FpDp.i.l=Pop(vm); FpDp.i.h=Pop(vm); da=FpDp.f;
                    FpDp.f=pow(da,db);
                    Push(vm,FpDp.i.h); Push(vm,FpDp.i.l); break;

    }
}
#endif

