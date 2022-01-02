/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_DYFP(IP* ip) {
  ip->Overloads[1][0]=EX_DYFP+ 1;   /* B */
  ip->Overloads[2][0]=EX_DYFP+ 2;   /* C */
  ip->Overloads[3][0]=EX_DYFP+ 3;   /* D */
  ip->Overloads[4][0]=EX_DYFP+ 4;   /* E */
  ip->Overloads[5][0]=EX_DYFP+ 5;   /* F */
  ip->Overloads[6][0]=EX_DYFP+ 6;   /* G */
  ip->Overloads[8][0]=EX_DYFP+ 8;   /* I */
  ip->Overloads[10][0]=EX_DYFP+10;  /* K */
  ip->Overloads[11][0]=EX_DYFP+11;  /* L */
  ip->Overloads[12][0]=EX_DYFP+12;  /* M */
  ip->Overloads[13][0]=EX_DYFP+13;  /* N */
  ip->Overloads[14][0]=EX_DYFP+14;  /* O */
  ip->Overloads[15][0]=EX_DYFP+15;  /* P */
  ip->Overloads[16][0]=EX_DYFP+16;  /* Q */
  ip->Overloads[17][0]=EX_DYFP+17;  /* R */
  ip->Overloads[18][0]=EX_DYFP+18;  /* S */
  ip->Overloads[19][0]=EX_DYFP+19;  /* T */
  ip->Overloads[23][0]=EX_DYFP+23;  /* X */
  ip->Overloads[24][0]=EX_DYFP+24;  /* Y */
}

void Do_DYFP(VM* vm,int Cmd)
{
  int cip;
  int x,y,z,i;
  INT v,a,b,c;
  IP  *mip,*fip;
  VECTOR src,siz,dst;
  cip = vm->cip;
  switch (Cmd) {
    case EX_DYFP+ 1:Sub_Delta(vm->Parent);               /* DYFP, B */
                    break;
    case EX_DYFP+ 2:v=Pop(vm);                           /* DYFP, C */
                    if (v == 0) {
                      if (vm->Parent->Mode>2) src.z=Pop(vm); else src.z=0;
                      if (vm->Parent->Mode>1) src.y=Pop(vm); else src.y=0;
                      src.x=Pop(vm);
                      if (vm->Mode>2) dst.z=Pop(vm); else dst.z=0;
                      if (vm->Mode>1) dst.y=Pop(vm); else dst.y=0;
                      dst.x=Pop(vm);
                      if (vm->Parent->Mode>2) siz.z=Pop(vm); else siz.z=1;
                      if (vm->Parent->Mode>1) siz.y=Pop(vm); else siz.y=1;
                      siz.x=Pop(vm);
                      if (vm->Mode<3) siz.z=1;
                      if (vm->Mode<2) siz.y=1;
                      for (z=0; z<siz.z; z++)
                        for (y=0; y<siz.y; y++)
                          for (x=0; x<siz.x; x++) {
                            v = Get_Funge(vm->Parent,x+src.x,y+src.y,z+src.z);
                            Put_Funge(vm,x+dst.x,y+dst.y,z+dst.z,v);
                            }
                      }
                    else {
                      if (vm->Mode>2) src.z=Pop(vm); else src.z=0;
                      if (vm->Mode>1) src.y=Pop(vm); else src.y=0;
                      src.x=Pop(vm);
                      if (vm->Parent->Mode>2) dst.z=Pop(vm); else dst.z=0;
                      if (vm->Parent->Mode>1) dst.y=Pop(vm); else dst.y=0;
                      dst.x=Pop(vm);
                      if (vm->Mode>2) siz.z=Pop(vm); else siz.z=1;
                      if (vm->Mode>1) siz.y=Pop(vm); else siz.y=1;
                      siz.x=Pop(vm);
                      if (vm->Mode<3) siz.z=1;
                      if (vm->Mode<2) siz.y=1;
                      for (z=0; z<siz.z; z++)
                        for (y=0; y<siz.y; y++)
                          for (x=0; x<siz.x; x++) {
                            v = Get_Funge(vm,x+src.x,y+src.y,z+src.z);
                            Put_Funge(vm->Parent,x+dst.x,y+dst.y,z+dst.z,v);
                            }
                      }
                    break;
    case EX_DYFP+ 3:if (vm->Parent->Mode>2) z=Pop(vm);   /* DYFP, D */
                      else z=0;
                    if (vm->Parent->Mode>1) y=Pop(vm);
                      else y=0;
                    x=Pop(vm);
                    vm->Parent->IPs[vm->Parent->cip].DeltaX = x;
                    vm->Parent->IPs[vm->Parent->cip].DeltaY = y;
                    vm->Parent->IPs[vm->Parent->cip].DeltaZ = z;
                    break;
    case EX_DYFP+ 4:Push(vm,vm->IPs[cip].StackPtr);      /* DYFP, E */
                    break;
    case EX_DYFP+ 5:Add_Delta(vm->Parent);               /* DYFP, F */
                    break;
    case EX_DYFP+ 6:if (vm->Parent->Mode>2) z=Pop(vm);   /* DYFP, G */
                      else z=0;
                    if (vm->Parent->Mode>1) y=Pop(vm);
                      else y=0;
                    x=Pop(vm);
                    v=Get_Funge(vm->Parent,x,y,x);
                    Push(vm,v);
                    break;
    case EX_DYFP+ 8:v=Pop(vm);                           /* DYFP, I */
                    fip=&(vm->IPs[cip]);
                    mip=&(vm->Parent->IPs[vm->Parent->cip]);
                    mip->Stack      = fip->Stack;
                    mip->StackPtr   = fip->StackPtr;
                    mip->Stacks     = fip->Stacks;
                    mip->StacksPtrs = fip->StacksPtrs;
                    mip->StacksPtr  = fip->StacksPtr;
                    mip->StacksSize = fip->StacksSize;
                    mip->StackSize = fip->StackSize;
                    Exec(vm->Parent,v,0);
                    fip->Stack      = mip->Stack;
                    fip->StackPtr   = mip->StackPtr;
                    fip->Stacks     = mip->Stacks;
                    fip->StacksPtrs = mip->StacksPtrs;
                    fip->StacksPtr  = mip->StacksPtr;
                    fip->StacksSize = mip->StacksSize;
                    fip->StackSize = mip->StackSize;
                    break;
    case EX_DYFP+10:v=Pop(vm);                           /* DYFP, K */
                    v++;
                    if (v>vm->IPs[cip].StackPtr) Push(vm,0);
                      else Push(vm,vm->IPs[cip].Stack[vm->IPs[cip].StackPtr-v]);
                    break;
    case EX_DYFP+11:if (vm->Parent->Mode>2) z=Pop(vm);   /* DYFP, L */
                      else z=0;
                    if (vm->Parent->Mode>1) y=Pop(vm);
                      else y=0;
                    x=Pop(vm);
                    vm->Parent->IPs[vm->Parent->cip].x = x;
                    vm->Parent->IPs[vm->Parent->cip].y = y;
                    vm->Parent->IPs[vm->Parent->cip].z = z;
                    break;
    case EX_DYFP+12:                                     /* DYFP, M */
                    mip=&(vm->Parent->IPs[vm->Parent->cip]);
                    v = 0;
                    if (mip->StringMode != 0) v |= 1;
                    if (mip->HoverMode != 0)  v |= 2;
                    if (mip->InvertMode != 0) v |= 4;
                    if (mip->QueueMode != 0)  v |= 8;
                    if (mip->SwitchMode != 0) v |= 16;
                    Push(vm,v);
                    break;
    case EX_DYFP+13:Add_Delta(vm->Parent);               /* DYFP, N */
                    v = Get_Cell(vm->Parent);
                    Push(vm->Parent,v);
                    Sub_Delta(vm->Parent);
                    break;
    case EX_DYFP+14:a=Pop(vm);                           /* DYFP, O */
                    a++;
                    if (a>=vm->IPs[cip].StackPtr) Push(vm,0);
                      else {
                        b=vm->IPs[cip].Stack[vm->IPs[cip].StackPtr-a];
                        for (i=vm->IPs[cip].StackPtr-a;i<vm->IPs[cip].StackPtr;i++)
                          vm->IPs[cip].Stack[i]=vm->IPs[cip].Stack[i+1];
                        c=Pop(vm); Push(vm,b);
                        }
                    break;
    case EX_DYFP+15:v=Pop(vm);                           /* DYFP, P */
                    if (vm->Parent->Mode>2) z=Pop(vm);
                      else z=0;
                    if (vm->Parent->Mode>1) y=Pop(vm);
                      else y=0;
                    x=Pop(vm);
                    Put_Funge(vm->Parent,x,y,x,v);
                    break;
    case EX_DYFP+16:                                     /* DYFP, Q */
                    mip=&(vm->Parent->IPs[vm->Parent->cip]);
                    Push(vm,mip->x);
                    if (vm->Parent->Mode>1) Push(vm,mip->y);
                    if (vm->Parent->Mode>2) Push(vm,mip->z);
                    Push(vm,mip->DeltaX);
                    if (vm->Parent->Mode>1) Push(vm,mip->DeltaY);
                    if (vm->Parent->Mode>2) Push(vm,mip->DeltaZ);
                    Push(vm,mip->OffsetX);
                    if (vm->Parent->Mode>1) Push(vm,mip->OffsetY);
                    if (vm->Parent->Mode>2) Push(vm,mip->OffsetZ);
                    break;
    case EX_DYFP+17:Reflect(vm->Parent);                 /* DYFP, B */
                    break;
    case EX_DYFP+18:if (vm->Parent->Mode>2) z=Pop(vm);   /* DYFP, S */
                      else z=0;
                    if (vm->Parent->Mode>1) y=Pop(vm);
                      else y=0;
                    x=Pop(vm);
                    vm->Parent->IPs[vm->Parent->cip].OffsetX = x;
                    vm->Parent->IPs[vm->Parent->cip].OffsetY = y;
                    vm->Parent->IPs[vm->Parent->cip].OffsetZ = z;
                    break;
    case EX_DYFP+19:for (i=0; i<vm->NumIPs; i++)         /* DYFP, T */
                      if (i != cip)
                        vm->IPs[i].uid = -1;
                    break;
    case EX_DYFP+23:Exec(vm,'@',0);                      /* DYFP, X */
                    Exec(vm->Parent,'@',0);
                    break;
    case EX_DYFP+24:fip=&(vm->IPs[cip]);                 /* DYFP, Y */
                    mip=&(vm->Parent->IPs[vm->Parent->cip]);
                    mip->Stack      = fip->Stack;
                    mip->StackPtr   = fip->StackPtr;
                    mip->Stacks     = fip->Stacks;
                    mip->StacksPtrs = fip->StacksPtrs;
                    mip->StacksPtr  = fip->StacksPtr;
                    mip->StacksSize = fip->StacksSize;
                    mip->StackSize = fip->StackSize;
                    Exec(vm->Parent,'y',0);
                    fip->Stack      = mip->Stack;
                    fip->StackPtr   = mip->StackPtr;
                    fip->Stacks     = mip->Stacks;
                    fip->StacksPtrs = mip->StacksPtrs;
                    fip->StacksPtr  = mip->StacksPtr;
                    fip->StacksSize = mip->StacksSize;
                    fip->StackSize = mip->StackSize;
                    break;
    }
}

