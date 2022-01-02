/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#include <math.h>

struct VECTOR3 {
  double x,y,z;
  };

struct MATRIX {
  double c[4][4];
  };

struct MATRIX Matrix_Mul(struct MATRIX a,struct MATRIX b);
struct MATRIX Matrix_Gen_Rotation(double angle,int Axis);
struct MATRIX Matrix_Gen_Scale(double tx,double ty,double tz);
struct MATRIX Matrix_Gen_Translation(double tx,double ty,double tz);
struct VECTOR3 Vector_Add(struct VECTOR3 a,struct VECTOR3 b);
struct VECTOR3 Vector_Cross(struct VECTOR3 a,struct VECTOR3 b);
struct VECTOR3 Vector_Div(struct VECTOR3 a,struct VECTOR3 b);
double Vector_Dot(struct VECTOR3 a,struct VECTOR3 b);
double Vector_Len(struct VECTOR3 a);
struct VECTOR3 Vector_Matrix_Mul(struct VECTOR3 a,struct MATRIX b);
struct VECTOR3 Vector_Max(struct VECTOR3 a,struct VECTOR3 b);
struct VECTOR3 Vector_Min(struct VECTOR3 a,struct VECTOR3 b);
struct VECTOR3 Vector_Mul(struct VECTOR3 a,struct VECTOR3 b);
struct VECTOR3 Vector_Norm(struct VECTOR3 a);
struct VECTOR3 Vector_Scale(struct VECTOR3 a,double Scale);
struct VECTOR3 Vector_Sub(struct VECTOR3 a,struct VECTOR3 b);
struct MATRIX Matrix_Zero();

struct VECTOR3 Vector_Add(struct VECTOR3 a,struct VECTOR3 b)
{
  struct VECTOR3 Result;
  Result.x=a.x+b.x;
  Result.y=a.y+b.y;
  Result.z=a.z+b.z;
  return Result;
}

struct VECTOR3 Vector_Sub(struct VECTOR3 a,struct VECTOR3 b)
{
  struct VECTOR3 Result;
  Result.x=a.x-b.x;
  Result.y=a.y-b.y;
  Result.z=a.z-b.z;
  return Result;
}

struct VECTOR3 Vector_Mul(struct VECTOR3 a,struct VECTOR3 b)
{
  struct VECTOR3 Result;
  Result.x=a.x*b.x;
  Result.y=a.y*b.y;
  Result.z=a.z*b.z;
  return Result;
}

struct VECTOR3 Vector_Div(struct VECTOR3 a,struct VECTOR3 b)
{
  struct VECTOR3 Result;
  Result.x=a.x/b.x;
  Result.y=a.y/b.y;
  Result.z=a.z/b.z;
  return Result;
}

double Vector_Dot(struct VECTOR3 a,struct VECTOR3 b)
{
  return a.x*b.x+a.y*b.y+a.z*b.z;
}

struct VECTOR3 Vector_Cross(struct VECTOR3 a,struct VECTOR3 b)
{
  struct VECTOR3 Result;
  Result.x=a.y*b.z-a.z*b.y;
  Result.y=a.z*b.x-a.x*b.z;
  Result.z=a.x*b.y-a.y*b.x;
  return Result;
}

struct VECTOR3 Vector_Min(struct VECTOR3 a,struct VECTOR3 b)
{
  struct VECTOR3 Result;
  Result.x=(a.x<b.x)?a.x:b.x;
  Result.y=(a.y<b.y)?a.y:b.y;
  Result.z=(a.z<b.z)?a.z:b.z;
  return Result;
}

struct VECTOR3 Vector_Max(struct VECTOR3 a,struct VECTOR3 b)
{
  struct VECTOR3 Result;
  Result.x=(a.x>b.x)?a.x:b.x;
  Result.y=(a.y>b.y)?a.y:b.y;
  Result.z=(a.z>b.z)?a.z:b.z;
  return Result;
}

double Vector_Len(struct VECTOR3 a)
{
  return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

struct VECTOR3 Vector_Norm(struct VECTOR3 a)
{
  double Scale;
  struct VECTOR3 Result;
  Scale=1/Vector_Len(a);
  Result.x=a.x*Scale;
  Result.y=a.y*Scale;
  Result.z=a.z*Scale;
  return Result;
}

struct VECTOR3 Vector_Scale(struct VECTOR3 a,double Scale)
{
  struct VECTOR3 Result;
  Result.x=a.x*Scale;
  Result.y=a.y*Scale;
  Result.z=a.z*Scale;
  return Result;
}

struct MATRIX Matrix_Zero()
{
  int x,y;
  struct MATRIX Result;
  for (y=0;y<4;y++) for (x=0;x<4;x++) Result.c[x][y]=0;
  return Result;
}

struct MATRIX Matrix_Gen_Translation(double tx,double ty,double tz)
{
  struct MATRIX Result;
  Result=Matrix_Zero();
  Result.c[0][0]=1; Result.c[1][1]=1; Result.c[2][2]=1; Result.c[3][3]=1;
  Result.c[3][0]=tx;
  Result.c[3][1]=ty;
  Result.c[3][2]=tz;
  return Result;
}

struct MATRIX Matrix_Gen_Scale(double tx,double ty,double tz)
{
  struct MATRIX Result;
  Result=Matrix_Zero();
  Result.c[3][3]=1;
  Result.c[0][0]=tx;
  Result.c[1][1]=ty;
  Result.c[2][2]=tz;
  return Result;
}

struct MATRIX Matrix_Gen_Rotation(double angle,int Axis)
{
  int m1,m2;
  struct MATRIX Result;
  Result=Matrix_Zero();
  for (m1=0; m1<4; m1++) Result.c[m1][m1]=1;
  m1=(Axis%3)+1;
  m2=m1%3;
  m1--;
  Result.c[Axis-1][Axis-1]=1;
  Result.c[m1][m1]=cos(angle);
  Result.c[m1][m2]=sin(angle);
  Result.c[m2][m2]=cos(angle);
  Result.c[m2][m1]=-sin(angle);
  return Result;
}

struct MATRIX Matrix_Mul(struct MATRIX a,struct MATRIX b)
{
  int i,j,k;
  double acc;
  struct MATRIX Result;
  for (i=0;i<4;i++)
    for (j=0;j<4;j++) {
      acc=0;
      for (k=0;k<4;k++)
        acc+=a.c[i][k]*b.c[k][j];
      Result.c[i][j]=acc;
      }
  return Result;
}

struct VECTOR3 Vector_Matrix_Mul(struct VECTOR3 a,struct MATRIX b)
{
  struct VECTOR3 Result;
  Result.x=a.x*b.c[0][0]+a.y*b.c[1][0]+a.z*b.c[2][0]+b.c[3][0];
  Result.y=a.x*b.c[0][1]+a.y*b.c[1][1]+a.z*b.c[2][1]+b.c[3][1];
  Result.z=a.x*b.c[0][2]+a.y*b.c[1][2]+a.z*b.c[2][2]+b.c[3][2];
  return Result;
}
