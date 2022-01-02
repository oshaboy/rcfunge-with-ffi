/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef SMEM
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include "funge.h"

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

void Load_SMEM(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[6][vm->IPs[cip].NumOvers]=EX_SMEM+ 6;    /* G */
  vm->IPs[cip].Overloads[10][vm->IPs[cip].NumOvers]=EX_SMEM+10;   /* K */
  vm->IPs[cip].Overloads[17][vm->IPs[cip].NumOvers]=EX_SMEM+17;   /* R */
  vm->IPs[cip].Overloads[19][vm->IPs[cip].NumOvers]=EX_SMEM+19;   /* T */
  vm->IPs[cip].Overloads[22][vm->IPs[cip].NumOvers]=EX_SMEM+22;   /* W */
}

void Unload_SMEM(VM* vm) {
  Unload_Semantic(vm,6);
  Unload_Semantic(vm,10);
  Unload_Semantic(vm,17);
  Unload_Semantic(vm,18);
  Unload_Semantic(vm,19);
  }

void smem_error(VM* vm,int n) {
  Reflect(vm);
  switch (errno) {
    case EACCES: Push(vm,1); break;
    case EEXIST: Push(vm,2); break;
    case EFAULT: Push(vm,3); break;
    case EIDRM: Push(vm,4); break;
    case EINVAL: Push(vm,5); break;
    case ENFILE: Push(vm,6); break;
    case EOVERFLOW: Push(vm,7); break;
    case ENOENT: Push(vm,8); break;
    case ENOMEM: Push(vm,9); break;
    case ENOSPC: Push(vm,10); break;
    case EPERM: Push(vm,11); break;
    }
  }

void Do_SMEM(VM* vm,int Cmd)
{
  int i,n;
  key_t key;
  int flags;
  int id;
  int size;
  int addr;
  byte* shmem;
  struct shmid_ds ds;
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_SMEM+ 6:n=Pop(vm);                           /* SMEM, G */
                    size=Pop(vm);
                    key=Pop(vm);
                    flags = 0;
                    if (n & 0x1000) flags |= IPC_CREAT;
                    if (n & 0x2000) flags |= IPC_EXCL;
                    if (n & 0x4000) key = IPC_PRIVATE;
                    n |= 0x1c0;
                    flags |= (n & 0x1ff);
                    id = shmget(key,size,flags);
                    if (id != -1) {
                      Push(vm,id);
                      return;
                      }
                    smem_error(vm,id);
                    break;
    case EX_SMEM+10:key=Pop(vm);                         /* SMEM, K */
                    i = shmctl(key,IPC_RMID,&ds);
                    if (id == -1) {
                      smem_error(vm,i);
                      }
                    break;
    case EX_SMEM+17:n=Pop(vm);                           /* SMEM, R */
                    id=Pop(vm);
                    addr=Pop(vm);
                    size=Pop(vm);
                    i = shmctl(id,IPC_STAT,&ds);
                    if (id == -1) {
                      smem_error(vm,i);
                      }
                    if (addr+size >= ds.shm_segsz) {
                      Reflect(vm);
                      Push(vm,3);
                      return;
                      }
                    flags = 0;
                    if (n&1) flags |=SHM_RDONLY;
                    shmem = shmat(id,NULL,flags);
                    if (shmem == (void*)-1) {
                      smem_error(vm,id);
                      return;
                      }
                    for (i=size-1; i>=0; i--)
                      Push(vm,shmem[addr+i]);
                    i = shmdt(shmem);
                    if (i == -1) {
                      smem_error(vm,id);
                      return;
                      }
                    break;
    case EX_SMEM+22:n=Pop(vm);                           /* SMEM, W */
                    id=Pop(vm);
                    addr=Pop(vm);
                    size=Pop(vm);
                    i = shmctl(id,IPC_STAT,&ds);
                    if (id == -1) {
                      smem_error(vm,i);
                      }
                    if (addr+size >= ds.shm_segsz) {
                      Reflect(vm);
                      Push(vm,3);
                      return;
                      }
                    flags = 0;
                    if (n&1) flags |=SHM_RDONLY;
                    shmem = shmat(id,NULL,flags);
                    if (shmem == (void*)-1) {
                      smem_error(vm,id);
                      return;
                      }
                    for (i=0; i<size; i++)
                      shmem[addr+i] = Pop(vm);
                    i = shmdt(shmem);
                    if (i == -1) {
                      smem_error(vm,id);
                      return;
                      }
                    break;
    case EX_SMEM+19:key=Pop(vm);                         /* SMEM, T */
                    i = shmctl(key,IPC_STAT,&ds);
                    if (id == -1) {
                      smem_error(vm,i);
                      }
                    Push(vm,ds.shm_segsz);
                    break;
    }
}
#endif

