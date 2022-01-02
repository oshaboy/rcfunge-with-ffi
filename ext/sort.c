/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef SORT
#include <time.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_SORT(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[1][vm->IPs[cip].NumOvers]=EX_SORT+ 1;   /* B */
  vm->IPs[cip].Overloads[5][vm->IPs[cip].NumOvers]=EX_SORT+ 5;   /* F */
  vm->IPs[cip].Overloads[10][vm->IPs[cip].NumOvers]=EX_SORT+10;  /* K */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_SORT+18;  /* S */
}

void Unload_SORT(VM* vm) {
  Unload_Semantic(vm,1);
  Unload_Semantic(vm,5);
  Unload_Semantic(vm,10);
  Unload_Semantic(vm,18);
  }

void isort(INT* data,int count) {
  int i;
  int flag;
  INT tmp;
  flag = 1;
  while (flag == 1) {
    flag = 0;
    for (i=0; i<count-1; i++) 
      if (data[i]>data[i+1]) {
        flag = 1;
        tmp = data[i];
        data[i] = data[i+1];
        data[i+1] = tmp;
        }
    }
  }

char* getFungeString(VM* vm,VECTOR pos,VECTOR delta) {
  int   i;
  char* buffer;
  int   count = 0;
  i = 1;
  while (i != 0) {
    i = Get_Funge(vm,pos.x,pos.y,pos.z);
    pos.x += delta.x;
    pos.y += delta.y;
    pos.z += delta.z;
    count++;
    if (count == 1) buffer=(char*)malloc(sizeof(char));
      else buffer=(char*)realloc(buffer,sizeof(char)*count);
    buffer[count-1] = i;
    }
  return buffer;
  }

void putFungeString(VM* vm,VECTOR pos,VECTOR delta,char* buffer) {
  int i;
  for (i=0; i<=strlen(buffer); i++) {
    Put_Funge(vm,pos.x,pos.y,pos.z,buffer[i]);
    pos.x += delta.x;
    pos.y += delta.y;
    pos.z += delta.z;
    }
  }

void Do_SORT(VM* vm,int Cmd) {
  int i,j;
  int w;
  INT n;
  INT* temp;
  INT itmp;
  int flag;
  char** strings;
  char*  string;
  char*  tmp;
  VECTOR orig;
  VECTOR pos;
  VECTOR delta;
  VECTOR sDelta;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_SORT+ 1:n=Pop(vm);                           /* SORT, B */
                    w=Pop(vm);
                    sDelta = Pop_Vector(vm);
                    delta = Pop_Vector(vm);
                    pos = Pop_Vector(vm);
                    if (n<=0 || w<=0) {
                      Reflect(vm);
                      return;
                      }
                    if (delta.x == 0 && delta.y ==0 && delta.z == 0) {
                      Reflect(vm);
                      return;
                      }
                    if (sDelta.x == 0 && sDelta.y ==0 && sDelta.z == 0) {
                      Reflect(vm);
                      return;
                      }
                    flag = 1;
                    while (flag == 1) {
                      flag = 0;
                      for (i=0; i<n-1; i++)
                      if (Get_Funge(vm,pos.x+(delta.x*i),
                                       pos.y+(delta.y*i),
                                       pos.z+(delta.z*i))
                          >
                          Get_Funge(vm,pos.x+(delta.x*(i+1)),
                                       pos.y+(delta.y*(i+1)),
                                       pos.z+(delta.z*(i+1)))) {
                        flag = 1;
                        for (j=0; j<w; j++) {
                          itmp = Get_Funge(vm,
                            pos.x+(delta.x*i)+(sDelta.x*j),
                            pos.y+(delta.y*i)+(sDelta.y*j),
                            pos.z+(delta.z*i)+(sDelta.z*j));
                          Put_Funge(vm,
                            pos.x+(delta.x*i)+(sDelta.x*j),
                            pos.y+(delta.y*i)+(sDelta.y*j),
                            pos.z+(delta.z*i)+(sDelta.z*j),
                            Get_Funge(vm,
                              pos.x+(delta.x*(i+1))+(sDelta.x*j),
                              pos.y+(delta.y*(i+1))+(sDelta.y*j),
                              pos.z+(delta.z*(i+1))+(sDelta.z*j)));
                          Put_Funge(vm,
                            pos.x+(delta.x*(i+1))+(sDelta.x*j),
                            pos.y+(delta.y*(i+1))+(sDelta.y*j),
                            pos.z+(delta.z*(i+1))+(sDelta.z*j),itmp);
                          }
                        }
                      }
                    break;
    case EX_SORT+ 5:n=Pop(vm);                           /* SORT, F */
                    delta = Pop_Vector(vm);
                    pos = Pop_Vector(vm);
                    if (n<=0) {
                      Reflect(vm);
                      return;
                      }
                    if (delta.x == 0 && delta.y ==0 && delta.z == 0) {
                      Reflect(vm);
                      return;
                      }
                    temp = (INT*)malloc(sizeof(INT)*n);
                    if (temp == NULL) {
                      printf("ABORT: Coult not allocate memory in SORT:F\n");
                      exit(-1);
                      }
                    orig = pos;
                    for (i=0; i<n; i++) {
                      temp[i] = Get_Funge(vm,pos.x,pos.y,pos.z);
                      pos.x += delta.x;
                      pos.y += delta.y;
                      pos.z += delta.z;
                      }
                    isort(temp,n);
                    pos = orig;
                    for (i=0; i<n; i++) {
                      Put_Funge(vm,pos.x,pos.y,pos.z,temp[i]);
                      pos.x += delta.x;
                      pos.y += delta.y;
                      pos.z += delta.z;
                      }
                    free(temp);
                    break;
    case EX_SORT+10:n=Pop(vm);                           /* SORT, K */
                    if (n<=0) {
                      Reflect(vm);
                      return;
                      }
                    temp = (INT*)malloc(sizeof(INT)*n);
                    if (temp == NULL) {
                      printf("ABORT: Coult not allocate memory in SORT:K\n");
                      exit(-1);
                      }
                    for (i=0; i<n; i++) temp[i] = Pop(vm);
                    isort(temp,n);
                    for (i=n-1; i>=0; i--) Push(vm,temp[i]);
                    free(temp);
                    break;
    case EX_SORT+18:n=Pop(vm);                           /* SORT, S */
                    sDelta = Pop_Vector(vm);
                    delta = Pop_Vector(vm);
                    pos = Pop_Vector(vm);
                    if (n<=0) {
                      Reflect(vm);
                      return;
                      }
                    if (delta.x == 0 && delta.y ==0 && delta.z == 0) {
                      Reflect(vm);
                      return;
                      }
                    if (sDelta.x == 0 && sDelta.y ==0 && sDelta.z == 0) {
                      Reflect(vm);
                      return;
                      }
                    orig = pos;
                    strings = (char**)malloc(sizeof(char*)*n);
                    if (strings == NULL) {
                      printf("ABORT: Coult not allocate memory in SORT:S\n");
                      exit(-1);
                      }
                    for (i=0; i<n; i++) {
                      string = getFungeString(vm,pos,sDelta);
                      strings[i] = (char*)malloc(strlen(string)+1);
                      strcpy(strings[i],string);
                      pos.x += delta.x;
                      pos.y += delta.y;
                      pos.z += delta.z;
                      }
                    flag = 1;
                    while (flag == 1) {
                      flag = 0;
                      for (i=0; i<n-1; i++)
                        if (strcmp(strings[i],strings[i+1])>0) {
                          tmp = strings[i];
                          strings[i] = strings[i+1];
                          strings[i+1] = tmp;
                          flag = 1;
                          }
                      }
                    pos = orig;
                    for (i=0; i<n; i++) {
                      putFungeString(vm,pos,sDelta,strings[i]);
                      free(strings[i]);
                      pos.x += delta.x;
                      pos.y += delta.y;
                      pos.z += delta.z;
                      }
                    free(strings);
                    break;

    }
}
#endif

