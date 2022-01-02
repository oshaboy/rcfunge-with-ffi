/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef SP3D
#include "funge.h"
#include "vector.c"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */
void Load_3DSP(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_3DSP+00;   /* A */
  vm->IPs[cip].Overloads[1][vm->IPs[cip].NumOvers]=EX_3DSP+01;   /* B */
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_3DSP+02;   /* C */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_3DSP+03;   /* D */
  vm->IPs[cip].Overloads[11][vm->IPs[cip].NumOvers]=EX_3DSP+05;  /* L */
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_3DSP+06;  /* M */
  vm->IPs[cip].Overloads[13][vm->IPs[cip].NumOvers]=EX_3DSP+07;  /* N */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_3DSP+13;  /* P */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_3DSP+10;  /* R */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_3DSP+9 ;  /* S */
  vm->IPs[cip].Overloads[19][vm->IPs[cip].NumOvers]=EX_3DSP+8 ;  /* T */
  vm->IPs[cip].Overloads[20][vm->IPs[cip].NumOvers]=EX_3DSP+15;  /* U */
  vm->IPs[cip].Overloads[21][vm->IPs[cip].NumOvers]=EX_3DSP+14;  /* V */
  vm->IPs[cip].Overloads[23][vm->IPs[cip].NumOvers]=EX_3DSP+11;  /* X */
  vm->IPs[cip].Overloads[24][vm->IPs[cip].NumOvers]=EX_3DSP+12;  /* Y */
  vm->IPs[cip].Overloads[25][vm->IPs[cip].NumOvers]=EX_3DSP+04;  /* Z */
}

void Unload_3DSP(VM* vm) {
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,1);
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,11);
  Unload_Semantic(vm,12);
  Unload_Semantic(vm,13);
  Unload_Semantic(vm,15);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,19);
  Unload_Semantic(vm,20);
  Unload_Semantic(vm,21);
  Unload_Semantic(vm,23);
  Unload_Semantic(vm,24);
  Unload_Semantic(vm,25);
  }

struct MATRIX Get_Matrix(VM* vm,int x,int y,int z)
{
  int fx,fy;
  int i;
  struct MATRIX Result;
  union FLOAT {
    float f;
    long int i;
    } f;
  i=0;
  for (fy=0;fy<4;fy++) {
    for (fx=0;fx<4;fx++) {
      f.i=Get_Funge(vm,x+fx,y+fy,z);
      Result.c[fx][fy]=f.f;
      }
    }
  return Result;
}

void Put_Matrix(VM* vm,struct MATRIX *a,int x,int y,int z)
{
  int fx,fy;
  int i;
  union FLOAT {
    float f;
    long int i;
    } f;
  i=0;
  for (fy=0;fy<4;fy++) {
    for (fx=0;fx<4;fx++) {
      f.f=a->c[fx][fy];
      Put_Funge(vm,x+fx,y+fy,z,f.i);
      }
    }
}

void Do_3DSP(VM* vm,int Cmd) {
  struct VECTOR3 a,b;
  struct MATRIX m1,m2;
  INT x,y,z;
  union FLOAT {
    float f;
    long int i;
    } Float;
  float f;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_3DSP+00:Float.i=Pop(vm); b.z=Float.f;                    /*  A */
                    Float.i=Pop(vm); b.y=Float.f;
                    Float.i=Pop(vm); b.x=Float.f;
                    Float.i=Pop(vm); a.z=Float.f;
                    Float.i=Pop(vm); a.y=Float.f;
                    Float.i=Pop(vm); a.x=Float.f;
                    a=Vector_Add(a,b);
                    Float.f=a.x; Push(vm,Float.i);
                    Float.f=a.y; Push(vm,Float.i);
                    Float.f=a.z; Push(vm,Float.i);
                    break;
    case EX_3DSP+01:Float.i=Pop(vm); b.z=Float.f;                    /*  B */
                    Float.i=Pop(vm); b.y=Float.f;
                    Float.i=Pop(vm); b.x=Float.f;
                    Float.i=Pop(vm); a.z=Float.f;
                    Float.i=Pop(vm); a.y=Float.f;
                    Float.i=Pop(vm); a.x=Float.f;
                    a=Vector_Sub(a,b);
                    Float.f=a.x; Push(vm,Float.i);
                    Float.f=a.y; Push(vm,Float.i);
                    Float.f=a.z; Push(vm,Float.i);
                    break;
    case EX_3DSP+02:Float.i=Pop(vm); b.z=Float.f;                    /*  C */
                    Float.i=Pop(vm); b.y=Float.f;
                    Float.i=Pop(vm); b.x=Float.f;
                    Float.i=Pop(vm); a.z=Float.f;
                    Float.i=Pop(vm); a.y=Float.f;
                    Float.i=Pop(vm); a.x=Float.f;
                    a=Vector_Cross(a,b);
                    Float.f=a.x; Push(vm,Float.i);
                    Float.f=a.y; Push(vm,Float.i);
                    Float.f=a.z; Push(vm,Float.i);
                    break;
    case EX_3DSP+03:Float.i=Pop(vm); b.z=Float.f;                    /*  D */
                    Float.i=Pop(vm); b.y=Float.f;
                    Float.i=Pop(vm); b.x=Float.f;
                    Float.i=Pop(vm); a.z=Float.f;
                    Float.i=Pop(vm); a.y=Float.f;
                    Float.i=Pop(vm); a.x=Float.f;
                    Float.f=Vector_Dot(a,b);
                    Push(vm,Float.i);
                    break;
    case EX_3DSP+04:Float.i=Pop(vm); b.z=Float.f;                    /*  Z */
                    Float.i=Pop(vm); b.y=Float.f;
                    Float.i=Pop(vm); b.x=Float.f;
                    Float.i=Pop(vm); f=Float.f;
                    a=Vector_Scale(b,f);
                    Float.f=a.x; Push(vm,Float.i);
                    Float.f=a.y; Push(vm,Float.i);
                    Float.f=a.z; Push(vm,Float.i);
                    break;
    case EX_3DSP+05:Float.i=Pop(vm); b.z=Float.f;                    /*  L */
                    Float.i=Pop(vm); b.y=Float.f;
                    Float.i=Pop(vm); b.x=Float.f;
                    Float.f=Vector_Len(b);
                    Push(vm,Float.i);
                    break;
    case EX_3DSP+06:Float.i=Pop(vm); b.z=Float.f;                    /*  M */
                    Float.i=Pop(vm); b.y=Float.f;
                    Float.i=Pop(vm); b.x=Float.f;
                    Float.i=Pop(vm); a.z=Float.f;
                    Float.i=Pop(vm); a.y=Float.f;
                    Float.i=Pop(vm); a.x=Float.f;
                    a=Vector_Mul(a,b);
                    Float.f=a.x; Push(vm,Float.i);
                    Float.f=a.y; Push(vm,Float.i);
                    Float.f=a.z; Push(vm,Float.i);
                    break;
    case EX_3DSP+07:Float.i=Pop(vm); b.z=Float.f;                    /*  N */
                    Float.i=Pop(vm); b.y=Float.f;
                    Float.i=Pop(vm); b.x=Float.f;
                    a=Vector_Norm(b);
                    Float.f=a.x; Push(vm,Float.i);
                    Float.f=a.y; Push(vm,Float.i);
                    Float.f=a.z; Push(vm,Float.i);
                    break;
    case EX_3DSP+8 :Float.i=Pop(vm); b.z=Float.f;                    /*  T */
                    Float.i=Pop(vm); b.y=Float.f;
                    Float.i=Pop(vm); b.x=Float.f;
                    m1=Matrix_Gen_Translation(b.x,b.y,b.z);
                    if (vm->Mode>2) z=Pop(vm); else z=0;
                    if (vm->Mode>1) y=Pop(vm); else y=0;
                    x=Pop(vm);
                    Put_Matrix(vm,&m1,x,y,z);
                    break;
    case EX_3DSP+9 :Float.i=Pop(vm); b.z=Float.f;                    /*  S */
                    Float.i=Pop(vm); b.y=Float.f;
                    Float.i=Pop(vm); b.x=Float.f;
                    m1=Matrix_Gen_Scale(b.x,b.y,b.z);
                    if (vm->Mode>2) z=Pop(vm); else z=0;
                    if (vm->Mode>1) y=Pop(vm); else y=0;
                    x=Pop(vm);
                    Put_Matrix(vm,&m1,x,y,z);
                    break;
    case EX_3DSP+10:Float.i=Pop(vm); b.z=Float.f;                    /*  R */
                    b.z=b.z*(M_PI/180);
                    x=Pop(vm);
                    m1=Matrix_Gen_Rotation(b.z,x);
                    if (vm->Mode>2) z=Pop(vm); else z=0;
                    if (vm->Mode>1) y=Pop(vm); else y=0;
                    x=Pop(vm);
                    Put_Matrix(vm,&m1,x,y,z);
                    break;
    case EX_3DSP+11:if (vm->Mode>2) z=Pop(vm); else z=0;            /*  X */
                    if (vm->Mode>1) y=Pop(vm); else y=0;
                    x=Pop(vm);
                    Float.i=Pop(vm); b.z=Float.f;
                    Float.i=Pop(vm); b.y=Float.f;
                    Float.i=Pop(vm); b.x=Float.f;
                    m1=Get_Matrix(vm,x,y,z);
                    a=Vector_Matrix_Mul(b,m1);
                    Float.f=a.x; Push(vm,Float.i);
                    Float.f=a.y; Push(vm,Float.i);
                    Float.f=a.z; Push(vm,Float.i);
                    break;
    case EX_3DSP+12:if (vm->Mode>2) b.z=Pop(vm); else b.z=0;         /*  Y */
                    if (vm->Mode>1) b.y=Pop(vm); else b.y=0;
                    b.x=Pop(vm);
                    if (vm->Mode>2) a.z=Pop(vm); else a.z=0;
                    if (vm->Mode>1) a.y=Pop(vm); else a.y=0;
                    a.x=Pop(vm);
                    m1=Get_Matrix(vm,a.x,a.y,a.z);
                    m2=Get_Matrix(vm,b.x,b.y,b.z);
                    m1=Matrix_Mul(m1,m2);
                    if (vm->Mode>2) a.z=Pop(vm); else a.z=0;
                    if (vm->Mode>1) a.y=Pop(vm); else a.y=0;
                    a.x=Pop(vm);
                    Put_Matrix(vm,&m1,a.x,a.y,a.z);
                    break;
    case EX_3DSP+13:if (vm->Mode>2) {                                 /* P */
                      b.z=Pop(vm);
                      }
                     else b.z = 0;
                    if (vm->Mode>1) {
                      b.y=Pop(vm);
                      }
                      else b.y = 0;
                    b.x=Pop(vm);
                    if (vm->Mode>2) {
                      a.z=Pop(vm);
                      }
                      else a.z = 0;
                    if (vm->Mode>1) {
                      a.y=Pop(vm);
                      }
                      else a.y = 0;
                    a.x=Pop(vm);
                    m1=Get_Matrix(vm,b.x,b.y,b.z);
                    Put_Matrix(vm,&m1,a.x,a.y,a.z);
                    break;
    case EX_3DSP+14:Float.i=Pop(vm); b.z=Float.f;                    /*  V */
                    Float.i=Pop(vm); b.y=Float.f;
                    Float.i=Pop(vm); b.x=Float.f;
                    if (b.z==0) Float.f=b.x; else Float.f=b.x/b.z;
                    Push(vm,Float.i);
                    if (b.z==0) Float.f=b.y; else Float.f=b.y/b.z;
                    Push(vm,Float.i);
                    break;
    case EX_3DSP+15:Float.i=Pop(vm); a.z=Float.f;                    /*  U */
                    Float.i=Pop(vm); a.y=Float.f;
                    Float.i=Pop(vm); a.x=Float.f;
                    Float.f=a.x; Push(vm,Float.i);
                    Float.f=a.y; Push(vm,Float.i);
                    Float.f=a.z; Push(vm,Float.i);
                    Float.f=a.x; Push(vm,Float.i);
                    Float.f=a.y; Push(vm,Float.i);
                    Float.f=a.z; Push(vm,Float.i);
                    break;
    }
}
#endif

