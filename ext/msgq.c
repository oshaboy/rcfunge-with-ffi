/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef MSGQ
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_MSGQ(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_MSGQ+ 6;    /* G */
  vm->IPs[cip].Overloads[10][vm->IPs[cip].NumOvers]=EX_MSGQ+10;   /* K */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_MSGQ+17;   /* R */
  vm->IPs[cip].Overloads[18][vm->IPs[cip].NumOvers]=EX_MSGQ+18;   /* S */
  vm->IPs[cip].Overloads[19][vm->IPs[cip].NumOvers]=EX_MSGQ+19;   /* T */
}

void Unload_MSGQ(VM* vm) {
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,10);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,19);
  }

void msgq_error(VM* vm,int n) {
  Reflect(vm);
  switch (errno) {
    case EACCES: Push(vm,1); break;
    case EEXIST: Push(vm,2); break;
    case ENOENT: Push(vm,3); break;
    case ENOMEM: Push(vm,4); break;
    case ENOSPC: Push(vm,5); break;
    case EFAULT: Push(vm,6); break;
    case EINVAL: Push(vm,7); break;
    case EPERM:  Push(vm,8); break;
    case EAGAIN: Push(vm,9); break;
    case EIDRM:  Push(vm,10); break;
    case EINTR:  Push(vm,11); break;
    case E2BIG:  Push(vm,12); break;
    case ENOMSG: Push(vm,13); break;
    }
  }

void Do_MSGQ(VM* vm,int Cmd)
{
  int i,n;
  key_t key;
  int flags;
  int id;
  int mtype;
  int size;
  struct msqid_ds ds;
  struct {
    long mtype;
    byte message[4096];
    } msgbuf;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_MSGQ+ 6:n=Pop(vm);                           /* MSGQ, G */
                    key=Pop(vm);
                    flags = 0;
                    if (n & 0x1000) flags |= IPC_CREAT;
                    if (n & 0x2000) flags |= IPC_EXCL;
                    if (n & 0x4000) key = IPC_PRIVATE;
                    n |= 0x1c0;
                    flags |= (n & 0x1ff);
                    id = msgget(key,flags);
                    if (id != -1) {
                      Push(vm,id);
                      return;
                      }
                    msgq_error(vm,id);
                    break;
    case EX_MSGQ+10:key=Pop(vm);                         /* MSGQ, K */
                    i = msgctl(key,IPC_RMID,&ds);
                    if (id == -1) {
                      msgq_error(vm,i);
                      }
                    break;
    case EX_MSGQ+17:n=Pop(vm);                           /* MSGQ, R */
                    id=Pop(vm);
                    mtype=Pop(vm);
                    size=Pop(vm);
                    if (size > 4096) {
                      Push(vm,12);
                      Reflect(vm);
                      return;
                      }
                    flags = 0;
                    if (n&1) flags |=IPC_NOWAIT;
                    if (n&2) flags |=MSG_NOERROR;
                    n = msgrcv(id,&msgbuf,size,mtype,flags);
                    if (n == -1) {
                      msgq_error(vm,n);
                      }
                    else {
                      for (i=n-1; i>=0; i--)
                        Push(vm,msgbuf.message[i]);
                      Push(vm,n);
                      Push(vm,msgbuf.mtype);
                      }
                    break;
    case EX_MSGQ+18:n=Pop(vm);                           /* MSGQ, S */
                    id=Pop(vm);
                    mtype=Pop(vm);
                    size=Pop(vm);
                    if (size > 4096) {
                      Push(vm,12);
                      Reflect(vm);
                      return;
                      }
                    for (i=0; i<size; i++)
                      msgbuf.message[i] = (Pop(vm) & 0xff);
                    msgbuf.mtype = mtype;
                    flags = 0;
                    if (n&1) flags |=IPC_NOWAIT;
                    i=msgsnd(id,&msgbuf,size,flags);
                    if (i == -1) {
                      msgq_error(vm,i);
                      }
                    break;
    case EX_MSGQ+19:key=Pop(vm);                         /* MSGQ, K */
                    i = msgctl(key,IPC_STAT,&ds);
                    if (id == -1) {
                      msgq_error(vm,i);
                      }
                    Push(vm,ds.msg_qnum);
                    Push(vm,ds.msg_qbytes);
                    break;
    }
}
#endif

