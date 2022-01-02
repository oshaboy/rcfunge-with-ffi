/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef SMPH
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_SMPH(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[0][vm->IPs[cip].NumOvers]=EX_SMPH+ 0;    /* A */
  vm->IPs[cip].Overloads[3][vm->IPs[cip].NumOvers]=EX_SMPH+ 3;    /* D */
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_SMPH+ 6;    /* G */
  vm->IPs[cip].Overloads[10][vm->IPs[cip].NumOvers]=EX_SMPH+10;   /* K */
  vm->IPs[cip].Overloads[12][vm->IPs[cip].NumOvers]=EX_SMPH+12;   /* M */
  vm->IPs[cip].Overloads[13][vm->IPs[cip].NumOvers]=EX_SMPH+13;   /* N */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_SMPH+17;   /* R */
  vm->IPs[cip].Overloads[22][vm->IPs[cip].NumOvers]=EX_SMPH+22;   /* W */
  vm->IPs[cip].Overloads[25][vm->IPs[cip].NumOvers]=EX_SMPH+25;   /* Z */
}

void Unload_SMPH(VM* vm) {
  Unload_Semantic(vm,1);
  Unload_Semantic(vm,3);
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,10);
  Unload_Semantic(vm,12);
  Unload_Semantic(vm,13);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,22);
  Unload_Semantic(vm,25);
  }

void smph_error(VM* vm,int n) {
  Reflect(vm);
  switch (errno) {
    case E2BIG: Push(vm,1); break;
    case EACCES: Push(vm,2); break;
    case EAGAIN: Push(vm,3); break;
    case EEXIST: Push(vm,4); break;
    case EFAULT: Push(vm,5); break;
    case EFBIG: Push(vm,6); break;
    case EIDRM: Push(vm,7); break;
    case EINTR: Push(vm,8); break;
    case EINVAL: Push(vm,9); break;
    case ENOENT: Push(vm,10); break;
    case ENOMEM: Push(vm,11); break;
    case ENOSPC: Push(vm,12); break;
    case EPERM: Push(vm,13); break;
    case ERANGE: Push(vm,14); break;
    default:Push(vm,0-errno); break;
    }
  }

void Do_SMPH(VM* vm,int Cmd)
{
  int i,n,v;
  key_t key;
  int flags;
  int id;
  int size;
  struct sembuf sem;
  struct sembuf *sems;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_SMPH+ 0:i=Pop(vm);                           /* SMPH, A */
                    id=Pop(vm);
                    n=Pop(vm);
                    sem.sem_num = n;
                    sem.sem_op = -1;
                    sem.sem_flg = 0;
                    if (i&1) sem.sem_flg |= IPC_NOWAIT;
                    if (i&2) sem.sem_flg |= SEM_UNDO;
                    i = semop(id,&sem,1);
                    if (i == -1) {
                      smph_error(vm,i);
                      }
                    break;
    case EX_SMPH+ 3:i=Pop(vm);                           /* SMPH, D */
                    id=Pop(vm);
                    n=Pop(vm);
                    sem.sem_num = n;
                    sem.sem_op = 1;
                    sem.sem_flg = 0;
                    if (i&1) sem.sem_flg |= IPC_NOWAIT;
                    if (i&2) sem.sem_flg |= SEM_UNDO;
                    i = semop(id,&sem,1);
                    if (i == -1) {
                      smph_error(vm,i);
                      }
                    break;
    case EX_SMPH+ 6:n=Pop(vm);                           /* SMPH, G */
                    size=Pop(vm);
                    key=Pop(vm);
                    flags = 0;
                    if (n & 0x1000) flags |= IPC_CREAT;
                    if (n & 0x2000) flags |= IPC_EXCL;
                    if (n & 0x4000) key = IPC_PRIVATE;
                    n |= 0x1c0;
                    flags |= (n & 0x1ff);
                    id = semget(key,size,flags);
                    if (id != -1) {
                      Push(vm,id);
                      return;
                      }
                    smph_error(vm,id);
                    break;
    case EX_SMPH+10:key=Pop(vm);                         /* SMPH, K */
                    i = semctl(key,IPC_RMID,0);
                    if (i == -1) {
                      smph_error(vm,i);
                      return;
                      }
                    break;
    case EX_SMPH+12:id=Pop(vm);                          /* SMPH, M */
                    n=Pop(vm);
                    sems = (struct sembuf*)malloc(sizeof(struct sembuf)*n);
                    for (i=0; i<n; i++) {
                      v=Pop(vm);
                      sems[i].sem_flg = 0;
                      if (v&1) sems[i].sem_flg |= IPC_NOWAIT;
                      if (v&2) sems[i].sem_flg |= SEM_UNDO;
                      sems[i].sem_num = Pop(vm);
                      sems[i].sem_op = Pop(vm);
                      }
                    i = semop(id,sems,n);
                    if (i == -1) {
                      smph_error(vm,i);
                      return;
                      }
                    free(sems);
                    break;
    case EX_SMPH+13:key=Pop(vm);                         /* SMPH, N */
                    n = Pop(vm);
                    i = semctl(key,GETZCNT,n);
                    if (id == -1) {
                      smph_error(vm,i);
                      }
                    Push(vm,i);
                    i = semctl(key,GETNCNT,n);
                    if (i == -1) {
                      smph_error(vm,i);
                      return;
                      }
                    Push(vm,i);
                    break;
    case EX_SMPH+17:key=Pop(vm);                         /* SMPH, R */
                    n = Pop(vm);
                    i = semctl(key,n,GETVAL);
                    if (i == -1) {
                      smph_error(vm,i);
                      return;
                      }
                    Push(vm,i);
                    break;
    case EX_SMPH+22:key=Pop(vm);                         /* SMPH, W */
                    n = Pop(vm);
                    v = Pop(vm);
                    i = semctl(key,n,SETVAL,v);
                    if (i == -1) {
                      smph_error(vm,i);
                      }
                    break;
    case EX_SMPH+25:i=Pop(vm);                           /* SMPH, Z */
                    id=Pop(vm);
                    n=Pop(vm);
                    sem.sem_num = n;
                    sem.sem_op = 0;
                    sem.sem_flg = 0;
                    if (i&1) sem.sem_flg |= IPC_NOWAIT;
                    if (i&2) sem.sem_flg |= SEM_UNDO;
                    i = semop(id,&sem,1);
                    if (i == -1) {
                      smph_error(vm,i);
                      }
                    break;
    }
}
#endif

