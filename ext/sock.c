/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef SOCK
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


void Load_SOCK(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_SOCK+8 ;     /* A */
  vm->IPs[cip].Overloads[1][vm->IPs[cip].NumOvers]=EX_SOCK+07;     /* B */
  vm->IPs[cip].Overloads[2][vm->IPs[cip].NumOvers]=EX_SOCK+01;     /* C */
  vm->IPs[cip].Overloads[8][vm->IPs[cip].NumOvers]=EX_SOCK+9 ;     /* I */
  vm->IPs[cip].Overloads[10][vm->IPs[cip].NumOvers]=EX_SOCK+02;    /* K */
  vm->IPs[cip].Overloads[11][vm->IPs[cip].NumOvers]=EX_SOCK+05;    /* L */
  vm->IPs[cip].Overloads[14][vm->IPs[cip].NumOvers]=EX_SOCK+06;    /* O */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_SOCK+03;    /* R */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_SOCK+00;    /* S */
  vm->IPs[cip].Overloads[22][vm->IPs[cip].NumOvers]=EX_SOCK+04;    /* W */

  vm->IPs[cip].Overloads[7][vm->IPs[cip].NumOvers]=EX_SOCK+20;     /* H */
  vm->IPs[cip].Overloads[15][vm->IPs[cip].NumOvers]=EX_SOCK+21;    /* P */

}

void Unload_SOCK(VM* vm) {
  Unload_Semantic(vm,0);
  Unload_Semantic(vm,1);
  Unload_Semantic(vm,2);
  Unload_Semantic(vm,8);
  Unload_Semantic(vm,10);
  Unload_Semantic(vm,11);
  Unload_Semantic(vm,14);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,22);
  }

void Do_SOCK(VM* vm,int Cmd)
{
  int i,a,b,c,x,y,z;
  unsigned long n;
  int domain,stype;
  socklen_t clen;
  char Buffer[8192];
  union {
    char Buffer[4];
    int  i;
    } itos;
  struct protoent *proto;
  struct sockaddr_in saddr;
/* scke */
  struct hostent  *host;
  fd_set files;
  struct timeval time;

  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_SOCK+00:a=Pop(vm);                                       /*  S */
                    switch (a) {
                      case  1:proto=getprotobyname("tcp"); break;
                      case  2:proto=getprotobyname("udp"); break;
                      default:proto=getprotobyname("tcp"); break;
                      }
                    a=Pop(vm);
                    switch (a) {
                      case  1:stype=SOCK_DGRAM; break;
                      case  2:stype=SOCK_STREAM; break;
                      default:stype=SOCK_STREAM; break;
                      }
                    a=Pop(vm);
                    switch (a) {
                      case  1:domain=PF_UNIX; break;
                      case  2:domain=PF_INET; break;
                      default:domain=PF_INET; break;
                      }
                    a=socket(domain,stype,proto->p_proto);
                    Push(vm,a);
                    if (a==-1) Reflect(vm);
/*                      else fcntl(a,F_SETFL,O_NDELAY); */
                    break;
    case EX_SOCK+01:n=Pop(vm);                                       /*  C */
                    saddr.sin_addr.s_addr=n;
                    n=Pop(vm);
                    saddr.sin_port=htons(n);
                    a=Pop(vm);
                    switch (a) {
                      case  1:saddr.sin_family=AF_UNIX; break;
                      case  2:saddr.sin_family=AF_INET; break;
                      default:saddr.sin_family=AF_INET; break;
                      }
                    a=Pop(vm);
                    a=connect(a,(struct sockaddr *)&saddr,sizeof(saddr));
                    if (a<0) {
                      Reflect(vm);
                      }
                    break;
    case EX_SOCK+02:a=Pop(vm);                                       /*  K */
                    a=close(a);
                    break;
    case EX_SOCK+03:a=Pop(vm);                                       /*  R */
                    b=Pop(vm);
                    if (vm->Mode>2) z=Pop(vm); else z=0;
                    if (vm->Mode>1) y=Pop(vm); else y=0;
                    x=Pop(vm);
                    a=recv(a,Buffer,b,0);
                    Push(vm,a);
                    if (a<0) Reflect(vm); else
                      for (i=0;i<a;i++)
                        Put_Funge(vm,x+i,y,z,Buffer[i]);
                    break;
    case EX_SOCK+04:a=Pop(vm);                                       /*  W */
                    b=Pop(vm);
                    if (vm->Mode>2) z=Pop(vm); else z=0;
                    if (vm->Mode>1) y=Pop(vm); else y=0;
                    x=Pop(vm);
                    for (i=0;i<b;i++)
                      Buffer[i]=Get_Funge(vm,x+i,y,z);
                    a=send(a,Buffer,b,0);
                    Push(vm,a);
                    if (a<0) Reflect(vm);
                    break;
    case EX_SOCK+05:a=Pop(vm);                                       /*  L */
                    b=Pop(vm);
                    a=listen(a,b);
                    if (a<0) Reflect(vm);
                    break;
    case EX_SOCK+06:a=Pop(vm);                                       /*  O */
                    b=Pop(vm);
                    switch (b) {
                      case 1:b=SO_DEBUG; break;
                      case 2:b=SO_REUSEADDR; break;
                      case 3:b=SO_KEEPALIVE; break;
                      case 4:b=SO_DONTROUTE; break;
                      case 5:b=SO_BROADCAST; break;
                      case 6:b=SO_OOBINLINE; break;
                      }
                    c=Pop(vm);
                    itos.i=c;
                    a=setsockopt(a,SOL_SOCKET,b,itos.Buffer,
                      sizeof(int));
                    if (a<0) Reflect(vm);
                    break;
    case EX_SOCK+07:a=Pop(vm);                                       /*  B */
                    saddr.sin_addr.s_addr=a;
                    a=Pop(vm);
                    saddr.sin_port=htons(a);
                    a=Pop(vm);
                    switch (a) {
                      case  1:saddr.sin_family=AF_UNIX; break;
                      case  2:saddr.sin_family=AF_INET; break;
                      default:saddr.sin_family=AF_INET; break;
                      }
                    a=Pop(vm);
                    a=bind(a,(struct sockaddr *)&saddr,sizeof(saddr));
                    if (a<0) {
                      Reflect(vm);
                      }
                    break;
    case EX_SOCK+8:a=Pop(vm);                                       /*  A */
                    saddr.sin_addr.s_addr=0;
                    saddr.sin_port=0;
                    saddr.sin_family=AF_INET;
                    clen=sizeof(saddr);
                    a=accept(a,(struct sockaddr *)&saddr,&clen);
                    if (a<0) Reflect(vm);
                    else {
                      Push(vm,saddr.sin_port);
                      Push(vm,saddr.sin_addr.s_addr);
                      Push(vm,a);
                      }
                    break;
    case EX_SOCK+9: Pop_String(vm,Buffer);                        /*  I */
                    n=inet_addr(Buffer);
                    Push(vm,n);
                    break;

    case EX_SOCK+20:Pop_String(vm,Buffer);                       /*  H */
                    host = gethostbyname(Buffer);
                    if (host == NULL) {
                      Reflect(vm);
                      return;
                      } 
                    for (i=0; i<4; i++) itos.Buffer[i] = host->h_addr[i];
                    Push(vm,itos.i);
                    break;
    case EX_SOCK+21:i=Pop(vm);                                  /*  P */
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

