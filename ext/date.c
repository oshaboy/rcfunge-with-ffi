/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef DATE
#include <time.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_DATE(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_DATE+ 0;   /* A */
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_DATE+ 2;   /* C */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_DATE+ 3;   /* D */
  vm->IPs[cip].Overloads[9][vm->IPs[cip].NumOvers]=EX_DATE+ 9;   /* J */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_DATE+18;  /* S */
  vm->IPs[cip].Overloads[19][vm->IPs[cip].NumOvers]=EX_DATE+19;  /* T */
  vm->IPs[cip].Overloads[22][vm->IPs[cip].NumOvers]=EX_DATE+22;  /* W */
  vm->IPs[cip].Overloads[24][vm->IPs[cip].NumOvers]=EX_DATE+24;  /* Y */
}

int DATE_cal_to_jd(int m,int d,int y) {
  int j;
  int a;
  if (y<0) y++;
  a = floor((double)((14-m)/12));
  y = y+4800-a;
  m = m+12*a-3;
  j = d+floor((double)((153*m+2)/5))+365*y
       +floor((double)(y/4))
       -floor((double)(y/100))
       +floor((double)(y/400))
       -32045;
  if (j<0) j--;
  return j;
  }

void DATE_jd_to_cal(int jd,int* mo,int* dy,int* yr) {
/*
  int j;
  int g;
  int dg;
  int c;
  int dc;
  int b;
  int db;
  int a;
  int da;
  j = jd+32044;
  g = j/146097;
  dg = j%146097;
  c = (dg / 36524+1) * 3/4;
  dc = dg - c*36524;
  b = dc / 1461;
  db = dc % 1461;
  a = (db / 365 +1) * 3/4;
  da = db - a*365;
  *yr = g*400+c*100+b*4+a;
  *mo = (da*5+308)/153 -2;
  *dy = da-(*mo+4)*153/5+122;
  *yr=*yr-4800+(*mo+2)/12;
  *mo=(*mo+2)%12+1;
  *dy=*dy+1;
*/

  int l,n,i,j;
  l=68569+jd;
  n=floor((double)(4*l/146097.0));
  l=l-floor((double)((146097*n+3)/4.0));
  i=floor((double)(4000*(l+1)/1461001.0));
  l=l-floor((double)(1461*i/4.0))+31;
  j=floor((double)(80*l/2447.0));
  *dy=floor(l-floor((double)(2447*j/80.0)));
  l=floor((double)(j/11.0));
  *mo=floor(j+2-12*l);
  *yr=floor(100*(n-49)+i+l);
if (*yr <= 0) *yr -= 1;
  }

void Unload_DATE(VM* vm) {
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,9);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,19);
  Unload_Semantic(vm,22);
  Unload_Semantic(vm,24);
  }

int days_in_year(int y) {
  if (y%4 != 0) return 365;
  if (y%400 == 0) return 366;
  if (y%100 == 0) return 365;
  return 366;
  }

void Do_DATE(VM* vm,int Cmd) {
  int m,d,y,j;
  int m2,d2,y2,j2;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_DATE+ 0:d2=Pop(vm);                          /* DATE, A */
                    d=Pop(vm);
                    m=Pop(vm);
                    y=Pop(vm);
                    j = DATE_cal_to_jd(m,d,y) + d2;
                    DATE_jd_to_cal(j,&m,&d,&y);
                    Push(vm,y);
                    Push(vm,m);
                    Push(vm,d);
                    break;
    case EX_DATE+ 2:j=Pop(vm);                           /* DATE, C */
                    DATE_jd_to_cal(j,&m,&d,&y);
                    Push(vm,y);
                    Push(vm,m);
                    Push(vm,d);
                    break;
    case EX_DATE+ 3:d=Pop(vm);                           /* DATE, D */
                    m=Pop(vm);
                    y=Pop(vm);
                    d2=Pop(vm);
                    m2=Pop(vm);
                    y2=Pop(vm);
                    j = DATE_cal_to_jd(m,d,y);
                    j2 = DATE_cal_to_jd(m2,d2,y2);
                    Push(vm,j2-j);
                    break;
    case EX_DATE+ 9:d=Pop(vm);                           /* DATE, J */
                    m=Pop(vm);
                    y=Pop(vm);
                    if (d<=0 || m<=1 || m>12 || y == 0) {
                      Reflect(vm);
                      return; 
                      }
                    j = DATE_cal_to_jd(m,d,y);
                    Push(vm,j);
                    break;
    case EX_DATE+19:d=Pop(vm);                           /* DATE, T */
                    y=Pop(vm);
                    if (d > days_in_year(y)) {
                      Reflect(vm);
                      return;
                      }
                    j = DATE_cal_to_jd(1,1,y) + d;
                    DATE_jd_to_cal(j,&m,&d,&y);
                    Push(vm,y);
                    Push(vm,m);
                    Push(vm,d);
                    break;
    case EX_DATE+22:d=Pop(vm);                           /* DATE, W */
                    m=Pop(vm);
                    y=Pop(vm);
                    j = DATE_cal_to_jd(m,d,y);
                    Push(vm,(j % 7));
                    break;
    case EX_DATE+24:d=Pop(vm);                           /* DATE, Y */
                    m=Pop(vm);
                    y=Pop(vm);
                    if (d<=0 || m<=1 || m>12 || y==0) {
                      Reflect(vm);
                      return;
                      }
                    Push(vm,DATE_cal_to_jd(m,d,y)-DATE_cal_to_jd(1,1,y));
                    break;
    }
}
#endif

