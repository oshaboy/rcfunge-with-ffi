/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef SCKE
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "funge.h"
/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */


void Load_SCKE(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[7][vm->IPs[cip].NumOvers]=EX_SCKE+7 ;     /* H */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_SCKE+15;    /* P */
}

void Unload_SCKE(VM* vm) {
  Unload_Semantic(vm,7);
  Unload_Semantic(vm,15);
  }

void Do_SCKE(VM* vm,int Cmd)
{
  int i;
  char Buffer[8192];
  union {
    char Buffer[4];
    int  i;
    } itos;
  struct hostent  *host;
  fd_set files;
  struct timeval time;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_SCKE+ 7:Pop_String(vm,Buffer);                       /*  H */
                    host = gethostbyname(Buffer);
                    if (host == NULL) {
                      Reflect(vm);
                      return;
                      }
                    for (i=0; i<4; i++) itos.Buffer[i] = host->h_addr[i];
                    Push(vm,itos.i);
                    break;
    case EX_SCKE+15:i=Pop(vm);                                  /*  P */
                    FD_ZERO(&files);
                    FD_SET(i,&files);
                    time.tv_sec=0;
                    time.tv_usec=0;
                    i=select(i+1,&files,NULL,NULL,&time);
                    if (i == 0) {
                      Push(vm,0);
                      return; 
                      }
                    Push(vm,-1);
                    break;
    }
}
#endif

