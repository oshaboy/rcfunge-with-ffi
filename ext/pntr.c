/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef PNTR
#include <time.h>
#include "funge.h"

void Load_PNTR(long int FingerPrint,INT cip)
{
  INT  i;
  IPs[cip].NumOvers++;
  for (i=0;i<26;i++) IPs[cip].Overloads[i][IPs[cip].NumOvers]=0;
  IPs[cip].OverFinger[IPs[cip].NumOvers]=FingerPrint;
  Push(FingerPrint,cip); Push(1,cip);
  IPs[cip].Overloads[6][IPs[cip].NumOvers]=EX_PNTR+00;   /* G */
  IPs[cip].Overloads[15][IPs[cip].NumOvers]=EX_PNTR+01;  /* P */
  IPs[cip].Overloads[21][IPs[cip].NumOvers]=EX_PNTR+02;  /* V */
  IPs[cip].Overloads[22][IPs[cip].NumOvers]=EX_PNTR+03;  /* W */
}

void Unload_PNTR(INT cip) {
  Unload_Semantic(cip,6);
  Unload_Semantic(cip,15);
  Unload_Semantic(cip,21);
  Unload_Semantic(cip,22);
  }

void Do_PNTR(int Cmd,INT cip)
{
  INT x,y,z;
  INT a,b,c;
  switch (Cmd) {
    case EX_PNTR+00:if (Mode>2) z=Pop(cip); else z=0;     /* PNTR, G */
                    if (Mode>1) y=Pop(cip); else y=0;
                    x=Pop(cip);
                    if (Mode>2) c=Get_Funge(x++,y,z); else c=0;
                    if (Mode>1) b=Get_Funge(x++,y,z); else b=0;
                    a=Get_Funge(x,y,z);
                    Push(Get_Funge(a,b,c),cip); break;
    case EX_PNTR+01:if (Mode>2) z=Pop(cip); else z=0;     /* PNTR, P */
                    if (Mode>1) y=Pop(cip); else y=0;
                    x=Pop(cip);
                    if (Mode>2) c=Get_Funge(x++,y,z); else c=0;
                    if (Mode>1) b=Get_Funge(x++,y,z); else b=0;
                    a=Get_Funge(x,y,z);
                    Put_Funge(a,b,c,Pop(cip)); break;
    case EX_PNTR+02:if (Mode>2) z=Pop(cip); else z=0;     /* PNTR, V */
                    if (Mode>1) y=Pop(cip); else y=0;
                    x=Pop(cip);
                    if (Mode>2) c=Get_Funge(x++,y,z); else c=0;
                    if (Mode>1) b=Get_Funge(x++,y,z); else b=0;
                    a=Get_Funge(x,y,z);
                    Push(Get_Funge(a++,b,c),cip);
                    if (Mode>1) Push(Get_Funge(a++,b,c),cip);
                    if (Mode>2) Push(Get_Funge(a++,b,c),cip);
                    break;
    case EX_PNTR+03:if (Mode>2) z=Pop(cip); else z=0;     /* PNTR, W */
                    if (Mode>1) y=Pop(cip); else y=0;
                    x=Pop(cip);
                    if (Mode>2) c=Get_Funge(x++,y,z); else c=0;
                    if (Mode>1) b=Get_Funge(x++,y,z); else b=0;
                    a=Get_Funge(x,y,z);
                    Put_Funge(a++,b,c,Pop(cip));
                    if (Mode>1) Put_Funge(a++,b,c,Pop(cip));
                    if (Mode>2) Put_Funge(a++,b,c,Pop(cip));
                    break;
    }
}
#endif

