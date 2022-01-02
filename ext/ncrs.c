/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef NCRS
#include <time.h>
#include <curses.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_NCRS(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[1][vm->IPs[cip].NumOvers]=EX_NCRS+ 1;   /* B */
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_NCRS+ 2;   /* C */
  vm->IPs[cip].Overloads[4][vm->IPs[cip].NumOvers]=EX_NCRS+ 4;   /* E */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_NCRS+ 6;   /* G */
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_NCRS+ 8;   /* I */
  vm->IPs[cip].Overloads[10][vm->IPs[cip].NumOvers]=EX_NCRS+10;  /* K */
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_NCRS+12;  /* M */
  vm->IPs[cip].Overloads[13][vm->IPs[cip].NumOvers]=EX_NCRS+13;  /* N */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_NCRS+15;  /* P */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_NCRS+17;  /* R */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_NCRS+18;  /* S */
  vm->IPs[cip].Overloads[20][vm->IPs[cip].NumOvers]=EX_NCRS+20;  /* U */
}

void Unload_NCRS(VM* vm) {
  Unload_Semantic(vm,1);
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,4);
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,8);
  Unload_Semantic(vm,10);
  Unload_Semantic(vm,12);
  Unload_Semantic(vm,13);
  Unload_Semantic(vm,15);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,20);
  }

void Do_NCRS(VM* vm,int Cmd)
{
  int i,x,y;
  int cip;
  char buffer[1000];
  cip = vm->cip;
  switch (Cmd) {
    case EX_NCRS+ 1:beep(); break;                       /* NCRS, B */
    case EX_NCRS+ 2:i=Pop(vm);                           /* NCRS, C */
                    if (i != 0 && i != 1 && i != 2) { 
                      Reflect(vm);
                      return;
                      }
                    if (i==0) i=clear();
                      else if (i==1) i=clrtoeol();
                      else i=clrtobot();
                    if (i==ERR) {
                      Reflect(vm);
                      }
                    break;
    case EX_NCRS+ 4:i=Pop(vm);                           /* NCRS, E */
                    if (i != 0 && i != 1) {
                      Reflect(vm);
                      return;
                      }
                    if (i == 0) i=noecho();
                      else i=echo();
                    if (i==ERR) {
                      Reflect(vm);
                      }
                    break;
    case EX_NCRS+ 6:i=getch();                           /* NCRS, G */
                    if (i==ERR) {
                      Reflect(vm);
                      return;
                      }
                    Push(vm,i);
                    break;
    case EX_NCRS+ 8:i=Pop(vm);                           /* NCRS, I */
                    if (i==1) {
                      if (initscr() == NULL) {
                        Reflect(vm);
                        return;
                        }
                      }
                      else i=endwin();
                    if (i==ERR) {
                      Reflect(vm);
                      }
                    break;
    case EX_NCRS+10:i=Pop(vm);                           /* NCRS, K */
                    if (i != 0 && i != 1) {
                      Reflect(vm);
                      return;
                      }
                    if (i == 0) i=keypad(stdscr,FALSE);
                      else i=keypad(stdscr,TRUE);
                    if (i==ERR) {
                      Reflect(vm);
                      }
                    break;
    case EX_NCRS+12:y=Pop(vm);                           /* NCRS, M */
                    x=Pop(vm);
                    i=move(y,x);
                    if (i==ERR) {
                      Reflect(vm);
                      }
                    break;
    case EX_NCRS+13:i=Pop(vm);                           /* NCRS, N */
                    if (i != 0 && i != 1) {
                      Reflect(vm);
                      return;
                      }
                    if (i == 0) i=cbreak();
                      else i=nocbreak();
                    if (i==ERR) {
                      Reflect(vm);
                      }
                    break;
    case EX_NCRS+15:i=Pop(vm);                           /* NCRS, P */
                    i=addch(i);
                    if (i==ERR) {
                      Reflect(vm);
                      return;
                      }
                    break;
    case EX_NCRS+17:i=refresh();                         /* NCRS, R */
                    if (i==ERR) {
                      Reflect(vm);
                      return;
                      }
                    break;
    case EX_NCRS+18:Pop_String(vm,buffer);               /* NCRS, S */
                    i=printw("%s",buffer);
                    if (i==ERR) {
                      Reflect(vm);
                      return;
                      }
                    break;
    case EX_NCRS+20:i=Pop(vm);                           /* NCRS, U */
                    i=ungetch(i);
                    if (i==ERR) {
                      Reflect(vm);
                      return;
                      }
                    break;
    }
}
#endif

