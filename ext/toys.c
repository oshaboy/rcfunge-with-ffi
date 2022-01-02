/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef TOYS
#include <time.h>
#include "funge.h"

void Load_TOYS(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_TOYS+11;   /* A */
  vm->IPs[cip].Overloads[1][vm->IPs[cip].NumOvers]=EX_TOYS+19;   /* B */
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_TOYS+ 0;   /* C */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_TOYS+8;    /* D */
  vm->IPs[cip].Overloads[4][vm->IPs[cip].NumOvers]=EX_TOYS+12;   /* E */
  vm->IPs[cip].Overloads[5][vm->IPs[cip].NumOvers]=EX_TOYS+20;   /* F */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_TOYS+21;   /* G */
  vm->IPs[cip].Overloads[7][vm->IPs[cip].NumOvers]=EX_TOYS+10;   /* H */
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_TOYS+7;    /* I */
  vm->IPs[cip].Overloads[9][vm->IPs[cip].NumOvers]=EX_TOYS+22;   /* J */
  vm->IPs[cip].Overloads[10][vm->IPs[cip].NumOvers]=EX_TOYS+1;   /* K */
  vm->IPs[cip].Overloads[11][vm->IPs[cip].NumOvers]=EX_TOYS+5;   /* L */
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_TOYS+2;   /* M */
  vm->IPs[cip].Overloads[13][vm->IPs[cip].NumOvers]=EX_TOYS+9;   /* N */
  vm->IPs[cip].Overloads[14][vm->IPs[cip].NumOvers]=EX_TOYS+23;  /* O */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_TOYS+13;  /* P */
  vm->IPs[cip].Overloads[16][vm->IPs[cip].NumOvers]=EX_TOYS+17;  /* Q */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_TOYS+6;   /* R */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_TOYS+4;   /* S */
  vm->IPs[cip].Overloads[19][vm->IPs[cip].NumOvers]=EX_TOYS+24;  /* T */
  vm->IPs[cip].Overloads[20][vm->IPs[cip].NumOvers]=EX_TOYS+18;  /* U */
  vm->IPs[cip].Overloads[21][vm->IPs[cip].NumOvers]=EX_TOYS+3;   /* V */
  vm->IPs[cip].Overloads[22][vm->IPs[cip].NumOvers]=EX_TOYS+25;  /* W */
  vm->IPs[cip].Overloads[23][vm->IPs[cip].NumOvers]=EX_TOYS+14;  /* X */
  vm->IPs[cip].Overloads[24][vm->IPs[cip].NumOvers]=EX_TOYS+15;  /* Y */
  vm->IPs[cip].Overloads[25][vm->IPs[cip].NumOvers]=EX_TOYS+16;  /* Z */
}

void Unload_TOYS(VM* vm) {
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,1);
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,4);
  Unload_Semantic(vm,5);
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,7);
  Unload_Semantic(vm,8);
  Unload_Semantic(vm,9);
  Unload_Semantic(vm,10);
  Unload_Semantic(vm,11);
  Unload_Semantic(vm,12);
  Unload_Semantic(vm,13);
  Unload_Semantic(vm,14);
  Unload_Semantic(vm,15);
  Unload_Semantic(vm,16);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,19);
  Unload_Semantic(vm,20);
  Unload_Semantic(vm,21);
  Unload_Semantic(vm,22);
  Unload_Semantic(vm,23);
  Unload_Semantic(vm,24);
  Unload_Semantic(vm,25);
  }

void Do_TOYS(VM* vm,int Cmd)
{
  INT i,j;
  INT a,b,c;
  INT x,y,z;
  INT dx,dy,dz;
  INT vx,vy,vz;
  int sx,sy;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_TOYS+00:switch (vm->Mode) {                       /* TOYS, C */
                      case 1:x=Pop(vm);
                             vx=Pop(vm);
                             dx=Pop(vm);
                             for (a=0;a<vx;a++)
                               Put_Funge(vm,dx+a,0,0,Get_Funge(vm,x+a,0,0));
                             break;
                      case 2:dy=Pop(vm); dx=Pop(vm);
                             vy=Pop(vm); vx=Pop(vm);
                             y=Pop(vm); x=Pop(vm);
                             for (b=0;b<vy;b++)
                               for (a=0;a<vx;a++) {
                                 Put_Funge(vm,dx+a,dy+b,0,Get_Funge(vm,x+a,y+b,0));
                                 }
                             break;
                      case 3:dz=Pop(vm); dy=Pop(vm); dx=Pop(vm);
                             vz=Pop(vm); vy=Pop(vm); vx=Pop(vm);
                             z=Pop(vm); y=Pop(vm); x=Pop(vm);
                             for (c=0;c<vz;c++)
                               for (b=0;b<vy;b++)
                                 for (a=0;a<vx;a++)
                                   Put_Funge(vm,dx+a,dy+b,dz+c,Get_Funge(vm,x+a,y+b,z+c));
                             break;
                      }
                      break;
    case EX_TOYS+01:switch (vm->Mode) {                       /* TOYS, K */
                      case 1:dx=Pop(vm);
                             vx=Pop(vm);
                             x=Pop(vm);
                             for (a=vx-1;a>=0;a--)
                               Put_Funge(vm,dx+a,0,0,Get_Funge(vm,x+a,0,0));
                             break;
                      case 2:dy=Pop(vm); dx=Pop(vm);
                             vy=Pop(vm); vx=Pop(vm);
                             y=Pop(vm); x=Pop(vm);
                             for (b=vy-1;b>=0;b--)
                               for (a=vx-1;a>=0;a--)
                                 Put_Funge(vm,dx+a,dy+b,0,Get_Funge(vm,x+a,y+b,0));
                             break;
                      case 3:dz=Pop(vm); dy=Pop(vm); dx=Pop(vm);
                             vz=Pop(vm); vy=Pop(vm); vx=Pop(vm);
                             z=Pop(vm); y=Pop(vm); x=Pop(vm);
                             for (c=vz-1;c>=0;c--)
                               for (b=vy-1;b>=0;b--)
                                 for (a=vx-1;a>=0;a--)
                                   Put_Funge(vm,dx+a,dy+b,dz+c,Get_Funge(vm,x+a,y+b,z+c));
                             break;
                      }
                      break;
    case EX_TOYS+02:switch (vm->Mode) {                       /* TOYS, M */
                      case 1:dx=Pop(vm);
                             vx=Pop(vm);
                             x=Pop(vm);
                             for (a=0;a<vx;a++) {
                               Put_Funge(vm,dx+a,0,0,Get_Funge(vm,x+a,0,0));
                               Put_Funge(vm,x+a,0,0,32);
                               }
                             break;
                      case 2:dy=Pop(vm); dx=Pop(vm);
                             vy=Pop(vm); vx=Pop(vm);
                             y=Pop(vm); x=Pop(vm);
                             for (b=0;b<vy;b++)
                               for (a=0;a<vx;a++) {
                                 Put_Funge(vm,dx+a,dy+b,0,Get_Funge(vm,x+a,y+b,0));
                                 Put_Funge(vm,x+a,y+b,0,32);
                                 }
                             break;
                      case 3:dz=Pop(vm); dy=Pop(vm); dx=Pop(vm);
                             vz=Pop(vm); vy=Pop(vm); vx=Pop(vm);
                             z=Pop(vm); y=Pop(vm); x=Pop(vm);
                             for (c=0;c<vz;c++)
                               for (b=0;b<vy;b++)
                                 for (a=0;a<vx;a++) {
                                   Put_Funge(vm,dx+a,dy+b,dz+c,Get_Funge(vm,x+a,y+b,z+c));
                                   Put_Funge(vm,x+a,y+b,z+c,32);
                                   }
                             break;
                      }
                      break;
    case EX_TOYS+03:switch (vm->Mode) {                       /* TOYS, V */
                      case 1:dx=Pop(vm);
                             vx=Pop(vm);
                             x=Pop(vm);
                             for (a=vx-1;a>=0;a--) {
                               Put_Funge(vm,dx+a,0,0,Get_Funge(vm,x+a,0,0));
                               Put_Funge(vm,x+a,0,0,32);
                               }
                             break;
                      case 2:dy=Pop(vm); dx=Pop(vm);
                             vy=Pop(vm); vx=Pop(vm);
                             y=Pop(vm); x=Pop(vm);
                             for (b=vy-1;b>=0;b--)
                               for (a=vx-1;a>=0;a--) {
                                 Put_Funge(vm,dx+a,dy+b,0,Get_Funge(vm,x+a,y+b,0));
                                 Put_Funge(vm,x+a,y+b,0,32);
                                 }
                             break;
                      case 3:dz=Pop(vm); dy=Pop(vm); dx=Pop(vm);
                             vz=Pop(vm); vy=Pop(vm); vx=Pop(vm);
                             z=Pop(vm); y=Pop(vm); x=Pop(vm);
                             for (c=vz-1;c>=0;c--)
                               for (b=vy-1;b>=0;b--)
                                 for (a=vx-1;a>=0;a--) {
                                   Put_Funge(vm,dx+a,dy+b,dz+c,Get_Funge(vm,x+a,y+b,z+c));
                                   Put_Funge(vm,x+a,y+b,z+c,32);
                                   }
                             break;
                      }
                      break;
    case EX_TOYS+04:switch (vm->Mode) {                       /* TOYS, S */
                      case 1:x=Pop(vm);
                             vx=Pop(vm);
                             j=Pop(vm);
                             for (a=0;a<vx;a++)
                               Put_Funge(vm,x+a,0,0,j);
                             break;
                      case 2:y=Pop(vm); x=Pop(vm);
                             vy=Pop(vm); vx=Pop(vm);
                             j=Pop(vm);
                             for (b=0;b<vy;b++)
                               for (a=0;a<vx;a++)
                                 Put_Funge(vm,x+a,y+b,0,j);
                             break;
                      case 3:z=Pop(vm); y=Pop(vm); x=Pop(vm);
                             vz=Pop(vm); vy=Pop(vm); vx=Pop(vm);
                             j=Pop(vm);
                             for (c=0;c<vz;c++)
                               for (b=0;b<vy;b++)
                                 for (a=0;a<vx;a++)
                                   Put_Funge(vm,x+a,y+b,z+c,j);
                             break;
                      }
                      break;
    case EX_TOYS+05:y=-vm->IPs[cip].DeltaX;                   /* TOYS, L */
                    x=vm->IPs[cip].DeltaY;
                    Push(vm,Get_Funge(vm,vm->IPs[cip].x+x,vm->IPs[cip].y+y,vm->IPs[cip].z));
                    break;
    case EX_TOYS+06:y=vm->IPs[cip].DeltaX;                   /* TOYS, R */
                    x=-vm->IPs[cip].DeltaY;
                    Push(vm,Get_Funge(vm,vm->IPs[cip].x+x,vm->IPs[cip].y+y,vm->IPs[cip].z));
                    break;
    case EX_TOYS+07:Push(vm,Pop(vm)+1); break;          /* TOYS, I */
    case EX_TOYS+8 :Push(vm,Pop(vm)-1); break;          /* TOYS, I */
    case EX_TOYS+9 :Push(vm,0-Pop(vm)); break;          /* TOYS, N */
    case EX_TOYS+10:b=Pop(vm); a=Pop(vm);               /* TOYS, H */
                   if (b>=0) Push(vm,a<<b); else Push(vm,a>>abs(b));
                   break;
    case EX_TOYS+11:b=Pop(vm); a=Pop(vm);               /* TOYS, A */
                   for (i=0;i<b;i++) Push(vm,a);
                   break;
    case EX_TOYS+12:a=0;                                  /* TOYS, E */
                   while (vm->IPs[cip].StackPtr>0) a+=Pop(vm);
                   Push(vm,a);
                   break;
    case EX_TOYS+13:a=1;                                  /* TOYS, E */
                   while (vm->IPs[cip].StackPtr>0) a*=Pop(vm);
                   Push(vm,a);
                   break;
    case EX_TOYS+14:vm->IPs[cip].DeltaX++; break;             /* TOYS, X */
    case EX_TOYS+15:vm->IPs[cip].DeltaY++; break;             /* TOYS, Y */
    case EX_TOYS+16:if (vm->Mode>2)                           /* TOYS, Z */
                      vm->IPs[cip].DeltaZ++;
                    else Reflect(vm);
                   break;
    case EX_TOYS+17:a=Pop(vm);                           /* TOYS, Q */
                   Sub_Delta(vm);
                   Put_Funge(vm,vm->IPs[cip].x,vm->IPs[cip].y,vm->IPs[cip].z,a);
                   Add_Delta(vm);
                   break;
    case EX_TOYS+18:switch (vm->Mode) {                       /* TOYS, U */
                     case 1:a=rnd(2); break;
                     case 2:a=rnd(4); break;
                     case 3:a=rnd(6); break;
                     }
                   switch (rnd(a+1)) {
                     case 0:a='<'; break;
                     case 1:a='>'; break;
                     case 2:a='^'; break;
                     case 3:a='v'; break;
                     case 4:a='h'; break;
                     case 5:a='l'; break;
                     }
                   Put_Funge(vm,vm->IPs[cip].x,vm->IPs[cip].y,vm->IPs[cip].z,a);
                   break;
    case EX_TOYS+19:b=Pop(vm);                           /* TOYS, B */
                    a=Pop(vm);
                    Push(vm,a+b);
                    Push(vm,a-b);
                    break;
    case EX_TOYS+20:y=Pop(vm);                           /* TOYS, F */
                    x=Pop(vm);
                    sx=Pop(vm);
                    sy=Pop(vm);
                    for (i=0; i<sy; i++) {
                      for (j=0; j<sx; j++) {
                        a = Pop(vm);
                        Put_Funge(vm,x+j,y+i,0,a);
                        }
                      
                      }
                    break;
    case EX_TOYS+21:y=Pop(vm);                           /* TOYS, G */
                    x=Pop(vm);
                    sy=Pop(vm);
                    sx=Pop(vm);
                    for (i=sx-1; i>=0; i--) {
                      for (j=sy-1; j>=0; j--) {
                        Push(vm,Get_Funge(vm,x+j,y+i,0));
                        }
                      
                      }
                    break;
    case EX_TOYS+22:y=Pop(vm);                           /* TOYS, J */
                    a = vm->dFspace[0].Row;
                    b = vm->dFspace[vm->NumRows-1].Row;
                    while (y > 0) {
                      for (i=b+1; i>=a;i--)
                        Put_Funge(vm,vm->IPs[cip].x,i,0,Get_Funge(vm,vm->IPs[cip].x,i-1,0));
                      y--;
                      }
                    while (y < 0) {
                      for (i=a-1; i<=b+1;i++)
                        Put_Funge(vm,vm->IPs[cip].x,i,0,Get_Funge(vm,vm->IPs[cip].x,i+1,0));
                      y++;
                      }
                    break;
    case EX_TOYS+23:sy=Pop(vm);                          /* TOYS, O */
                    a = vm->dFspace[0].Row;
                    b = vm->dFspace[vm->NumRows-1].Row;
                    while (sy<0) {
                      i = Find_Row(vm,vm->IPs[cip].y,0);
                      for (x=vm->dFspace[i].Min-1; x<=vm->dFspace[i].Max; x++) {
                        Put_Funge(vm,x,vm->IPs[cip].y,0,Get_Funge(vm,x+1,vm->IPs[cip].y,0));
                        }
                      sy++;
                      }
                    while (sy>0) {
                      i = Find_Row(vm,vm->IPs[cip].y,0);
                      for (x=vm->dFspace[i].Max+1; x>=vm->dFspace[i].Min; x--) {
                        Put_Funge(vm,x,vm->IPs[cip].y,0,Get_Funge(vm,x-1,vm->IPs[cip].y,0));
                        }
                      sy--;
                      }
    case EX_TOYS+24:sy=Pop(vm);                          /* TOYS, T */
                    if (sy == 0) {
                      if (Pop(vm)==0) {
                        if (vm->IPs[cip].HoverMode==0) {
                          vm->IPs[cip].DeltaX=1; vm->IPs[cip].DeltaY=0; vm->IPs[cip].DeltaZ=0;
                          } else vm->IPs[cip].DeltaX++;
                        } else {
                        if (vm->IPs[cip].HoverMode==0) {
                          vm->IPs[cip].DeltaX=-1; vm->IPs[cip].DeltaY=0; vm->IPs[cip].DeltaZ=0;
                          } else vm->IPs[cip].DeltaX--;
                        }
                      }
                    if (sy == 1) {
                      if (vm->Mode == 0) {
                        Reflect(vm);
                        return;
                        }
                      if (Pop(vm)==0) {
                        if (vm->IPs[cip].HoverMode==0) {
                          vm->IPs[cip].DeltaX=0; vm->IPs[cip].DeltaY=1; vm->IPs[cip].DeltaZ=0;
                          } else vm->IPs[cip].DeltaY++;
                        } else {
                        if (vm->IPs[cip].HoverMode==0) {
                          vm->IPs[cip].DeltaX=0; vm->IPs[cip].DeltaY=-1; vm->IPs[cip].DeltaZ=0;
                          } else vm->IPs[cip].DeltaY--;
                        }
                      }
                    if (sy == 2) {
                      if (vm->Mode>2) {
                        if (Pop(vm)==0) {
                          vm->IPs[cip].DeltaX=0; vm->IPs[cip].DeltaY=0; vm->IPs[cip].DeltaZ=-1;
                          } else {
                          vm->IPs[cip].DeltaX=0; vm->IPs[cip].DeltaY=0; vm->IPs[cip].DeltaZ=1;
                          }
                        } else Reflect(vm);
                      }
                    if (sy < 0 || sy > 2) Reflect(vm);
                    break;
    case EX_TOYS+25:if (vm->Mode == 1) {                      /* TOYS, W */
                      vx=Pop(vm);
                      vy = 0;
                      vz = 0;
                      }
                    if (vm->Mode == 2) {
                      vy=Pop(vm);
                      vx=Pop(vm);
                      vz = 0;
                      }
                    if (vm->Mode == 3) {
                      vz=Pop(vm);
                      vy=Pop(vm);
                      vx=Pop(vm);
                      }
                    i = Pop(vm);
                    a = Get_Funge(vm,vx,vy,vz);
                    if (a < i) {
                      Push(vm,i);
                      if (vm->Mode == 3) Push(vm,vz);
                      if (vm->Mode == 2) Push(vm,vy);
                      Push(vm,vx);
                      Sub_Delta(vm);
                      }
                    if (a > i) {
                      Reflect(vm);
                      }
                    break;

    }
}
#endif

