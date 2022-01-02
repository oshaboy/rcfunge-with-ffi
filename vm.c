/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "funge.h"

/* **************************************************************** */
/* ***** Function to create a new VM, initialized to defaults ***** */
/* **************************************************************** */
VM New_VM() {
  int i;
  VM  ret;
  ret.dFspace = NULL;
  ret.PFs = NULL;
  ret.uid = 0;
  ret.IPs = NULL;
  ret.NumIPs = 0;
  ret.Mode = 2;
  ret.objs = NULL;
  ret.VmType = ' ';
  ret.NumObjs = 0;
  ret.TraceMode = 0;
  ret.TraceNoStack = 0;
  ret.Debugger = 0;
  ret.WarnMode = 0;
  ret.RetCode = 0;
  ret.Language = 98;
  ret.fpMode = 'T';
  ret.XDim = 0;
  ret.YDim = 0;
  ret.ZDim = 0;
  ret.XMin = 0;
  ret.YMin = 0;
  ret.ZMin = 0;
  ret.NumBPs = 0;
  ret.MapScreen = 0;
  ret.ModeY = 1;
  ret.ExecCount = 0;
  ret.CycleCount = 0;
  ret.delay = 0;
  ret.ProgName = NULL;
  ret.StackSize = STACK_SIZE;
  ret.ShowSummary = 1;
  ret.isDynamic = 'N';
  for (i=0;i<128;i++) ret.Traps[i]=' ';
#ifdef FILS
  for (i=0; i<MAX_FFILES; i++) ret.Files[i].Handle=NULL;
#endif
#ifdef REFC
  for (i=0; i<MAX_VECTORS; i++) ret.Vectors[i].Alloc=0;
#endif 
#ifdef IMAP
  for (i=0; i<256; i++) ret.Mapper[i]=i;
#endif
#ifdef EMEM
  for (i=0; i<MAX_EMEM; i++) ret.emems[i] = NULL;
#endif
#ifdef TRDS
  ret.Jumps = NULL;
  ret.NumJumps = 0;
  ret.TimeJumped =0;
  ret.PrintTime = -1;
  ret.StopTime = -1;
#endif
  return ret;
  }
/* **************************************************************** */


/* *************************************************** */
/* ***** Function to produce a duplicate of a VM ***** */
/* *************************************************** */
VM Dup_VM(VM* vm) {
  VM  ret;
  int i,j;
  ret = *vm;
  /* +++++++++++++++++++++++++++++++++++++++++++++ */
  /* +++++ If source has a name then copy it +++++ */
  /* +++++++++++++++++++++++++++++++++++++++++++++ */
  if (vm->ProgName != NULL) {
    ret.ProgName = (char*)malloc(strlen(vm->ProgName)+1);
    strcpy(ret.ProgName,vm->ProgName);
    }
  /* +++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  /* +++++ If source VM has funge-space then copy it +++++ */
  /* +++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  if (vm->dFspace != NULL) {
    ret.dFspace = (ROWS*)malloc(sizeof(ROWS) * vm->NumRows);
    for (i=0; i<vm->NumRows; i++) {
      ret.dFspace[i].NumCells = vm->dFspace[i].NumCells;
      ret.dFspace[i].Cells=(CELL*)malloc(sizeof(CELL)*vm->dFspace[i].NumCells);
      for (j=0; j<ret.dFspace[i].NumCells; j++) {
        ret.dFspace[i].Cells[j] = vm->dFspace[i].Cells[j];
        }
      }
    }
  /* +++++++++++++++++++++++++++++++++++++++++++++++ */
  /* +++++ If source VM has IPs then copy them +++++ */
  /* +++++++++++++++++++++++++++++++++++++++++++++++ */
  if (vm->NumIPs > 0) {
    ret.IPs = (IP*)malloc(sizeof(IP) * vm->NumIPs);
    for (i=0; i<vm->NumIPs; i++) {
      ret.IPs[i] = Dup_IP(vm->IPs[i]);
      }
    }
  return ret;
  }
/* *************************************************** */


/* ***************************************************** */
/* ***** Function to free memory allocated to a VM ***** */
/* ***************************************************** */
void Del_VM(VM* vm) {
  int i;
  /* ++++++++++++++++++++++++++++++++++++++++ */
  /* +++++ Free program name if defined +++++ */
  /* ++++++++++++++++++++++++++++++++++++++++ */
  if (vm->ProgName != NULL) free(vm->ProgName);
  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  /* +++++ If VM has allocated funge-space then free it +++++ */
  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  for (i=0; i<vm->NumRows; i++) {
    if (vm->dFspace[i].Cells != NULL) free(vm->dFspace[i].Cells);
    }
  if (vm->dFspace != NULL) free(vm->dFspace);
  /* ++++++++++++++++++++++++++++++++++++++++++ */
  /* +++++ If VM has IPs then delete them +++++ */
  /* ++++++++++++++++++++++++++++++++++++++++++ */
  for (i=0; i<vm->NumIPs; i++) {
    Del_IP(&(vm->IPs[i]));
    }
  if (vm->IPs != NULL) free(vm->IPs);
  }
/* ***************************************************** */


/* *************************************************** */
/* ***** Move current IP forward along its delta ***** */
/* *************************************************** */
void Add_Delta(VM* vm)
{
  int cip; 
  cip = vm->cip;
  vm->IPs[cip].x+=vm->IPs[cip].DeltaX;
  vm->IPs[cip].y+=vm->IPs[cip].DeltaY;
  vm->IPs[cip].z+=vm->IPs[cip].DeltaZ;
  Check_Wrap(vm,1);
}
/* *************************************************** */


/* ***************************************************** */
/* ***** Move current IP backwards along its delta ***** */
/* ***************************************************** */
void Sub_Delta(VM* vm)
{
  int cip;
  cip = vm->cip;
  vm->IPs[cip].x-=vm->IPs[cip].DeltaX;
  vm->IPs[cip].y-=vm->IPs[cip].DeltaY;
  vm->IPs[cip].z-=vm->IPs[cip].DeltaZ;
  Check_Wrap(vm,-1);
}
/* ***************************************************** */


/* *********************************************** */
/* ***** Turn current IP's delta to the left ***** */
/* *********************************************** */
void Turn_Left(VM* vm)
{
  int rx,ry;
  rx = vm->IPs[vm->cip].DeltaY;
  ry = -vm->IPs[vm->cip].DeltaX;
  vm->IPs[vm->cip].DeltaX = rx;
  vm->IPs[vm->cip].DeltaY = ry;
}
/* *********************************************** */


/* ************************************************ */
/* ***** Turn current IP's delta to the right ***** */
/* ************************************************ */
void Turn_Right(VM* vm)
{
  int rx,ry;
  rx = -vm->IPs[vm->cip].DeltaY;
  ry = vm->IPs[vm->cip].DeltaX;
  vm->IPs[vm->cip].DeltaX = rx;
  vm->IPs[vm->cip].DeltaY = ry;
}
/* ************************************************ */

void Random_Delta(VM* vm)
{
  INT i;
  int cip;
  cip = vm->cip;
  switch (vm->Mode) {
    case 1:i=rnd(2); break;
    case 2:i=rnd(4); break;
    case 3:i=rnd(6); break;
    }
  switch (i) {
    case 0:vm->IPs[cip].DeltaX=1; vm->IPs[cip].DeltaY=0; vm->IPs[cip].DeltaZ=0; break;
    case 1:vm->IPs[cip].DeltaX=-1; vm->IPs[cip].DeltaY=0; vm->IPs[cip].DeltaZ=0; break;
    case 2:vm->IPs[cip].DeltaX=0; vm->IPs[cip].DeltaY=1; vm->IPs[cip].DeltaZ=0; break;
    case 3:vm->IPs[cip].DeltaX=0; vm->IPs[cip].DeltaY=-1; vm->IPs[cip].DeltaZ=0; break;
    case 4:vm->IPs[cip].DeltaX=0; vm->IPs[cip].DeltaY=0; vm->IPs[cip].DeltaZ=1; break;
    case 5:vm->IPs[cip].DeltaX=0; vm->IPs[cip].DeltaY=0; vm->IPs[cip].DeltaZ=-1; break;
    }
}

void Sys_Info(VM* vm,INT flag)
{
  INT i,j,x,y,z;
  INT sp;
  INT PushCount;
  INT minX,minY,maxX,maxY;
  struct tm *curtime;
  time_t    Time_T;
  int cip;
  cip = vm->cip;
  Time_T=time(NULL);
  curtime=localtime(&Time_T);
  sp=vm->IPs[cip].StackPtr;
/* Find smallest and largest cell */
  Find_Limits(vm,&minX,&minY,&maxX,&maxY);

  x=vm->XDim-1; y=vm->YDim-1; z=vm->ZDim-1;

  PushCount=0;
  if (vm->Language == 108) {
    if (flag<=0 || flag==23 || vm->ModeY!=0) {  /* Cell size in bits */
      Push(vm,32);
      }
    if (flag<=0 || flag==22 || vm->ModeY!=0) {  /* Data type */
      Push(vm,2);
      }
    if (flag<=0 || flag==21 || vm->ModeY!=0) {  /* Interpreter uri */
      Push_String(vm,"rcfunge98/rcsu");
      }
    }
  if (flag<=0 || flag==20 || vm->ModeY!=0) {  /* Environment Variables */
    Push(vm,0); PushCount++;
    i=0;
    while (Envp[i]!=NULL) {
      Push_String(vm,Envp[i]);
      PushCount+=strlen(Envp[i++]);
      }
    }
  if (flag<=0 || flag==19 || vm->ModeY!=0) {  /* Command Line */
    Push(vm,0); PushCount++;
    Push(vm,0); PushCount++;
    for (i=ArgC-1;i>=0;i--) {
      for (j=strlen(ArgV[i]);j>=0;j--) {
        Push(vm,ArgV[i][j]);
        PushCount++;
        }
      }
    }
  if (flag<=0 || flag==18 || vm->ModeY!=0) {  /* Stack Sizes */
    for (i=vm->IPs[cip].StacksPtr;i>0;i--) {
      Push(vm,vm->IPs[cip].StacksPtrs[i]);
      PushCount++;
      }
    Push(vm,sp);
    PushCount++;
    }
  if (flag<=0 || flag==17 || vm->ModeY!=0) {  /* Number of stacks */
    Push(vm,vm->IPs[cip].StacksPtr+1);
    PushCount++;
    }
  if (flag<=0 || flag==16 || vm->ModeY!=0) {  /* Time */
    Push(vm,(curtime->tm_hour*256*256+curtime->tm_min*256+curtime->tm_sec));
    PushCount++;
    }
  if (flag<=0 || flag==15 || vm->ModeY!=0) {  /* Date */
    Push(vm,(curtime->tm_year*256*256+(curtime->tm_mon+1)*256+curtime->tm_mday));
    PushCount++;
    }
  if (flag<=0 || flag==14 || vm->ModeY!=0) {  /* Largest cell with non-blank */
    Push(vm,maxX - minX); PushCount++;
    if (vm->Mode>1) { Push(vm,maxY - minY); PushCount++; }
    if (vm->Mode>2) { Push(vm,vm->ZDim-vm->ZMin); PushCount++; }
    }
  if (flag<=0 || flag==13 || vm->ModeY!=0) {  /* Smallest cell with non-blank */
    Push(vm,minX); PushCount++;
    if (vm->Mode>1) { Push(vm,minY); PushCount++; }
    if (vm->Mode>2) { Push(vm,vm->ZMin); PushCount++; }
    }
  if (flag<=0 || flag==12 || vm->ModeY!=0) {  /* Storage offset of current IP */
    Push(vm,vm->IPs[cip].OffsetX); PushCount++;
    if (vm->Mode>1) { Push(vm,vm->IPs[cip].OffsetY); PushCount++; }
    if (vm->Mode>2) { Push(vm,vm->IPs[cip].OffsetZ); PushCount++; }
    }
  if (flag<=0 || flag==11 || vm->ModeY!=0) {  /* Delta of current IP */
    Push(vm,vm->IPs[cip].DeltaX); PushCount++;
    if (vm->Mode>1) { Push(vm,vm->IPs[cip].DeltaY); PushCount++; }
    if (vm->Mode>2) { Push(vm,vm->IPs[cip].DeltaZ); PushCount++; }
    }
  if (flag<=0 || flag==10 || vm->ModeY!=0) {  /* Location of current IP */
    Push(vm,vm->IPs[cip].x); PushCount++;
    if (vm->Mode>1) { Push(vm,vm->IPs[cip].y); PushCount++; }
    if (vm->Mode>2) { Push(vm,vm->IPs[cip].z); PushCount++; }
    }
  if (flag<=0 || flag==9 || vm->ModeY!=0) {   /* Team number */
    Push(vm,0); PushCount++;
    }
  if (flag<=0 || flag==8 || vm->ModeY!=0) {   /* ID of current IP */
    Push(vm,vm->IPs[cip].uid); PushCount++;
    }
  if (flag<=0 || flag==7 || vm->ModeY!=0) {   /* Dimensions of funge-space */
    Push(vm,vm->Mode); PushCount++;
    }
  if (flag<=0 || flag==6 || vm->ModeY!=0) {   /* Path separator */
    Push(vm,'/'); PushCount++;
    }
  if (flag<=0 || flag==5 || vm->ModeY!=0) {   /* how = is interpreted */
    if (SandBox != 'Y') Push(vm,3);
      else Push(vm,0);
    PushCount++;
    }
  if (flag<=0 || flag==4 || vm->ModeY!=0) {   /* Version Number */
    Push(vm,VERSIONINT); PushCount++;
    }
  if (flag<=0 || flag==3 || vm->ModeY!=0) {   /* Handprint */
    Push(vm,HANDPRINT); PushCount++;
    }
  if (flag<=0 || flag==2 || vm->ModeY!=0) {   /* Cell Size */
    Push(vm,sizeof(INT)); PushCount++;
    }
  if (flag<=0 || flag==1 || vm->ModeY!=0) {   /* Supported commands */
    if (SandBox != 'Y') Push(vm,1+2+4+8+vm->MapScreen*16);
      else Push(vm,1+vm->MapScreen*16);
    PushCount++;
    }
  if (vm->ModeY!=0 && flag>0) {
/* ************************************ */
/* Modification made by Matti Niemenmaa */
/* ************************************ */
     for (i=0;i<flag - 1;i++) Pop(vm);
     x = Pop(vm);
     j = vm->IPs[cip].StackPtr - sp;
     for (i=0;i<j;i++) Pop(vm);
/* ************************************ */
    vm->IPs[cip].StackPtr = sp;
    Push(vm,x);
    }
}

void Reflect(VM* vm)
{
  vm->IPs[vm->cip].DeltaX=-vm->IPs[vm->cip].DeltaX;
  vm->IPs[vm->cip].DeltaY=-vm->IPs[vm->cip].DeltaY;
  vm->IPs[vm->cip].DeltaZ=-vm->IPs[vm->cip].DeltaZ;
}

void Begin_Block(VM* vm,INT n)
{
  INT Temp[STACK_SIZE];
  INT TempPtr,i;
  int cip;
  cip = vm->cip;
  TempPtr=0;
/*
  if (n<0) for (i=0;i<abs(n);i++) Temp[TempPtr++]=0;
*/
  if (n<0) for (i=0;i<abs(n);i++) Push(vm,0);
  else for (i=0;i<n;i++) Temp[TempPtr++]=Pop(vm);
  Push(vm,vm->IPs[cip].OffsetX);
  if (vm->Mode>1) Push(vm,vm->IPs[cip].OffsetY);
  if (vm->Mode>2) Push(vm,vm->IPs[cip].OffsetZ);
  Add_Delta(vm);
  vm->IPs[cip].OffsetX=vm->IPs[cip].x;
  vm->IPs[cip].OffsetY=vm->IPs[cip].y;
  vm->IPs[cip].OffsetZ=vm->IPs[cip].z;
  Sub_Delta(vm);
  vm->IPs[cip].StacksPtrs[vm->IPs[cip].StacksPtr++]=vm->IPs[cip].StackPtr;
  vm->IPs[cip].Stacks[vm->IPs[cip].StacksPtr]=vm->IPs[cip].StackPtr+
    vm->IPs[cip].Stacks[vm->IPs[cip].StacksPtr-1];
  vm->IPs[cip].StackPtr=0;
  while (TempPtr>0) Push(vm,Temp[--TempPtr]);
}

void End_Block(VM* vm,INT n)
{
  INT Temp[STACK_SIZE];
  INT TempPtr,i;
  int cip;
  cip = vm->cip;
  TempPtr=0;
  if (vm->IPs[cip].StacksPtr>0) {
    for (i=0;i<n;i++) Temp[TempPtr++]=Pop(vm);
    vm->IPs[cip].StackPtr=vm->IPs[cip].StacksPtrs[--vm->IPs[cip].StacksPtr];
    if (vm->Mode>2) vm->IPs[cip].OffsetZ=Pop(vm);
    if (vm->Mode>1) vm->IPs[cip].OffsetY=Pop(vm);
    vm->IPs[cip].OffsetX=Pop(vm);
    while (TempPtr>0) Push(vm,Temp[--TempPtr]);
    if (n<0) for (i=0;i<abs(n);i++) TempPtr=Pop(vm);
    }
  else Reflect(vm);
}

INT Exec(VM* vm,INT Cell,int dflag) {
  INT a,b,c,f,i,x,y,z;
  int tx,ty,tz;
  char ch;
  char Buffer[255];
  char *PChar;
  INT cip;
  IP   tmpIP;
  cip = vm->cip;
  vm->ExecCount++;
/*
printf("[%d][%d][%d]:CMD=%d %x %c\n",vm->IPs[cip].x,vm->IPs[cip].y,vm->IPs[cip].z,Cell,Cell,Cell);
*/
#ifdef IMAP
  if (Cell>=0 && Cell<256) Cell=vm->Mapper[Cell];
#endif
  if (dflag==0) {
    if (vm->TraceMode==1) {
      fprintf(stderr,"IP=%d X=%d Y=%d CMD=%c ",cip,vm->IPs[cip].x,vm->IPs[cip].y,Cell);
      if (vm->TraceNoStack != 1) {
        for (i=0;i<vm->IPs[cip].StackPtr;i++)
          fprintf(stderr,"%d ",vm->IPs[cip].Stack[i]);
        }
      fprintf(stderr,"\n");
      }
    if (vm->Debugger>0) Cell=Debug(vm,Cell);
   }
    switch (Cell) {
      case ' ':break;
      case '!':if (Pop(vm)==0) Push(vm,1); else Push(vm,0);
               break;
      case '\"':vm->IPs[cip].StringMode=1-vm->IPs[cip].StringMode;
                break;
      case '#':Add_Delta(vm); break;
      case '$':Pop(vm); break;
      case '%':b=Pop(vm); a=Pop(vm);
               if (b!=0) Push(vm,a%b); else Push(vm,0);
               break;
      case '&':a = 0; 
               while ((a<'0' || a>'9') && a != '-') a=getchar();
               if (a != 0) ungetc(a,stdin);
               scanf("%d",&a);
               Push(vm,a);
               break;
/*
      case '&':fgets(Buffer,255,stdin);
               PChar=Buffer;
               while (*PChar!='\0' && (*PChar<'0' || *PChar>'9')) PChar++;
               sscanf(PChar,"%d",&a); Push(vm,a); break;
*/
      case '\'':if (vm->Language != 93) {
                 Add_Delta(vm); Push(vm,Get_Cell(vm));
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case '(':if (vm->Language != 93) {
                 if (vm->IPs[cip].FingerMode==0) Load_Fingerprint(vm);
                   else if (vm->IPs[cip].FingerMode==FINGER_SWAP) {
                   a=Pop(vm);
                   if (a<vm->IPs[cip].NumOvers) {
                     a=vm->IPs[cip].NumOvers-a;
                     SwapFingerprint(vm,a,vm->IPs[cip].NumOvers);
                     }
                   else Reflect(vm);
                   }
                   else if (vm->IPs[cip].FingerMode==FINGER_ROLL) {
                   a=Pop(vm);
                   if (a<vm->IPs[cip].NumOvers) {
                     a=vm->IPs[cip].NumOvers-a;
                     CopyFingerprint(vm,vm->IPs[cip].NumOvers+1,a);
                     for (i=a;i<=vm->IPs[cip].NumOvers;i++)
                       CopyFingerprint(vm,i,i+1);
                     }
                   else Reflect(vm);
                   }
                   else if (vm->IPs[cip].FingerMode==FINGER_ABS) {
                   a=Pop(vm);
                   if (a<vm->IPs[cip].NumOvers) {
                     a=vm->IPs[cip].NumOvers-a;
                     vm->IPs[cip].FingerSearch=a;
                     }
                   else Reflect(vm);
                   }
                 if (vm->IPs[cip].SwitchMode==1)
                   Put_Funge(vm,vm->IPs[cip].x-vm->IPs[cip].OffsetX,
                                vm->IPs[cip].y-vm->IPs[cip].OffsetY,
                                vm->IPs[cip].z-vm->IPs[cip].OffsetZ,')');
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case ')':if (vm->Language != 93) {
                 if (vm->IPs[cip].FingerMode==0) Unload_Fingerprint(vm);
                   else if (vm->IPs[cip].FingerMode==FINGER_SWAP) {
                   if (vm->IPs[cip].NumOvers>1)
                    SwapFingerprint(vm,vm->IPs[cip].NumOvers,vm->IPs[cip].NumOvers-1);
                   else Reflect(vm);
                   }
                   else if (vm->IPs[cip].FingerMode==FINGER_ROLL) {
                   a=Pop(vm);
                   if (a<vm->IPs[cip].NumOvers) {
                     a=vm->IPs[cip].NumOvers-a;
                     for (i=vm->IPs[cip].NumOvers+1;i>a;i--)
                       CopyFingerprint(vm,i,i-1);
                     CopyFingerprint(vm,a,vm->IPs[cip].NumOvers+1);
                     }
                   else Reflect(vm);
                   }
                   else if (vm->IPs[cip].FingerMode==FINGER_ABS) {
                   a=Pop(vm);
                   if (a<vm->IPs[cip].NumOvers) {
                     a=vm->IPs[cip].NumOvers-a;
                     CopyFingerprint(vm,vm->IPs[cip].NumOvers,a);
                     vm->IPs[cip].FingerSearch=-1;
                     }
                   else Reflect(vm);
                   }
                 if (vm->IPs[cip].SwitchMode==1)
                   Put_Funge(vm,vm->IPs[cip].x-vm->IPs[cip].OffsetX,
                                vm->IPs[cip].y-vm->IPs[cip].OffsetY,
                                vm->IPs[cip].z-vm->IPs[cip].OffsetZ,'(');
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case '*':Push(vm,Pop(vm)*Pop(vm)); break;
      case '+':Push(vm,Pop(vm)+Pop(vm)); break;
      case ',':a=Pop(vm);
#ifdef TRDS
               if (vm->CycleCount>=vm->PrintTime) {
#endif
                 printf("%c",a);
#ifdef TRDS
                 }
#endif
               break;
      case '-':b=Pop(vm); Push(vm,Pop(vm)-b); break;
#ifdef TRDS
      case '.':a=Pop(vm);
               if (vm->CycleCount>=vm->PrintTime) printf("%d ",a); 
               break;
#else
      case '.':printf("%d",Pop(vm)); break;
#endif
      case '/':b=Pop(vm); a=Pop(vm);
               if (b!=0) Push(vm,a/b); else Push(vm,0);
               break;
      case '0':Push(vm,0); break;
      case '1':Push(vm,1); break;
      case '2':Push(vm,2); break;
      case '3':Push(vm,3); break;
      case '4':Push(vm,4); break;
      case '5':Push(vm,5); break;
      case '6':Push(vm,6); break;
      case '7':Push(vm,7); break;
      case '8':Push(vm,8); break;
      case '9':Push(vm,9); break;
      case ':':a=Pop(vm); Push(vm,a); Push(vm,a); break;
      case ';':if (vm->Language != 93) {
                 Add_Delta(vm);
                 while (Get_Cell(vm) != ';') Add_Delta(vm);;
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case '<':if (vm->IPs[cip].HoverMode==0) {
                 vm->IPs[cip].DeltaX=-1; vm->IPs[cip].DeltaY=0; vm->IPs[cip].DeltaZ=0;
                 }
               else vm->IPs[cip].DeltaX--;
               break;
      case '=':if (vm->Language != 93) {
                 if (SandBox != 'Y') {
                   Pop_String(vm,Buffer);
                   Push(vm,system(Buffer));
                   } else Reflect(vm);
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case '>':if (vm->IPs[cip].HoverMode==0) {
                 vm->IPs[cip].DeltaX=1; vm->IPs[cip].DeltaY=0; vm->IPs[cip].DeltaZ=0;
                 }
               else vm->IPs[cip].DeltaX++;
               break;
      case '?':Random_Delta(vm); break;
      case '@':
               vm->IPs[cip].uid = -1;
#ifdef TRDS
               if (vm->StopTime==cip) vm->StopTime=-1;
#endif
               return 1; break;
      case 'A':Do_Overload(vm,0); break;
      case 'B':Do_Overload(vm,1); break;
      case 'C':Do_Overload(vm,2); break;
      case 'D':Do_Overload(vm,3); break;
      case 'E':Do_Overload(vm,4); break;
      case 'F':Do_Overload(vm,5); break;
      case 'G':Do_Overload(vm,6); break;
      case 'H':Do_Overload(vm,7); break;
      case 'I':Do_Overload(vm,8); break;
      case 'J':Do_Overload(vm,9); break;
      case 'K':Do_Overload(vm,10); break;
      case 'L':Do_Overload(vm,11); break;
      case 'M':Do_Overload(vm,12); break;
      case 'N':Do_Overload(vm,13); break;
      case 'O':Do_Overload(vm,14); break;
      case 'P':Do_Overload(vm,15); break;
      case 'Q':Do_Overload(vm,16); break;
      case 'R':Do_Overload(vm,17); break;
      case 'S':Do_Overload(vm,18); break;
      case 'T':Do_Overload(vm,19); break;
      case 'U':Do_Overload(vm,20); break;
      case 'V':Do_Overload(vm,21); break;
      case 'W':Do_Overload(vm,22); break;
      case 'X':Do_Overload(vm,23); break;
      case 'Y':Do_Overload(vm,24); break;
      case 'Z':Do_Overload(vm,25); break;
      case '[':if (vm->Language != 93) {
                 if (vm->Mode < 2) {
                   Reflect(vm);
                   return 0;
                   }
                 if (vm->IPs[cip].SwitchMode==1)
                   Put_Funge(vm,vm->IPs[cip].x-vm->IPs[cip].OffsetX,
                                vm->IPs[cip].y-vm->IPs[cip].OffsetY,
                                vm->IPs[cip].z-vm->IPs[cip].OffsetZ,']');
                 Turn_Left(vm);
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case '\\':a=Pop(vm); b=Pop(vm);
               Push(vm,a); Push(vm,b); break;
      case ']':if (vm->Language != 93) {
                 if (vm->Mode < 2) {
                   Reflect(vm);
                   return 0;
                   }
                 if (vm->IPs[cip].SwitchMode==1)
                   Put_Funge(vm,vm->IPs[cip].x-vm->IPs[cip].OffsetX,
                                vm->IPs[cip].y-vm->IPs[cip].OffsetY,
                                vm->IPs[cip].z-vm->IPs[cip].OffsetZ,'[');
                 Turn_Right(vm);
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case '^':if (vm->Mode < 2) {
                 Reflect(vm);
                 return 0;
                 }
               if (vm->IPs[cip].HoverMode==0) {
                 vm->IPs[cip].DeltaX=0; vm->IPs[cip].DeltaY=-1; vm->IPs[cip].DeltaZ=0;
                 }
               else vm->IPs[cip].DeltaY--;
               break;
      case '_':if (Pop(vm)==0) {
                 if (vm->IPs[cip].HoverMode==0) {
                   vm->IPs[cip].DeltaX=1; vm->IPs[cip].DeltaY=0; vm->IPs[cip].DeltaZ=0;
                   } else vm->IPs[cip].DeltaX++;
                 } else {
                 if (vm->IPs[cip].HoverMode==0) {
                   vm->IPs[cip].DeltaX=-1; vm->IPs[cip].DeltaY=0; vm->IPs[cip].DeltaZ=0;
                   } else vm->IPs[cip].DeltaX--;
                 }
               break;
      case '`':b=Pop(vm); a=Pop(vm);
               if (a>b) Push(vm,1); else Push(vm,0);
               break;
      case 'a':if (vm->Language != 93) {
                 Push(vm,10);
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case 'b':if (vm->Language != 93) {
                 Push(vm,11);
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case 'c':if (vm->Language != 93) {
                 Push(vm,12);
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case 'd':if (vm->Language != 93) {
                 Push(vm,13);
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case 'e':if (vm->Language != 93) {
                 Push(vm,14);
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case 'f':if (vm->Language != 93) {
                 Push(vm,15);
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case 'g':if (vm->Mode>2) z=Pop(vm); else z=vm->IPs[cip].z;
               if (vm->Mode>1) y=Pop(vm); else y=vm->IPs[cip].y;
               x=Pop(vm);
               Push(vm,Get_Funge(vm,x,y,z));
               break;
      case 'h':if (vm->Language != 93) {
                 if (vm->Mode>2) {
                   vm->IPs[cip].DeltaX=0; vm->IPs[cip].DeltaY=0; vm->IPs[cip].DeltaZ=1;
                   } else {
                   Warn(vm,"Requires 3d Funge-space - ",Cell);
                   Reflect(vm);
                   }
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case 'i':if (vm->Language != 93) {
                 if (SandBox != 'Y') {
                   Pop_String(vm,Buffer); f=Pop(vm);
                   if (vm->Mode>2) z=Pop(vm); else z=0;
                   if (vm->Mode>1) y=Pop(vm); else y=0;
                   x=Pop(vm);
                   if ((f & 1)==1)
                     i=Load_Bin_File(vm,Buffer,x,y,z);
                   else
                     i=Load_File(vm,Buffer,x,y,z);
                   if (i != 0) {
                     Push(vm,vm->LargestX);
                     if (vm->Mode>1) Push(vm,vm->LargestY);
                     if (vm->Mode>2) Push(vm,vm->LargestZ);
                     Push(vm,x);
                     if (vm->Mode>1) Push(vm,y);
                     if (vm->Mode>2) Push(vm,z);
                     } else Reflect(vm);
                   }
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case 'j':if (vm->Language != 93) {
                 a=Pop(vm);
                 if (a>=0)
                   for (i=0;i<a;i++) Add_Delta(vm);
                 else
                   for (i=0;i<abs(a);i++) Sub_Delta(vm);
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case 'k':if (vm->Language != 93) {
                 a=Pop(vm);
                 if (a<0) {
                   Reflect(vm);
                   return(0);
                   }
                 tx = vm->IPs[cip].x;
                 ty = vm->IPs[cip].y;
                 tz = vm->IPs[cip].z;
                 Add_Delta(vm);;
                 b=Get_Cell(vm);
                 while (b==' ' || b== ';') {
                   if (b==' ') {
                     Add_Delta(vm);;
                     b=Get_Cell(vm);
                     }
                   if (b==';') {
                     Add_Delta(vm);;
                     while (Get_Cell(vm) != ';') Add_Delta(vm);;
                     Add_Delta(vm);;
                     b=Get_Cell(vm);
                     }
                   }
                 vm->IPs[cip].x = tx;
                 vm->IPs[cip].y = ty;
                 vm->IPs[cip].z = tz;
                 for (i=0;i<a;i++) Exec(vm,b,0);
                 if (a == 0) Add_Delta(vm);;
/*                  if (a!=0) Sub_Delta(vm); */
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case 'l':if (vm->Language != 93) {
                 if (vm->Mode>2) {
                   vm->IPs[cip].DeltaX=0; vm->IPs[cip].DeltaY=0; vm->IPs[cip].DeltaZ=-1;
                   } else {
                   Warn(vm,"Requires 3d Funge-space - ",Cell);
                   Reflect(vm);
                   }
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case 'm':if (vm->Language != 93) {
                 if (vm->Mode>2) {
                   if (Pop(vm)==0) {
                     vm->IPs[cip].DeltaX=0; vm->IPs[cip].DeltaY=0; vm->IPs[cip].DeltaZ=-1;
                     } else {
                     vm->IPs[cip].DeltaX=0; vm->IPs[cip].DeltaY=0; vm->IPs[cip].DeltaZ=1;
                     }
                   } else {
                   Warn(vm,"Requires 3d Funge-space - ",Cell);
                   Reflect(vm);
                   }
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case 'n':if (vm->Language != 93) {
                 vm->IPs[cip].StackPtr=0;
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case 'o':if (vm->Language != 93) {
                 if (SandBox != 'Y') {
                   Pop_String(vm,Buffer); f=Pop(vm);
                   if (vm->Mode>2) z=Pop(vm); else z=0;
                   if (vm->Mode>1) y=Pop(vm); else y=0;
                   x=Pop(vm);
                   if (vm->Mode>2) c=Pop(vm); else c=1;
                   if (vm->Mode>1) b=Pop(vm); else b=0;
                   a=Pop(vm);
                   i=Write_File(vm,Buffer,x,y,z,a,b,c,f);
                   if (i==0) Reflect(vm);
                   }
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case 'p':if (vm->Mode>2) z=Pop(vm); else z=vm->IPs[cip].z;
               if (vm->Mode>1) y=Pop(vm); else y=vm->IPs[cip].y;
               x=Pop(vm);
               Put_Funge(vm,x,y,z,Pop(vm));
               break;
      case 'q':if (vm->Language != 93) {
                 vm->RetCode=Pop(vm); vm->NumIPs=0;
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case 'r':Reflect(vm); break;
      case 's':if (vm->Language != 93) {
                 Add_Delta(vm);; a=Pop(vm);
                 Put_Funge(vm,vm->IPs[cip].x,vm->IPs[cip].y,vm->IPs[cip].z,a);
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case 't':if (vm->Language != 93) {
                 Insert_IP(vm,Dup_IP(vm->IPs[cip]));
                 vm->IPs[vm->NumIPs-1].uid=vm->uid++;
#ifdef IIPC
                 vm->IPs[vm->NumIPs-1].parent=vm->IPs[cip].uid;
#endif
                 vm->IPs[vm->NumIPs-1].DeltaX=-vm->IPs[cip].DeltaX;
                 vm->IPs[vm->NumIPs-1].DeltaY=-vm->IPs[cip].DeltaY;
                 vm->IPs[vm->NumIPs-1].DeltaZ=-vm->IPs[cip].DeltaZ;
                 vm->cip = vm->NumIPs-1;
                 Add_Delta(vm);
                 vm->cip = cip;
                 tmpIP = vm->IPs[vm->NumIPs-1];
                 for (i=vm->NumIPs-1; i>0; i--) vm->IPs[i] = vm->IPs[i-1];
                 vm->IPs[0] = tmpIP;
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               return 2;
               break;
      case 'u':a=Pop(vm);
               if (vm->IPs[cip].StacksPtr>0) {
                 if (a>0) {
                   for (i=0;i<a;i++) Push(vm,Pop_soss(vm));
                   } 
                 else if (a<0) {
                   a=0-a;
                   for (i=0;i<a;i++) Push_soss(vm,Pop(vm));
                   }
                 }
               else Reflect(vm);
               break;
      case 'v':if (vm->Mode < 2) {
                 Reflect(vm);
                 return(0);
                 }
               if (vm->IPs[cip].HoverMode==0) {
                 vm->IPs[cip].DeltaX=0; vm->IPs[cip].DeltaY=1; vm->IPs[cip].DeltaZ=0;
                 }
               else vm->IPs[cip].DeltaY++;
               break;
      case 'w':if (vm->Language != 93) {
                 if (vm->Mode < 2) {
                   Reflect(vm);
                   return 0;
                   }
                 b=Pop(vm); a=Pop(vm);
                 if (a>b) Turn_Right(vm);
                 if (b>a) Turn_Left(vm);
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case 'x':if (vm->Language != 93) {
                 if (vm->Mode>2) vm->IPs[cip].DeltaZ=Pop(vm); else vm->IPs[cip].DeltaZ=0;
                 if (vm->Mode>1) vm->IPs[cip].DeltaY=Pop(vm); else vm->IPs[cip].DeltaY=0;
                 vm->IPs[cip].DeltaX=Pop(vm);
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case 'y':if (vm->Language != 93) {
                 Sys_Info(vm,Pop(vm));
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case 'z':if (vm->Language != 93) {
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case '{':if (vm->Language != 93) {
                 if (vm->IPs[cip].SwitchMode==1)
                   Put_Funge(vm,vm->IPs[cip].x-vm->IPs[cip].OffsetX,
                                vm->IPs[cip].y-vm->IPs[cip].OffsetY,
                                vm->IPs[cip].z-vm->IPs[cip].OffsetZ,'}');
                 Begin_Block(vm,Pop(vm));
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case '|':if (vm->Mode < 2) {
                 Reflect(vm);
                 return 0;
                 }
               if (Pop(vm)==0) {
                 if (vm->IPs[cip].HoverMode==0) {
                   vm->IPs[cip].DeltaX=0; vm->IPs[cip].DeltaY=1; vm->IPs[cip].DeltaZ=0;
                   } else vm->IPs[cip].DeltaY++;
                 } else {
                 if (vm->IPs[cip].HoverMode==0) {
                   vm->IPs[cip].DeltaX=0; vm->IPs[cip].DeltaY=-1; vm->IPs[cip].DeltaZ=0;
                   } else vm->IPs[cip].DeltaY--;
                 }
               break;
      case '}':if (vm->Language != 93) {
                 if (vm->IPs[cip].SwitchMode==1)
                   Put_Funge(vm,vm->IPs[cip].x-vm->IPs[cip].OffsetX,
                                vm->IPs[cip].y-vm->IPs[cip].OffsetY,
                                vm->IPs[cip].z-vm->IPs[cip].OffsetZ,'{');
                 End_Block(vm,Pop(vm));
                 }
               else {
                 Warn(vm,"Command not allowed in Funge/93 - ",Cell);
                 Reflect(vm);
                 }
               break;
      case '~':scanf("%c",&ch);
               Push(vm,ch);
               break;
      default :Warn(vm,"Invalid Command - ",Cell);
               Reflect(vm);
               break;
      }
  return 0;
}

void Cycle(int vm)
{
  INT i;
  INT j;
  INT Cell;
  INT Ret;
  int ModeTemp;
#ifdef TURT
  Cycle_TURT();
#endif
#ifdef TRDS
  for (i=0;i<vms[vm].NumIPs;i++)
    if (vms[vm].StopTime==-1 || vms[vm].StopTime==i)
      if (vms[vm].CycleCount>=vms[vm].IPs[i].RunTime && vms[vm].IPs[i].dormant==0) {
#else
  for (i=0;i<vms[vm].NumIPs;i++) {
#endif
    vms[vm].cip = i;
      Cell=Get_Cell(&(vms[vm]));
      if (vms[vm].IPs[i].StringMode!=0 && Cell != '"') {
        Push(&(vms[vm]),Cell); Ret=0;
        if (vms[vm].Language != 93) {
          if (Cell == 32) {
            while (Cell == 32) {
              Add_Delta(&(vms[vm]));
              Cell=Get_Cell(&(vms[vm]));
              }
            Sub_Delta(&(vms[vm]));
            Cell=Get_Cell(&(vms[vm]));
            }
          }
        }
      else {
        if (Cell == ';') {
          Add_Delta(&(vms[vm]));
          while ((Cell=Get_Cell(&(vms[vm]))) != ';') Add_Delta(&(vms[vm]));;
          Add_Delta(&(vms[vm]));;
          Cell=Get_Cell(&(vms[vm]));
          }
        while (Cell==' ') {
          Add_Delta(&(vms[vm]));
          Cell=Get_Cell(&(vms[vm]));
          if (Cell == ';') {
            Add_Delta(&(vms[vm]));
            while ((Cell=Get_Cell(&(vms[vm]))) != ';') Add_Delta(&(vms[vm]));;
            Add_Delta(&(vms[vm]));;
            Cell=Get_Cell(&(vms[vm]));
            }
          }

        if (vms[vm].delay>0) Delay(vms[vm].delay);
        ModeTemp = vms[vm].Mode;
        vms[vm].Mode = vms[vm].IPs[vms[vm].cip].IPMDMode;
        Ret=Exec(&(vms[vm]),Cell,0);
        vms[vm].Mode = ModeTemp;
        if (Ret == 2) {
          i++;
          vms[vm].cip++;
          }
/* ********************************* */
/* ***** Remove IP if it ended ***** */
/* ********************************* */
        if (vms[vm].IPs[i].uid == -1) {
          Del_IP(&(vms[vm].IPs[i]));
          vms[vm].NumIPs--;
          for (j=i;j<vms[vm].NumIPs;j++)
            vms[vm].IPs[j]=vms[vm].IPs[j+1];
          Ret=1;
          }
/* ********************************* */
        }
#ifdef TRDS
/* ********************************************************** */
/* ***** If an IP time jumped then the VM was reset and ***** */
/* ***** rest of IPs should not be processed            ***** */
/* ********************************************************** */
      if (vms[vm].TimeJumped!=0) {
        Ret=1;
        i=vms[vm].NumIPs+2;
        vms[vm].TimeJumped=0;
        vms[vm].CycleCount = -1;
        }
#endif
    if (Ret!=1 && i<vms[vm].NumIPs) Add_Delta(&(vms[vm]));
    if (Ret == 1) i--;
    }
  if (vms[vm].StopTime==-1) vms[vm].CycleCount++;
fflush(stdout);
}


/* ******************************************************* */
/* ***** This version of cycle is called for objects ***** */
/* ***** and fingerprints                            ***** */
/* ******************************************************* */
void CycleSubVM(VM* vm)
{
  INT i;
  INT j;
  INT Cell;
  INT Ret;
  while (vm->NumIPs > 0) {
#ifdef TURT
  Cycle_TURT();
#endif
#ifdef TRDS
  for (i=0;i<vm->NumIPs;i++)
    if (vm->StopTime==-1 || vm->StopTime==i)
      if (vm->CycleCount>=vm->IPs[i].RunTime && vm->IPs[i].dormant==0) {
#else
  for (i=0;i<vm->NumIPs;i++) {
#endif
    vm->cip = i;
    if (vm->IPs[i].uid >= 0) {
      Cell=Get_Cell(vm);
  /* ****************************** */
  /* ***** Process StringMode ***** */
  /* ****************************** */
      if (vm->IPs[i].StringMode!=0 && Cell != '"') {
        Push(vm,Cell); Ret=0;
        if (vm->Language != 93) {
          if (Cell == 32) {
            while (Cell == 32) {
              Add_Delta(vm);
              Cell=Get_Cell(vm);
              }
            Sub_Delta(vm);
            Cell=Get_Cell(vm);
            }
          }
        }
  /* *********************************************** */
  /* ***** Otherwise need to execute a command ***** */
  /* *********************************************** */
      /* **************************************************** */
      /* ***** Start by moving over spaces and ;blocks; ***** */
      /* **************************************************** */
      else {
        if (Cell == ';') {
          Add_Delta(vm);
          while ((Cell=Get_Cell(vm)) != ';') Add_Delta(vm);;
          Add_Delta(vm);;
          Cell=Get_Cell(vm);
          }
        while (Cell==' ') {
          Add_Delta(vm);
          Cell=Get_Cell(vm);
          if (Cell == ';') {
            Add_Delta(vm);
            while ((Cell=Get_Cell(vm)) != ';') Add_Delta(vm);;
            Add_Delta(vm);;
            Cell=Get_Cell(vm);
            }
          }
        /* ********************************************** */
        /* ***** And then execute the found command ***** */
        /* ********************************************** */
        if (vm->delay>0) Delay(vms->delay);
        Ret=Exec(vm,Cell,0);
        if (Ret == 2) {
          i++;
          vm->cip++;
          }
        }
      }
/* ********************************* */
/* ***** Remove IP if it ended ***** */
/* ********************************* */
    if (vm->IPs[i].uid == -1) {
      vm->NumIPs--;
      if (i == 0 && vm->NumIPs == 0) {
        }
      else {
        Del_IP(&(vm->IPs[i]));
        for (j=i;j<vm->NumIPs;j++)
          vm->IPs[j]=vm->IPs[j+1];
        }
      Ret=1;
      }
/* ********************************* */
#ifdef TRDS
/* ********************************************************** */
/* ***** If an IP time jumped then the VM was reset and ***** */
/* ***** rest of IPs should not be processed            ***** */
/* ********************************************************** */
      if (vm->TimeJumped!=0) {
        Ret=1;
        i=vm->NumIPs+2;
        vm->TimeJumped=0;
        vm->CycleCount = -1;
        }
#endif
    if (Ret!=1 && i<vm->NumIPs) Add_Delta(vm);
    if (Ret == 1) i--;
    }
  if (vm->StopTime==-1) vm->CycleCount++;
  }
}

