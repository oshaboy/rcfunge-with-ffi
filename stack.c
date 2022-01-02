#include "funge.h"

INT Pop(VM* vm)
{
  INT value;
  int i;
  int cip;
  cip = vm->cip;
  if (vm->IPs[cip].QueueMode==0) {
    if (vm->IPs[cip].StackPtr>0) return vm->IPs[cip].Stack[--vm->IPs[cip].StackPtr+
      vm->IPs[cip].Stacks[vm->IPs[cip].StacksPtr]];
      else return 0;
    } else {
    if(vm->IPs[cip].StackPtr>0) {
      value=vm->IPs[cip].Stack[vm->IPs[cip].Stacks[vm->IPs[cip].StacksPtr]];
      for (i=vm->IPs[cip].Stacks[vm->IPs[cip].StacksPtr];
        i<vm->IPs[cip].StackPtr+vm->IPs[cip].Stacks[vm->IPs[cip].StacksPtr];i++)
        vm->IPs[cip].Stack[i]=vm->IPs[cip].Stack[i+1];
      vm->IPs[cip].StackPtr--;
      return value;
      } else return 0; 
    }
}

void Push(VM* vm,INT value)
{
  int i;
  int cip;
  cip = vm->cip;
  if (vm->IPs[cip].StackPtr+vm->IPs[cip].Stacks[vm->IPs[cip].StacksPtr] >
      vm->IPs[cip].StackSize-100) {
    vm->IPs[cip].StackSize += 1000;
    vm->IPs[cip].Stack = (INT*)realloc(vm->IPs[cip].Stack,
                       vm->IPs[cip].StackSize*sizeof(INT));
    }
  if (vm->IPs[cip].StackPtr+vm->IPs[cip].Stacks[vm->IPs[cip].StacksPtr]<vm->IPs[cip].StackSize) {
    if (vm->IPs[cip].InvertMode==0) {
      vm->IPs[cip].Stack[vm->IPs[cip].StackPtr++ +vm->IPs[cip].Stacks[vm->IPs[cip].StacksPtr]]
      =value;
      } else {
      for (i=vm->IPs[cip].StackPtr+vm->IPs[cip].Stacks[vm->IPs[cip].StacksPtr];
           i>vm->IPs[cip].Stacks[vm->IPs[cip].StacksPtr];i--)
        vm->IPs[cip].Stack[i]=vm->IPs[cip].Stack[i-1];
        vm->IPs[cip].Stack[vm->IPs[cip].Stacks[vm->IPs[cip].StacksPtr]]=value;
        vm->IPs[cip].StackPtr++;
      }
  } else {
  printf("ERROR - Stack Overflow\n");
  exit(2); /* JVH */
  }
}

INT Pop_soss(VM* vm)
{
  INT addr;
  INT v,i;
  int cip;
  cip = vm->cip;
  if (vm->IPs[cip].StacksPtr>0)
    if (vm->IPs[cip].StacksPtrs[vm->IPs[cip].StacksPtr-1]>0) {
      addr=vm->IPs[cip].Stacks[vm->IPs[cip].StacksPtr]-1;
      v=vm->IPs[cip].Stack[addr];
      for (i=addr;i<STACK_SIZE-1;i++)
        vm->IPs[cip].Stack[i]=vm->IPs[cip].Stack[i+1];
      vm->IPs[cip].Stacks[vm->IPs[cip].StacksPtr]--;
      vm->IPs[cip].StacksPtrs[vm->IPs[cip].StacksPtr-1]--;
      return v;
      }
  return 0;
}

void Push_soss(VM* vm,INT value)
{
  INT addr;
  INT i;
  int cip;
  cip = vm->cip;
  addr=vm->IPs[cip].Stacks[vm->IPs[cip].StacksPtr];
  for (i=STACK_SIZE-1;i>addr;i--)
    vm->IPs[cip].Stack[i]=vm->IPs[cip].Stack[i-1];
  vm->IPs[cip].Stack[addr]=value;
  vm->IPs[cip].Stacks[vm->IPs[cip].StacksPtr]++;
  vm->IPs[cip].StacksPtrs[vm->IPs[cip].StacksPtr-1]++;
}

void Pop_String(VM* vm,char* Buffer)
{
  INT flag;
  flag=Pop(vm);
  while (flag!=0) {
    *Buffer++=(char)flag;
    flag=Pop(vm);
    }
  *Buffer=0;
}

void Push_String(VM* vm,char* Buffer)
{
  INT i;
  for (i=strlen(Buffer);i>=0;i--) Push(vm,Buffer[i]);
}

VECTOR Pop_Vector(VM* vm) {
  VECTOR ret;
  if (vm->Mode > 2) ret.z = Pop(vm); else ret.z = 0;
  if (vm->Mode > 1) ret.y = Pop(vm); else ret.y = 0;
  ret.x = Pop(vm);
  return ret;
  }

void Push_Vector(VM* vm,VECTOR v) {
  Push(vm,v.x);
  if (vm->Mode>1) Push(vm,v.y);
  if (vm->Mode>2) Push(vm,v.z);
  }

