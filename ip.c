#include "funge.h"

/* ********************************************************* */
/* ***** Create a new IP suitable for the specified VM ***** */
/* ********************************************************* */
IP New_IP(VM* vm) {
  INT i;
  IP  ret;
  ret.uid=vm->uid++;
  ret.x=0;
  ret.y=0;
  ret.z=0;
  ret.OffsetX=0;
  ret.OffsetY=0;
  ret.OffsetZ=0;
  ret.StringMode=0;
  ret.DeltaX=1;
  ret.DeltaY=0;
  ret.DeltaZ=0;
  ret.StackPtr=0;
  ret.NumOvers=0;
  ret.OverFinger[0]=0;
  ret.Timer=-1;
  ret.IPMDMode = vm->Mode;
  for (i=0;i<26;i++) ret.Overloads[i][0]=1;
  ret.FPVMs = NULL;
  ret.NumVMs = 0;
  ret.HoverMode=0;
  ret.InvertMode=0;
  ret.QueueMode=0;
  ret.SwitchMode=0;
  ret.FingerMode=0;
  ret.FingerSearch=0;
  ret.Debugger=0;
  ret.Stack=(INT *)malloc(vm->StackSize*sizeof(INT));
  if (ret.Stack == NULL) {
    printf("could not allocate memory for new IP stack\n");
    exit(-1);
    }
  ret.Stacks = (INT*)malloc(STACKS_SIZE*sizeof(INT));
  ret.StacksPtrs = (INT*)malloc(sizeof(INT)*STACKS_SIZE);
  ret.StacksSize = STACKS_SIZE;
  ret.StacksPtr=0;
  ret.Stacks[0]=0;
  ret.StackSize = vm->StackSize;
  ret.parent=-1;
  ret.dormant=0;
  ret.TimeMode='L';
  ret.FNGRloaded = 0;
  ret.mx = 0;
  ret.my = 0;
  ret.mz = 0;
  ret.tx = 0;
  ret.ty = 0;
  ret.tz = 0;
  ret.serial = 0;
  ret.subr_mode='A';
#ifdef ICAL
  ret.NextCount = 0;
#endif
#ifdef TRDS
  ret.SpMode='D';
  ret.VMode='D';
  ret.TMode='D';
  ret.RunTime=-1;
  ret.Jumped=-1;
#endif
  return ret;
}

/* ********************************************** */
/* ***** Insert an IP into the specified VM ***** */
/* ********************************************** */
void Insert_IP(VM* vm,IP ip)
{
  if (vm->NumIPs == 0) vm->IPs=(IP*)malloc(sizeof(IP));
    else vm->IPs=(IP*)realloc(vm->IPs,sizeof(IP)*(vm->NumIPs+1));
  if (vm->IPs == NULL) {
    printf("Could not allocate memory for new IP\n");
    exit(-1);
    }
  vm->IPs[vm->NumIPs] = ip;
  vm->NumIPs++;
  }

/* ************************************** */
/* ***** Completely duplicate an IP ***** */
/* ************************************** */
IP Dup_IP(IP old) {
  int i;
  IP  ret;
  ret = old;
  ret.Stack=(INT*)malloc(old.StackSize*sizeof(INT));
  if (ret.Stack == NULL) {
    printf("Dup_IP could not allocate stack for new IP\n");
    exit(-1);
    }
  for (i=0;i<old.StackSize;i++)
    ret.Stack[i]=old.Stack[i];
  ret.Stacks =(INT*)malloc(old.StacksSize*sizeof(INT));
  if (ret.Stacks == NULL) {
    printf("Dup_IP could not allocate Stacks for new IP\n");
    exit(-1);
    }
  ret.StacksPtrs =(INT*)malloc(old.StacksSize*sizeof(INT));
  if (ret.StacksPtrs == NULL) {
    printf("Dup_IP could not allocate StacksPtrs for new IP\n");
    exit(-1);
    }
  for (i=0; i<old.StacksSize; i++) {
    ret.Stacks[i] = old.Stacks[i];
    ret.StacksPtrs[i] = old.StacksPtrs[i];
    }
#ifdef IIPC
      ret.parent=old.uid;
#endif
  return ret;
  }

/* ************************************** */
/* ***** Delete an IPs dynamic data ***** */
/* ************************************** */
void Del_IP(IP* ip) {
  if (ip->Stack != NULL) {
    free(ip->Stack);
    }
  if (ip->Stacks != NULL) free(ip->Stacks);
  if (ip->StacksPtrs != NULL) free(ip->StacksPtrs);
  ip->Stacks = NULL;
  ip->StacksPtrs = NULL;
  ip->Stack = NULL;
  }

