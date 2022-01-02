/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#include "funge.h"

int Parse(char *buffer)
{
  int num_fields,i;
  char flag;
  char *dest;
  num_fields=0;
  for (i=0;i<10;i++) Fields[i][0]='\0';
  while (*buffer != '\0' && *buffer != '\n') {
    while (*buffer <= ' ' && *buffer != '\0' && *buffer != '\n') buffer++;
      if (*buffer>' ') flag='y'; else flag='n';
      dest=&Fields[num_fields][0];
      while (flag == 'y') {
        *dest=*buffer++;
        if (*dest<'0' || *dest>'z') flag='*';
        if (*dest>'9' && *dest<'A') flag='*';
        if (*dest>'Z' && *dest<'a') flag='*';
        if (*buffer<'0' || *buffer>'z') flag='*';
        if (*buffer>'9' && *buffer<'A') flag='*';
        if (*buffer>'Z' && *buffer<'a') flag='*';
        if (*dest>='0' && *dest<='9' &&
            (*buffer<'0' || *buffer>'9')) flag='*';
        if (*dest>='A' && *dest<='Z' &&
            *buffer>='0' && *buffer<='9') flag='*';
        if (*dest>='a' && *dest<='z' &&
            *buffer>='0' && *buffer<='9') flag='*';
        dest++;
        }
      if (flag=='*') {
        *dest='\0';
        num_fields++;
        }
    }
  NumFields=num_fields;
  return num_fields;
}

void Show_Data(VM* vm,int cell)
{
  printf("[%lld] ",vm->CycleCount);
  printf("IP=%d.%d  ",vm->IPs[vm->cip].uid,vm->IPs[vm->cip].serial);
  printf("Pos=%d",vm->IPs[vm->cip].x);
  if (vm->Mode>1) printf(",%d",vm->IPs[vm->cip].y);
  if (vm->Mode>2) printf(",%d",vm->IPs[vm->cip].z);
  printf("  ");
    printf("Dir=%d",vm->IPs[vm->cip].DeltaX);
    if (vm->Mode>1) printf(",%d",vm->IPs[vm->cip].DeltaY);
    if (vm->Mode>2) printf(",%d",vm->IPs[vm->cip].DeltaZ);
    printf("  ");
  printf("Cmd=%c ",cell);
  printf("  ?: ");
}

void Del(VM* vm)
{
  int i,j,x,y,z;
  if (strcmp(Fields[1],"bp")==0) {
    x=0; sscanf(Fields[2],"%d",&x);
    y=0; sscanf(Fields[3],"%d",&y);
    z=0; sscanf(Fields[4],"%d",&z);
    for (i=0;i<vm->NumBPs;i++)
      if (x==vm->BreakPoints[i].x &&
          y==vm->BreakPoints[i].y &&
          z==vm->BreakPoints[i].z) {
        for (j=i;j<vm->NumBPs;j++) vm->BreakPoints[j]=vm->BreakPoints[j+1];
        vm->NumBPs--; i--;
        }
    }
  else if (strcmp(Fields[1],"trap")==0) {
    i=Fields[2][0]; vm->Traps[i]=' ';
    }
}

void Set(VM* vm)
{
  int i,x,y,z;
  INT v;
  if (strcmp(Fields[1],"bp")==0) {
    x=0; sscanf(Fields[2],"%d",&x);
    y=0; sscanf(Fields[3],"%d",&y);
    z=0; sscanf(Fields[4],"%d",&z);
    vm->BreakPoints[vm->NumBPs].x=x;
    vm->BreakPoints[vm->NumBPs].y=y;
    vm->BreakPoints[vm->NumBPs++].z=z;
    }
  else if (strcmp(Fields[1],"cell")==0) {
    v=0; sscanf(Fields[2],"%d",&v);
    x=0; sscanf(Fields[3],"%d",&x);
    y=0; sscanf(Fields[4],"%d",&y);
    z=0; sscanf(Fields[5],"%d",&z);
    Put_Funge(vm,x,y,z,v);
    }
  else if (strcmp(Fields[1],"ip")==0 && strcmp(Fields[2],"pos")==0) {
    x=0; sscanf(Fields[3],"%d",&x);
    y=0; sscanf(Fields[4],"%d",&y);
    z=0; sscanf(Fields[5],"%d",&z);
    vm->IPs[vm->cip].x=x;
    vm->IPs[vm->cip].y=y;
    vm->IPs[vm->cip].z=z;
    }
  else if (strcmp(Fields[1],"ip")==0 && strcmp(Fields[2],"delta")==0) {
    x=0; sscanf(Fields[3],"%d",&x);
    y=0; sscanf(Fields[4],"%d",&y);
    z=0; sscanf(Fields[5],"%d",&z);
    vm->IPs[vm->cip].DeltaX=x;
    vm->IPs[vm->cip].DeltaY=y;
    vm->IPs[vm->cip].DeltaZ=z;
    }
  else if (strcmp(Fields[1],"trap")==0) {
    i=Fields[2][0]; vm->Traps[i]='*';
    }
}

void Show(VM* vm)
{
  int i,j,x,y,z;
  INT v;
  char Ext[5];
  int cip;
  cip = vm->cip;
  if (strcmp(Fields[1],"bp")==0) {
    for (i=0;i<vm->NumBPs;i++)
      printf("%d. x=%d y=%d z=%d\n",i,
             vm->BreakPoints[i].x,vm->BreakPoints[i].y,vm->BreakPoints[i].z);
    }
  else if (strcmp(Fields[1],"time")==0) {
    printf("%lld\n",vm->CycleCount);
    }
  else if (strcmp(Fields[1],"ipdetails")==0) {
    if (strlen(Fields[2])>0) { cip=0; sscanf(Fields[2],"%d",&cip); }
    printf("DX=%-5d ",vm->IPs[cip].DeltaX);
    if (vm->Mode>1) printf("DY=%d ",vm->IPs[cip].DeltaY);
    if (vm->Mode>2) printf("DZ=%d ",vm->IPs[cip].DeltaZ);
    printf("Hover=");
    if (vm->IPs[cip].HoverMode!=0) printf("y "); else printf("n ");
    printf("Invert=");
    if (vm->IPs[cip].InvertMode!=0) printf("y "); else printf("n ");
    printf("Queue=");
    if (vm->IPs[cip].QueueMode!=0) printf("y "); else printf("n ");
    printf("Switch=");
    if (vm->IPs[cip].SwitchMode!=0) printf("y "); else printf("n ");
    printf("Finger=");
    if (vm->IPs[cip].FingerMode==0) printf("Norm ");
    else if (vm->IPs[cip].FingerMode==1) printf("Abs ");
    else if (vm->IPs[cip].FingerMode==2) printf("Roll ");
    else if (vm->IPs[cip].FingerMode==3) printf("Swap ");
    printf("\n");
    printf("String Mode:%d Debugger:%d ",vm->IPs[cip].StringMode,vm->IPs[cip].Debugger);
    printf("uid:%d Timer:%ld\n",vm->IPs[cip].uid,vm->IPs[cip].Timer);
    printf("RunTime:%d Juumped:%d ",vm->IPs[cip].RunTime,vm->IPs[cip].Jumped);
    printf("Overloads:%d \n",vm->IPs[cip].NumOvers);
    printf("StackPtr:%d Stacks:%d\n",vm->IPs[cip].StackPtr,vm->IPs[cip].StacksPtr);
    printf("Offset X:%d Offset Y:%d ",vm->IPs[cip].OffsetX,vm->IPs[cip].OffsetY);
    printf("Offset Z:%d \n",vm->IPs[cip].OffsetZ);
    }
  else if (strcmp(Fields[1],"ip")==0) {
    printf("DX=%-5d ",vm->IPs[cip].DeltaX);
    if (vm->Mode>1) printf("DY=%d ",vm->IPs[cip].DeltaY);
    if (vm->Mode>2) printf("DZ=%d ",vm->IPs[cip].DeltaZ);
    printf("Hover=");
    if (vm->IPs[cip].HoverMode!=0) printf("y "); else printf("n ");
    printf("Invert=");
    if (vm->IPs[cip].InvertMode!=0) printf("y "); else printf("n ");
    printf("Queue=");
    if (vm->IPs[cip].QueueMode!=0) printf("y "); else printf("n ");
    printf("Switch=");
    if (vm->IPs[cip].SwitchMode!=0) printf("y "); else printf("n ");
    printf("Finger=");
    if (vm->IPs[cip].FingerMode==0) printf("Norm ");
    else if (vm->IPs[cip].FingerMode==1) printf("Abs ");
    else if (vm->IPs[cip].FingerMode==2) printf("Roll ");
    else if (vm->IPs[cip].FingerMode==3) printf("Swap ");
    printf("\n");
    }
  else if (strcmp(Fields[1],"ips")==0) {
   for (i=0;i<vm->NumIPs;i++) {
    printf("%d.%d  Pos=%d",vm->IPs[i].uid,vm->IPs[i].serial,vm->IPs[i].x);
    if (vm->Mode>1) printf(",%d",vm->IPs[i].y);
    if (vm->Mode>2) printf(",%d",vm->IPs[i].z);
    printf("  ");
    printf("Dir=%d",vm->IPs[i].DeltaX);
    if (vm->Mode>1) printf(",%d",vm->IPs[i].DeltaY);
    if (vm->Mode>2) printf(",%d",vm->IPs[i].DeltaZ);
    printf("  ");
    printf("Hv=");
    if (vm->IPs[i].HoverMode!=0) printf("y "); else printf("n ");
    printf("In=");
    if (vm->IPs[i].InvertMode!=0) printf("y "); else printf("n ");
    printf("Qu=");
    if (vm->IPs[i].QueueMode!=0) printf("y "); else printf("n ");
    printf("Sw=");
    if (vm->IPs[i].SwitchMode!=0) printf("y "); else printf("n ");
    printf("Fn=");
    if (vm->IPs[i].FingerMode==0) printf("Norm ");
    else if (vm->IPs[i].FingerMode==1) printf("Abs ");
    else if (vm->IPs[i].FingerMode==2) printf("Roll ");
    else if (vm->IPs[i].FingerMode==3) printf("Swap ");
    if (vm->CycleCount < vm->IPs[i].RunTime) {
      printf("RUN=%d ",vm->IPs[i].RunTime);
      }
    printf("\n");
    }
    }
  else if (strcmp(Fields[1],"mapper")==0) {
    for (i=32;i<80;i++) printf("%c",i); printf("\n");
    for (i=32;i<80;i++) printf("%c",vm->Mapper[i]); printf("\n\n");
    for (i=80;i<128;i++) printf("%c",i); printf("\n");
    for (i=80;i<128;i++) printf("%c",vm->Mapper[i]); printf("\n");
    }
  else if (strcmp(Fields[1],"stack")==0) {
    for (i=vm->IPs[cip].Stacks[vm->IPs[cip].StacksPtr];
         i<vm->IPs[cip].Stacks[vm->IPs[cip].StacksPtr]+vm->IPs[cip].StackPtr;i++)
      printf("%d ",vm->IPs[cip].Stack[i]);
    printf("\n");
    }
  else if (strcmp(Fields[1],"stacks")==0) {
    for (i=0;i<vm->IPs[cip].Stacks[vm->IPs[cip].StacksPtr]+vm->IPs[cip].StackPtr;i++) {
      for (j=1;j<=vm->IPs[cip].StacksPtr;j++)
        if (i==vm->IPs[cip].Stacks[j]) printf("  ");
      printf("%d ",vm->IPs[cip].Stack[i]);
      }
    printf("\n");
    }
  else if (strcmp(Fields[1],"cell")==0) {
    x=0; sscanf(Fields[2],"%d",&x);
    y=0; sscanf(Fields[3],"%d",&y);
    z=0; sscanf(Fields[4],"%d",&z);
    printf("%d\n",Get_Funge(vm,x,y,z));
    }
  else if (strcmp(Fields[1],"fingers")==0) {
    printf("          A B C D E F G H I J K L M N O P Q R S T U V W X Y Z\n");
    for (i=vm->IPs[cip].NumOvers;i>0;i--) {
      printf("%-10lx",vm->IPs[cip].OverFinger[i]);
      for (j=0; j<26;j++)
        if (vm->IPs[cip].Overloads[j][i]!=0) printf("* "); else printf("  ");
      Ext[4]='\0';
      v=vm->IPs[cip].OverFinger[i];
      Ext[3]=(v & 255); v=v>>8;
      Ext[2]=(v & 255); v=v>>8;
      Ext[1]=(v & 255); v=v>>8;
      Ext[0]=(v & 255); v=v>>8;
      printf("  %s\n",Ext);
      }
    }
  else if (strcmp(Fields[1],"traps")==0) {
    for (i=0;i<128;i++) if (vm->Traps[i]!=' ') printf("%c ",i);
    printf("\n");
    }
#ifdef TRDS
  else if (strcmp(Fields[1],"tardis")==0) {
    printf("  Space: ");
    switch(vm->IPs[cip].SpMode) {
      case 'A': printf("Abs "); break;
      case 'R': printf("Rel "); break;
      case 'D': printf("Def "); break;
      default : printf("XXX "); break;
      } 
    printf("%d,%d ",vm->IPs[cip].TSpX,vm->IPs[cip].TSpY);
    printf("Vector: ");
    switch(vm->IPs[cip].VMode) {
      case 'Y': printf("Set "); break;
      case 'D': printf("Def "); break;
      default : printf("XXX "); break;
      }
    printf("%d,%d ",vm->IPs[cip].TvX,vm->IPs[cip].TvY);
    printf("Time: ");
    switch(vm->IPs[cip].TMode) {
      case 'A': printf("Abs "); break;
      case 'R': printf("Rel "); break;
      case 'D': printf("Def "); break;
      default : printf("XXX "); break;
      }
    printf("%d\n",vm->IPs[cip].TTime);
    }
#endif

}

void Help() {
  printf("Debugger Commands:\n");
  printf("------------------\n");
  printf("back                    - Move ip backward by its delta\n");
  printf("del bp x [y [z]]        - Delete a breakpoint\n");
  printf("del trap c              - Delete a command trap\n");
  printf("drop                    - Drop top entry from stack\n");
  printf("fore                    - Move ip forward by its delta\n");
  printf("pop                     - Pop and display top of stack\n");
  printf("push n                  - Push a number onto the stack\n");
  printf("quit                    - Quit program\n");
  printf("run                     - Prevent single stepping on current ip\n");
  printf("set bp x [y [z]]        - Set a breakpoint\n");
  printf("set cell v x [y [z]]    - Set value in specified funge cell\n");
  printf("set ip delta x [y [z]]  - Set ip delta\n");
  printf("set ip pos x [y [z]]    - Set ip position\n");
  printf("set trap c              - Set a command breakpoint\n");
  printf("show bp                 - Show breakpoints\n");
  printf("show cell x [y [z]]     - Show value in specified funge cell\n");
  printf("show ip                 - Show ip information\n");
  printf("show ipdetails [n]      - Show detailed information about ip\n");
  printf("show ips                - Show information on all ips\n");
  printf("show fingers            - Show A-Z overloaded fingerprints\n");
  printf("show mapper             - Show instruction mappings\n");
  printf("show stack              - Show stack for current ip\n");
  printf("show stacks             - Show entries in all stacks\n");
#ifdef TRDS
  printf("show tardis             - Show current tardis settings\n");
#endif
  printf("show time               - Show current time point\n");
  printf("show traps              - Show command breakpoints\n");
  printf("steps n                 - Allow the current ip to step n instructions\n");
  printf("<enter>                 - Step one instruction\n");
  printf("  Note: Any single character command will be executed as the associated\n");
  printf("funge instruction (example, . will do the same as pop, with only a single\n");
  printf("keystroke.)\n");
  }

int Debug(VM* vm,int cell)
{
  char Buffer[100];
  char Flag;
  int i;
  INT a;
  int cip;
  cip = vm->cip;
  for (i=0;i<vm->NumBPs;i++)
    if (vm->IPs[cip].x==vm->BreakPoints[i].x && vm->IPs[cip].y==vm->BreakPoints[i].y &&
        vm->IPs[cip].z==vm->BreakPoints[i].z) vm->IPs[cip].Debugger=0;
  if (cell>0 && cell<128) if (vm->Traps[cell]!=' ') vm->IPs[cip].Debugger=0;
  if (vm->IPs[cip].Debugger<0) vm->IPs[cip].Debugger++;
  if (vm->IPs[cip].Debugger==0) Flag='y'; else Flag='n';
  while (Flag=='y') {
    Show_Data(vm,cell);
    gets(Buffer);
    Fields[0][0]='\0'; Parse(Buffer);
    if (strcmp(Fields[0],"back")==0) { Sub_Delta(vm); cell=Get_Cell(vm); }
    if (strcmp(Fields[0],"del")==0) Del(vm);
    if (strcmp(Fields[0],"drop")==0) Pop(vm);
    if (strcmp(Fields[0],"fore")==0) { Add_Delta(vm); cell=Get_Cell(vm); }
    if (strcmp(Fields[0],"pop")==0) printf("%d\n",Pop(vm));
    if (strcmp(Fields[0],"push")==0) {
      sscanf(Fields[1],"%d",&a); Push(vm,a);
      }
    if (strcmp(Fields[0],"quit")==0) { vm->NumIPs=0; Flag='n'; }
    if (strcmp(Fields[0],"run")==0) { vm->IPs[cip].Debugger=1; Flag='n'; }
    if (strcmp(Fields[0],"set")==0) { Set(vm); cell=Get_Cell(vm); }
    if (strcmp(Fields[0],"show")==0) Show(vm);
    if (strcmp(Fields[0],"help")==0) Help();
    if (strcmp(Fields[0],"steps")==0) {
      sscanf(Fields[1],"%d",&i);
      vm->IPs[cip].Debugger=0-i;
      Flag='n';
      }
    if (strlen(Fields[0])==1) Exec(vm,Fields[0][0],1);
    if (strcmp(Fields[0],"")==0) Flag='n';
    }
  return cell;
}
