/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef FIXP
#include <time.h>
#include "funge.h"

void Load_FIXP(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_FIXP+00;    /* A */
  vm->IPs[cip].Overloads[1][vm->IPs[cip].NumOvers]=EX_FIXP+13;    /* B */
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_FIXP+10;    /* C */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_FIXP+01;    /* D */
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_FIXP+11;    /* I */
  vm->IPs[cip].Overloads[9][vm->IPs[cip].NumOvers]=EX_FIXP+14;    /* J */
  vm->IPs[cip].Overloads[13][vm->IPs[cip].NumOvers]=EX_FIXP+02;   /* N */
  vm->IPs[cip].Overloads[14][vm->IPs[cip].NumOvers]=EX_FIXP+03;   /* O */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_FIXP+04;   /* P */
  vm->IPs[cip].Overloads[16][vm->IPs[cip].NumOvers]=EX_FIXP+05;   /* Q */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_FIXP+06;   /* R */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_FIXP+07;   /* S */
  vm->IPs[cip].Overloads[19][vm->IPs[cip].NumOvers]=EX_FIXP+12;   /* T */
  vm->IPs[cip].Overloads[20][vm->IPs[cip].NumOvers]=EX_FIXP+15;   /* U */
  vm->IPs[cip].Overloads[21][vm->IPs[cip].NumOvers]=EX_FIXP+8;    /* V */
  vm->IPs[cip].Overloads[23][vm->IPs[cip].NumOvers]=EX_FIXP+9;    /* X */
}

void Unload_FIXP(VM* vm) {
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,1);
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,8);
  Unload_Semantic(vm,9);
  Unload_Semantic(vm,13);
  Unload_Semantic(vm,14);
  Unload_Semantic(vm,15);
  Unload_Semantic(vm,16);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,19);
  Unload_Semantic(vm,20);
  Unload_Semantic(vm,21);
  Unload_Semantic(vm,23);
  }

void Do_FIXP(VM* vm,int Cmd)
{
  INT a,b;
  double r;
  switch (Cmd) {
    case EX_FIXP+00:Push(vm,Pop(vm)&Pop(vm)); break;     /* FIXP, A */
    case EX_FIXP+01:Push(vm,rnd(Pop(vm))); break;        /* FIXP, D */
    case EX_FIXP+02:Push(vm,0-Pop(vm)); break;           /* FIXP, N */
    case EX_FIXP+03:Push(vm,Pop(vm)|Pop(vm)); break;     /* FIXP, O */
    case EX_FIXP+04:a=Pop(vm);                           /* FIXP, P */
                    r = a;
                    r/=10000;
                    r*=3.14159265;
                    Push(vm,(INT)(r*10000));
                    break;
    case EX_FIXP+05:Push(vm,(INT)sqrt(Pop(vm))); break; /* FIXP, Q */
    case EX_FIXP+06:b=Pop(vm); a=Pop(vm);               /* FIXP, R */
                    Push(vm,(INT)pow(a,b)); break;
    case EX_FIXP+07:Push(vm,sgn(Pop(vm))); break;       /* FIXP, S */
    case EX_FIXP+8 :Push(vm,abs(Pop(vm))); break;       /* FIXP, V */
    case EX_FIXP+9 :Push(vm,Pop(vm)^Pop(vm)); break;    /* FIXP, X */
    case EX_FIXP+10:a=Pop(vm);                           /* FIXP, C */
                    r=a; r/=10000;
                    r=cos(r*3.14159265/180)*10000;
                    Push(vm,(INT)r); break;
    case EX_FIXP+11:a=Pop(vm);                           /* FIXP, I */
                    r=a; r/=10000;
                    r=sin(r*3.14159265/180)*10000;
                    Push(vm,(INT)r); break;
    case EX_FIXP+12:a=Pop(vm);                           /* FIXP, T */
                    r=a; r/=10000;
                    r=tan(r*3.14159265/180)*10000;
                    Push(vm,(INT)r); break;
    case EX_FIXP+13:a=Pop(vm);                           /* FIXP, B */
                    r=a; r/=10000;
                    r=acos(r)*(180/3.14159265);
                    Push(vm,(INT)(r*10000)); break;
    case EX_FIXP+14:a=Pop(vm);                           /* FIXP, J */
                    r=a; r/=10000;
                    r=asin(r)*(180/3.14159265);
                    Push(vm,(INT)(r*10000)); break;
    case EX_FIXP+15:a=Pop(vm);                           /* FIXP, U */
                    r=a; r/=10000;
                    r=atan(r)*(180/3.14159265);
                    Push(vm,(INT)(r*10000)); break;
    }
}
#endif

