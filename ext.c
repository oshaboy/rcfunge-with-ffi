/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include "funge.h"

void Push_Semantic(VM* vm,int slot,int sem) {
  int i;
  int cip;
  cip = vm->cip;
  if (vm->IPs[cip].Overloads[slot][vm->IPs[cip].NumOvers] == 0) {
    vm->IPs[cip].Overloads[slot][vm->IPs[cip].NumOvers] = sem;
    return;
    }
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=0xffffffff;
  vm->IPs[cip].Overloads[slot][vm->IPs[cip].NumOvers] =sem;
  }

/* ****************************************** */
/* ***** Unload a single given semantic ***** */
/* ***** Will return the semantic that  ***** */
/* ***** was popped off                 ***** */
/* ****************************************** */
int Unload_Semantic(VM* vm,int slot) {
  int i;
  int c;
  int j;
  int cip;
  int ret;
  ret = 1;
  cip = vm->cip;
  if (vm->IPs[cip].NumOvers == 0) return 1;
  i = vm->IPs[cip].NumOvers;
  while (i > 0) {
    if (vm->IPs[cip].Overloads[slot][i] != 0) {
      ret = vm->IPs[cip].Overloads[slot][i];
      vm->IPs[cip].Overloads[slot][i] = 0;
      i = -1;
      }
    i--;
    }
  if (i == 0) return 1;
  c = 0;
  for (j=0; j<26;j++)
    if (vm->IPs[cip].Overloads[j][vm->IPs[cip].NumOvers] != 0)
      c++;
  if (c == 0) {
    vm->IPs[cip].NumOvers--;
    }
  return ret;
  }

/* *********************************************** */
/* ***** Load fingerprint file to dynamic VM ***** */
/* *********************************************** */
void Load_Fingerprint_File(VM* vm,int InFile,IP* ip,int vmnum) {
  INT x,y,z;
  int count;
  char flag;
  char lineEnd;
  unsigned char *Ptr;
  unsigned char Buffer[1000];
  lineEnd = 0;
  x=0; y=0; z=0;
  vm->LargestX=0; vm->LargestY=0; vm->LargestZ=0;
  flag = ' ';
  while ((count=read(InFile,Buffer,1000)) > 0) {
    Ptr=Buffer;
    while (count > 0) {
      if (x == 0 && *Ptr == '=' &&
          *(Ptr+1) >= 'A' && *(Ptr+1) <= 'Z') {
        x = 0;
        y = 0;
        z = *(Ptr+1)-'A';
        Ptr++;
        count -= 1;
        if (ip != NULL) ip->Overloads[z][ip->NumOvers]=-(vmnum | z);
        flag = '*';
        }
      else if (*Ptr == 12) {
        z++;
        x = 0;
        y = 0;
        }
      else if (*Ptr == 10 || *Ptr == 13) {
        if (lineEnd == 0) lineEnd = *Ptr;
        if (*Ptr == lineEnd && lineEnd != 0) {
/*
            y++;
            x = 0;
*/
          if (flag == ' ') {
            y++;
            x = 0;
            }
            else flag = ' ';
          }
        }
      else {
        if (x>vm->LargestX) vm->LargestX=x;
        if (y>vm->LargestY) vm->LargestY=y;
        if (z>vm->LargestZ) vm->LargestZ=z;
        if (*Ptr != ' ') {
          Put_Funge(vm,x++,y,z,*Ptr);
          }
          else x++;
        }
      Ptr++;
      count--;
      }
    }
    vm->LargestX=vm->LargestX+1;
    vm->LargestY=vm->LargestY+1;
    vm->LargestZ=vm->LargestZ+1;
  }


void Load_Fingerprint(VM* vm)
{
  char Buffer[25];
  char *Ptr;
  long int FingerPrint;
  INT  i,j,n;
  VM   *vx;
  struct _VM v;
  int  InFile;
  int  cip;
  cip = vm->cip;
  FingerPrint=0;
  n=Pop(vm);
  if (n<0) {
    Reflect(vm);
    return;
    }
  Ptr=Buffer;
  for (i=0;i<n;i++) {
    j=Pop(vm);
    FingerPrint=FingerPrint*256+j;
    *Ptr++=(char)j;
    }
  *Ptr='\0';
  strcat(Buffer,".fl");
  if (FingerPrint != FingerPrint) i=i;
  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  /* +++++ Do not allow some extensions in sandbox mode +++++ */
  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
#ifdef DIRF
  else if (SandBox!='Y' && FingerPrint==0x44495246) Load_DIRF(vm,FingerPrint);
#endif
#ifdef EMEM
  else if (FingerPrint==0x454d454d) Load_EMEM(vm,FingerPrint);
#endif
#ifdef FILS
  else if (SandBox!='Y' && FingerPrint==0x46494c45) Load_FILE(vm,FingerPrint);
#endif
#ifdef FORK
  else if (SandBox!='Y' && FingerPrint==0x464F524B) Load_FORK(vm,FingerPrint);
#endif
#ifdef PERL
  else if (SandBox!='Y' && FingerPrint==0x5045524c) Load_PERL(vm,FingerPrint);
#endif
#ifdef MSGQ
  else if (SandBox!='Y' && FingerPrint==0x4d534751) Load_MSGQ(vm,FingerPrint);
#endif
#ifdef SGNE
  else if (SandBox!='Y' && FingerPrint==0x53474E45) Load_SGNE(vm,FingerPrint);
#endif
#ifdef SGNL
  else if (SandBox!='Y' && FingerPrint==0x53474E4C) Load_SGNL(vm,FingerPrint);
#endif
#ifdef SMEM
  else if (SandBox!='Y' && FingerPrint==0x534d454d) Load_SMEM(vm,FingerPrint);
#endif
#ifdef SMPH
  else if (SandBox!='Y' && FingerPrint==0x534d5048) Load_SMPH(vm,FingerPrint);
#endif
#ifdef SCKE
  else if (SandBox!='Y' && FingerPrint==0x53434b45) Load_SCKE(vm,FingerPrint);
#endif
#ifdef SOCK
  else if (SandBox!='Y' && FingerPrint==0x534f434b) Load_SOCK(vm,FingerPrint);
#endif
#ifdef UNIX
  else if (SandBox!='Y' && FingerPrint==0x554e4958) Load_UNIX(vm,FingerPrint);
#endif
  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
#ifdef SP3D
  else if (FingerPrint==0x33445350) Load_3DSP(vm,FingerPrint);
#endif
#ifdef ARRY
  else if (FingerPrint==0x41525259) Load_ARRY(vm,FingerPrint);
#endif
#ifdef BOOL
  else if (FingerPrint==0x424F4F4C) Load_BOOL(vm,FingerPrint);
#endif
#ifdef CPLI
  else if (FingerPrint==0x43504c49) Load_CPLI(vm,FingerPrint);
#endif
#ifdef DATE
  else if (FingerPrint==0x44415445) Load_DATE(vm,FingerPrint);
#endif
#ifdef EVAR
  else if (FingerPrint==0x45564152) Load_EVAR(vm,FingerPrint);
#endif
#ifdef HRTI
  else if (FingerPrint==0x48525449) Load_HRTI(vm,FingerPrint);
#endif
#ifdef ICAL
  else if (FingerPrint==0x4943414c) Load_ICAL(vm,FingerPrint);
#endif
#ifdef IMTH
  else if (FingerPrint==0x494d5448) Load_IMTH(vm,FingerPrint);
#endif
#ifdef INDV
  else if (FingerPrint==0x494E4456) Load_INDV(vm,FingerPrint);
#endif
#ifdef IPMD
  else if (FingerPrint==0x49504d44) Load_IPMD(vm,FingerPrint);
#endif
#ifdef PNTR
  else if (FingerPrint==0x504e5452) Load_INDV(vm,FingerPrint);
#endif
#ifdef EXEC
  else if (FingerPrint==0x45584543) Load_EXEC(vm,FingerPrint);
#endif
#ifdef FING
  else if (FingerPrint==0x46494e47) Load_FING(vm,FingerPrint);
#endif
#ifdef FNGR
  else if (FingerPrint==0x464e4752) Load_FNGR(vm,FingerPrint);
#endif
#ifdef FOBJ
  else if (FingerPrint==0x464f424a) Load_FOBJ(vm,FingerPrint);
#endif
#ifdef FPDP
  else if (FingerPrint==0x46504450) Load_FPDP(vm,FingerPrint);
#endif
#ifdef FPRT
  else if (FingerPrint==0x46505254) Load_FPRT(vm,FingerPrint);
#endif
#ifdef FPSP
  else if (FingerPrint==0x46505350) Load_FPSP(vm,FingerPrint);
#endif
#ifdef IIPC
  else if (FingerPrint==0x49495043) Load_IIPC(vm,FingerPrint);
#endif
#ifdef IMAP
  else if (FingerPrint==0x494d4150) Load_IMAP(vm,FingerPrint);
#endif
#ifdef JSTR
  else if (FingerPrint==0x4a535452) Load_JSTR(vm,FingerPrint);
#endif
#ifdef LONG
  else if (FingerPrint==0x4c4f4e47) Load_LONG(vm,FingerPrint);
#endif
#ifdef MACR
  else if (FingerPrint==0x4d414352) Load_MACR(vm,FingerPrint);
#endif
#ifdef MODU
  else if (FingerPrint==0x4d4f4455) Load_MODU(vm,FingerPrint);
#endif
#ifdef MVRS
  else if (FingerPrint==0x4d565253) Load_MVRS(vm,FingerPrint);
#endif
#ifdef NCRS
  else if (FingerPrint==0x4E435253) Load_NCRS(vm,FingerPrint);
#endif
#ifdef TRDS
  else if (FingerPrint==0x54524453) Load_TRDS(vm,FingerPrint);
#endif
#ifdef BASE
  else if (FingerPrint==0x42415345) Load_BASE(vm,FingerPrint);
#endif
#ifdef TOYS
  else if (FingerPrint==0x544f5953) Load_TOYS(vm,FingerPrint);
#endif
#ifdef TRGR
  else if (FingerPrint==0x54524752) Load_TRGR(vm,FingerPrint);
#endif
#ifdef ORTH
  else if (FingerPrint==0x4f525448) Load_ORTH(vm,FingerPrint);
#endif
#ifdef RAND
  else if (FingerPrint==0x52414e44) Load_RAND(vm,FingerPrint);
#endif
#ifdef REFC
  else if (FingerPrint==0x52454643) Load_REFC(vm,FingerPrint);
#endif
#ifdef REXP
  else if (FingerPrint==0x52455850) Load_REXP(vm,FingerPrint);
#endif
#ifdef MODE
  else if (FingerPrint==0x4d4f4445) Load_MODE(vm,FingerPrint);
#endif
#ifdef SETS
  else if (FingerPrint==0x53455453) Load_SETS(vm,FingerPrint);
#endif
#ifdef SORT
  else if (FingerPrint==0x534f5254) Load_SORT(vm,FingerPrint);
#endif
#ifdef STCK
  else if (FingerPrint==0x5354434b) Load_STCK(vm,FingerPrint);
#endif
#ifdef STRN
  else if (FingerPrint==0x5354524E) Load_STRN(vm,FingerPrint);
#endif
#ifdef SUBR
  else if (FingerPrint==0x53554252) Load_SUBR(vm,FingerPrint);
#endif
#ifdef TERM
  else if (FingerPrint==0x5445524D) Load_TERM(vm,FingerPrint);
#endif
#ifdef TIME
  else if (FingerPrint==0x54494D45) Load_TIME(vm,FingerPrint);
#endif
#ifdef ROMA
  else if (FingerPrint==0x524f4d41) Load_ROMA(vm,FingerPrint);
#endif
#ifdef FIXP
  else if (FingerPrint==0x46495850) Load_FIXP(vm,FingerPrint);
#endif
#ifdef FRTH
  else if (FingerPrint==0x46525448) Load_FRTH(vm,FingerPrint);
#endif
#ifdef WIND
  else if (FingerPrint==0x57494E44) Load_WIND(vm,FingerPrint);
#endif
#ifdef TURT
  else if (FingerPrint==0x54555254) Load_TURT(vm,FingerPrint);
#endif
#ifdef CFFI
  else if (SandBox!='Y' && FingerPrint==0x43464649) Load_CFFI(vm,FingerPrint);
#endif 
/* ********************************************************** */
/* ***** No special module for NULL, just push reflects ***** */
/* ********************************************************** */
#ifdef FNUL
  else if (FingerPrint==0x4e554c4c) {                /* NULL */
    vm->IPs[cip].NumOvers++;
    for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=1;
    vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
    Push(vm,FingerPrint); Push(vm,1);
    }
#endif
/* **************************************************************** */
/* ***** If nothing else worked, then try dynamic fingerprint ***** */
/* **************************************************************** */
  else if ((InFile=open(Buffer,O_RDONLY))!=-1) {
    vm->IPs[cip].NumOvers++;
    for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
    vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
    Push(vm,FingerPrint); Push(vm,1);
    v = New_VM();
    v.VmType = 'F';
    v.Mode = 3;
    v.isDynamic = 'Y';
    v.ModeY=vm->ModeY;
    v.ProgName = (char*)malloc(strlen(Buffer)+1);
    strcpy(v.ProgName,Buffer);
    Clear_Fs(&v);
    v.cip = -1;
    j=-1;
    for (i=0; i<vm->IPs[cip].NumVMs; i++) {
      vx = (VM*)(&(vm->IPs[cip].FPVMs[i]));
      if (vx->cip == -9999) j = i;
      }
    if (j == -1) {
      vm->IPs[cip].NumVMs++;
      if (vm->IPs[cip].NumVMs == 1)
        vm->IPs[cip].FPVMs=(struct _VM*)malloc(sizeof(struct _VM));
      else {
        vm->IPs[cip].FPVMs=(struct _VM*)realloc(vm->IPs[cip].FPVMs,
                sizeof(struct _VM)*
                vm->IPs[cip].NumVMs);
        }
      j = vm->IPs[cip].NumVMs-1;
      }
    Load_Fingerprint_File(&v,InFile,&(vm->IPs[cip]),(j+1)<<5);
    vm->IPs[cip].FPVMs[j] = v;
    }
  else Reflect(vm);
}

int Unload_Spec(VM* vm,long int FingerPrint) {
  int i;
#ifdef ARRY
  if (FingerPrint==0x41525259) {
    Unload_ARRY(vm);
    return 0;
    }
#endif
#ifdef BASE
  if (FingerPrint==0x42415345) {
    Unload_BASE(vm);
    return 0;
    }
#endif
#ifdef BOOL
  if (FingerPrint==0x424F4F4C) {
    Unload_BOOL(vm);
    return 0;
    }
#endif
#ifdef CPLI
  if (FingerPrint==0x43504c49) {
    Unload_CPLI(vm);
    return 0;
    }
#endif
#ifdef DATE
  if (FingerPrint==0x44415445)  {
    Unload_DATE(vm);
    return 0;
    }
#endif
#ifdef DIRF
  if (FingerPrint==0x44495246)  {
    Unload_DIRF(vm);
    return 0;
    }
#endif
#ifdef EMEM
  if (FingerPrint==0x454d454d) {
    Unload_EMEM(vm);
    return 0;
    }
#endif
#ifdef EVAR
  if (FingerPrint==0x45564152) {
    Unload_EVAR(vm);
    return 0;
    }
#endif
#ifdef EXEC
  if (FingerPrint==0x45584543) {
    Unload_EXEC(vm);
    return 0;
    }
#endif
#ifdef FILS
  if (FingerPrint==0x46494c45) {
    Unload_FILE(vm);
    return 0;
    }
#endif
#ifdef FING
  if (FingerPrint==0x46494e47) {
    Unload_FING(vm);
    return 0;
    }
#endif
#ifdef FIXP
  if (FingerPrint==0x46495850) {
    Unload_FIXP(vm);
    return 0;
    }
#endif
#ifdef FNGR
  if (FingerPrint==0x464e4752) {
    Unload_FNGR(vm);
    return 0;
    }
#endif
#ifdef FRTH
  if (FingerPrint==0x46525448) {
    Unload_FRTH(vm);
    return 0;
    }
#endif
#ifdef FOBJ
  if (FingerPrint==0x464f424a) {
    Unload_FOBJ(vm);
    return 0;
    }
#endif
#ifdef FORK
  if (FingerPrint==0x464F524B) {
    Unload_FORK(vm);
    return 0;
    }
#endif
#ifdef FPDP
  if (FingerPrint==0x46504450) {
    Unload_FPDP(vm);
    return 0;
    }
#endif
#ifdef FPRT
  if (FingerPrint==0x46505254) {
    Unload_FPRT(vm);
    return 0;
    }
#endif
#ifdef FPSP
  if (FingerPrint==0x46505350) {
    Unload_FPSP(vm);
    return 0;
    }
#endif
#ifdef HRTI
  if (FingerPrint==0x48525449) {
    Unload_HRTI(vm);
    return 0;
    }
#endif
#ifdef ICAL
  if (FingerPrint==0x4943414c) {
    Unload_ICAL(vm);
    return 0;
    }
#endif
#ifdef IIPC
  if (FingerPrint==0x49495043) {
    Unload_IIPC(vm);
    return 0;
    }
#endif
#ifdef IMAP
  if (FingerPrint==0x494d4150) {
    Unload_IMAP(vm);
    return 0;
    }
#endif
#ifdef IMTH
  if (FingerPrint==0x494d5448) {
    Unload_IMTH(vm);
    return 0;
    }
#endif
#ifdef INDV
  if (FingerPrint==0x494E4456) {
    Unload_INDV(vm);
    return 0;
    }
#endif
#ifdef IPMD
  if (FingerPrint==0x49504d44) {
    Unload_IPMD(vm);
    return 0;
    }
#endif
#ifdef PNTR
  if (FingerPrint==0x504e5452) {
    Unload_INDV(vm);
    return 0;
    }
#endif
#ifdef JSTR
  if (FingerPrint==0x4a535452) {
    Unload_JSTR(vm);
    return 0;
    }
#endif
#ifdef LONG
  if (FingerPrint==0x4c4f4e47) {
    Unload_LONG(vm);
    return 0;
    }
#endif
#ifdef MACR
  if (FingerPrint==0x4d414352) {
    Unload_MACR(vm);
    return 0;
    }
#endif
#ifdef MODE
  if (FingerPrint==0x4d4f4445) {
    Unload_MODE(vm);
    return 0;
    }
#endif
#ifdef MODU
  if (FingerPrint==0x4d4f4455) {
    Unload_MODU(vm);
    return 0;
    }
#endif
#ifdef MSGQ
  if (FingerPrint==0x4d534751) {
    Unload_MSGQ(vm);
    return 0;
    }
#endif
#ifdef MVRS
  if (FingerPrint==0x4d565253) {
    Unload_MVRS(vm);
    return 0;
    }
#endif
#ifdef NCRS
  if (FingerPrint==0x4E435253) {
    Unload_NCRS(vm);
    return 0;
    }
#endif
#ifdef FNUL
  if (FingerPrint==0x4e554c4c) {
    for (i=0; i<26; i++) Unload_Semantic(vm,i);
    return 0;
    }
#endif
#ifdef ORTH
  if (FingerPrint==0x4f525448) {
    Unload_ORTH(vm);
    return 0;
    }
#endif
#ifdef PERL
  if (FingerPrint==0x5045524c) {
    Unload_PERL(vm);
    return 0;
    }
#endif
#ifdef RAND
  if (FingerPrint==0x52414e44) {
    Unload_RAND(vm);
    return 0;
    }
#endif
#ifdef REFC
  if (FingerPrint==0x52454643) {
    Unload_REFC(vm);
    return 0;
    }
#endif
#ifdef REXP
  if (FingerPrint==0x52455850) {
    Unload_REXP(vm);
    return 0;
    }
#endif
#ifdef ROMA
  if (FingerPrint==0x524f4d41) {
    Unload_ROMA(vm);
    return 0;
    }
#endif
#ifdef SETS
  if (FingerPrint==0x53455453) {
    Unload_SETS(vm);
    return 0;
    }
#endif
#ifdef SGNE
  if (FingerPrint==0x53474E45) {
    Unload_SGNE(vm);
    return 0;
    }
#endif
#ifdef SGNL
  if (FingerPrint==0x53474E4C) {
    Unload_SGNL(vm);
    return 0;
    }
#endif
#ifdef SMEM
  if (FingerPrint==0x534d454d) {
    Unload_SMEM(vm);
    return 0;
    }
#endif
#ifdef SMPH
  if (FingerPrint==0x534d5048) {
    Unload_SMPH(vm);
    return 0;
    }
#endif
#ifdef SCKE
  if (FingerPrint==0x53434b45) {
    Unload_SCKE(vm);
    return 0;
    }
#endif
#ifdef SOCK
  if (FingerPrint==0x534f434b) {
    Unload_SOCK(vm);
    return 0;
    }
#endif
#ifdef SORT
  if (FingerPrint==0x534f5254) {
    Unload_SORT(vm);
    return 0;
    }
#endif
#ifdef SP3D
  if (FingerPrint==0x33445350) {
    Unload_3DSP(vm);
    return 0;
    }
#endif
#ifdef STCK
  if (FingerPrint==0x5354434b) {
    Unload_STCK(vm);
    return 0;
    }
#endif
#ifdef STRN
  if (FingerPrint==0x5354524E) {
    Unload_STRN(vm);
    return 0;
    }
#endif
#ifdef SUBR
  if (FingerPrint==0x53554252) {
    Unload_SUBR(vm);
    return 0;
    }
#endif
#ifdef TOYS
  if (FingerPrint==0x544f5953) {
    Unload_TOYS(vm);
    return 0;
    }
#endif
#ifdef TRGR
  if (FingerPrint==0x54524752) {
    Unload_TRGR(vm);
    return 0;
    }
#endif
#ifdef TERM
  if (FingerPrint==0x5445524D) {
    Unload_TERM(vm);
    return 0;
    }
#endif
#ifdef TIME
  if (FingerPrint==0x54494D45) {
    Unload_TIME(vm);
    return 0;
    }
#endif
#ifdef TRDS
  if (FingerPrint==0x54524453) {
    Unload_TRDS(vm);
    return 0;
    }
#endif
#ifdef TURT
  if (FingerPrint==0x54555254) {
    Unload_TURT(vm);
    return 0;
    }
#endif
#ifdef UNIX
  if (FingerPrint==0x554e4958) {
    Unload_UNIX(vm);
    return 0;
    }
#endif
#ifdef WIND
  if (FingerPrint==0x57494E44) {
    Unload_WIND(vm);
    return 0;
    }
#endif
#ifdef CFFI
  if (FingerPrint==0x43464649) {
    Unload_CFFI(vm);
    return 0;
    }
#endif 
  return -1;
  }

void Unload_Fingerprint(VM* vm)
{
  char Buffer[25];
  char *Ptr;
  INT  i,j,n;
  long int FingerPrint;
  int cip;
  cip = vm->cip;
  n=Pop(vm);
  if (n<0) {
    Reflect(vm);
    return;
    }
  Ptr=Buffer;
  FingerPrint=0;
  for (i=0;i<n;i++) FingerPrint=FingerPrint*256+Pop(vm);
  n=-1;
  if (vm->IPs[cip].FNGRloaded != 1) {
    if (Unload_Spec(vm,FingerPrint) == 0) return;
    }

  if (FingerPrint==0x464e4752) {
    vm->IPs[cip].FNGRloaded = 0;
    }
  for (i=1;i<=vm->IPs[cip].NumOvers;i++)
    if (FingerPrint==vm->IPs[cip].OverFinger[i]) n=i;
  if (n>=0) {
    for (i=0;i<26;i++) if (vm->IPs[cip].Overloads[i][n]<0)
/*
      if (vm->IPs[cip].MiniFs[abs(vm->IPs[cip].Overloads[i][n])] != NULL) {
        free(vm->IPs[cip].MiniFs[abs(vm->IPs[cip].Overloads[i][n])]);
        vm->IPs[cip].MiniFs[abs(vm->IPs[cip].Overloads[i][n])] = NULL;
        }
*/
    for (i=n;i<vm->IPs[cip].NumOvers;i++) {
      vm->IPs[cip].OverFinger[i]=vm->IPs[cip].OverFinger[i+1];
      for (j=0;j<26;j++)
        vm->IPs[cip].Overloads[j][i]=vm->IPs[cip].Overloads[j][i+1];
      }
    vm->IPs[cip].NumOvers--;
    }
  else Reflect(vm);

}

/* ******************************************************* */
/* ***** Funciton for executing fingerprint commands ***** */
/* ******************************************************* */
void Do_Overload(VM* vm,INT func)
{
  INT Cmd;
  INT i;
  IP  ip;
  VM  *fpvm;
  int vmNum;
  int cip;
  cip = vm->cip;
  i=vm->IPs[cip].NumOvers;
  if (vm->IPs[cip].FingerMode==FINGER_ABS && vm->IPs[cip].FingerSearch>0 &&
    vm->IPs[cip].FingerSearch<=vm->IPs[cip].NumOvers)
    i=vm->IPs[cip].FingerSearch;
  Cmd=0;
  while (Cmd==0) {
    Cmd=vm->IPs[cip].Overloads[func][i--];
    }
/* ********************************************************* */
/* ***** If Cmd<0 then Cmd is in a dynamic fingerprint ***** */
/* ********************************************************* */
  if (Cmd<0) {
    Cmd=abs(Cmd);
    vmNum = (Cmd >> 5)-1;
    Cmd = (Cmd & 0x1f);
    fpvm = (VM*)(&(vm->IPs[cip].FPVMs[vmNum]));
    fpvm->Parent = vm;
    /* ************************************************ */
    /* ***** Create IP in fingerprint funge-space ***** */
    /* ************************************************ */
    ip = New_IP(fpvm);
    ip.z = Cmd;
    if (ip.Stack != NULL) free(ip.Stack);
    if (ip.Stacks != NULL) free(ip.Stacks);
    if (ip.StacksPtrs != NULL) free(ip.StacksPtrs);
    /* ****************************************** */
    /* ***** Set stack to calling IPs stack ***** */
    /* ****************************************** */
    ip.Stack = vm->IPs[cip].Stack;
    ip.StackPtr = vm->IPs[cip].StackPtr;
    ip.Stacks = vm->IPs[cip].Stacks;
    ip.StacksPtrs = vm->IPs[cip].StacksPtrs;
    ip.StacksPtr = vm->IPs[cip].StacksPtr;
    ip.StacksSize = vm->IPs[cip].StacksSize;
    ip.StackSize = vm->IPs[cip].StackSize;
    /* *********************************** */
    /* ***** now run the fingerprint ***** */
    /* *********************************** */
    if (vm->fpMode == 'B') {
      fpvm->Mode = 2;
      }
    fpvm->CycleCount = 0;
    Load_DYFP(&ip);
    Insert_IP(fpvm,ip);
    CycleSubVM(fpvm);
    ip = fpvm->IPs[0];
    /* ************************************************** */
    /* ***** Transfer the stack back to original IP ***** */
    /* ************************************************** */
    vm->IPs[cip].Stack = ip.Stack;
    vm->IPs[cip].StackPtr = ip.StackPtr;
    vm->IPs[cip].Stacks = ip.Stacks;
    vm->IPs[cip].StacksPtrs = ip.StacksPtrs;
    vm->IPs[cip].StacksPtr = ip.StacksPtr;
    vm->IPs[cip].StacksSize = ip.StacksSize;
    vm->IPs[cip].StackSize = ip.StackSize;
    free(fpvm->IPs);
    fpvm->NumIPs = 0;
    return;
    }
/* **************************************************************** */
/* ***** If not dynamic then execute from correct fingerprint ***** */
/* **************************************************************** */
  else if (Cmd>=EX_DYFP && Cmd<=EX_DYFP+26) Do_DYFP(vm,Cmd);
#ifdef SP3D
  else if (Cmd>=EX_3DSP && Cmd<=EX_3DSP+26) Do_3DSP(vm,Cmd);
#endif
#ifdef ARRY
  else if (Cmd>=EX_ARRY && Cmd<=EX_ARRY+26) Do_ARRY(vm,Cmd);
#endif
#ifdef BASE
  else if (Cmd>=EX_BASE && Cmd<=EX_BASE+26) Do_BASE(vm,Cmd);
#endif
#ifdef BOOL
  else if (Cmd>=EX_BOOL && Cmd<=EX_BOOL+26) Do_BOOL(vm,Cmd);
#endif
#ifdef CPLI
  else if (Cmd>=EX_CPLI && Cmd<=EX_CPLI+26) Do_CPLI(vm,Cmd);
#endif
#ifdef DATE
  else if (Cmd>=EX_DATE && Cmd<=EX_DATE+26) Do_DATE(vm,Cmd);
#endif
#ifdef DIRF
  else if (Cmd>=EX_DIRF && Cmd<=EX_DIRF+26) Do_DIRF(vm,Cmd);
#endif
#ifdef EMEM
  else if (Cmd>=EX_EMEM && Cmd<=EX_EMEM+26) Do_EMEM(vm,Cmd);
#endif
#ifdef EVAR
  else if (Cmd>=EX_EVAR && Cmd<=EX_EVAR+26) Do_EVAR(vm,Cmd);
#endif
#ifdef EXEC
  else if (Cmd>=EX_EXEC && Cmd<=EX_EXEC+26) Do_EXEC(vm,Cmd);
#endif
#ifdef HRTI
  else if (Cmd>=EX_HRTI && Cmd<=EX_HRTI+26) Do_HRTI(vm,Cmd);
#endif
#ifdef ICAL
  else if (Cmd>=EX_ICAL && Cmd<=EX_ICAL+26) Do_ICAL(vm,Cmd);
#endif
#ifdef FILS
  else if (Cmd>=EX_FILE && Cmd<=EX_FILE+26) Do_FILE(vm,Cmd);
#endif
#ifdef FING
  else if (Cmd>=EX_FING && Cmd<=EX_FING+26) Do_FING(vm,Cmd);
#endif
#ifdef FNGR
  else if (Cmd>=EX_FNGR && Cmd<=EX_FNGR+26) Do_FNGR(vm,Cmd);
#endif
#ifdef FIXP
  else if (Cmd>=EX_FIXP && Cmd<=EX_FIXP+26) Do_FIXP(vm,Cmd);
#endif
#ifdef FOBJ
  else if (Cmd>=EX_FOBJ && Cmd<=EX_FOBJ+26) Do_FOBJ(vm,Cmd);
#endif
#ifdef FORK
  else if (Cmd>=EX_FORK && Cmd<=EX_FORK+26) Do_FORK(vm,Cmd);
#endif
#ifdef FPDP
  else if (Cmd>=EX_FPDP && Cmd<=EX_FPDP+26) Do_FPDP(vm,Cmd);
#endif
#ifdef FPRT
  else if (Cmd>=EX_FPRT && Cmd<=EX_FPRT+26) Do_FPRT(vm,Cmd);
#endif
#ifdef FPSP
  else if (Cmd>=EX_FPSP && Cmd<=EX_FPSP+26) Do_FPSP(vm,Cmd);
#endif
#ifdef FRTH
  else if (Cmd>=EX_FRTH && Cmd<=EX_FRTH+26) Do_FRTH(vm,Cmd);
#endif
#ifdef IIPC
  else if (Cmd>=EX_IIPC && Cmd<=EX_IIPC+26) Do_IIPC(vm,Cmd);
#endif
#ifdef IMAP
  else if (Cmd>=EX_IMAP && Cmd<=EX_IMAP+26) Do_IMAP(vm,Cmd);
#endif
#ifdef IMTH
  else if (Cmd>=EX_IMTH && Cmd<=EX_IMTH+26) Do_IMTH(vm,Cmd);
#endif
#ifdef IPMD
  else if (Cmd>=EX_IPMD && Cmd<=EX_IPMD+26) Do_IPMD(vm,Cmd);
#endif
#ifdef JSTR
  else if (Cmd>=EX_JSTR && Cmd<=EX_JSTR+26) Do_JSTR(vm,Cmd);
#endif
#ifdef MODE
  else if (Cmd>=EX_MODE && Cmd<=EX_MODE+26) Do_MODE(vm,Cmd);
#endif
#ifdef LONG
  else if (Cmd>=EX_LONG && Cmd<=EX_LONG+26) Do_LONG(vm,Cmd);
#endif
#ifdef MACR
  else if (Cmd>=EX_MACR && Cmd<=EX_MACR+26) Do_MACR(vm,Cmd);
#endif
#ifdef MODU
  else if (Cmd>=EX_MODU && Cmd<=EX_MODU+26) Do_MODU(vm,Cmd);
#endif
#ifdef MSGQ
  else if (Cmd>=EX_MSGQ && Cmd<=EX_MSGQ+26) Do_MSGQ(vm,Cmd);
#endif
#ifdef MVRS
  else if (Cmd>=EX_MVRS && Cmd<=EX_MVRS+26) Do_MVRS(vm,Cmd);
#endif
#ifdef NCRS
  else if (Cmd>=EX_NCRS && Cmd<=EX_NCRS+26) Do_NCRS(vm,Cmd);
#endif
#ifdef ORTH
  else if (Cmd>=EX_ORTH && Cmd<=EX_ORTH+26) Do_ORTH(vm,Cmd);
#endif
#ifdef PERL
  else if (Cmd>=EX_PERL && Cmd<=EX_PERL+26) Do_PERL(vm,Cmd);
#endif
#ifdef INDV
  else if (Cmd>=EX_INDV && Cmd<=EX_INDV+26) Do_INDV(vm,Cmd);
#endif
#ifdef RAND
  else if (Cmd>=EX_RAND && Cmd<=EX_RAND+26) Do_RAND(vm,Cmd);
#endif
#ifdef REFC
  else if (Cmd>=EX_REFC && Cmd<=EX_REFC+26) Do_REFC(vm,Cmd);
#endif
#ifdef REXP
  else if (Cmd>=EX_REXP && Cmd<=EX_REXP+26) Do_REXP(vm,Cmd);
#endif
#ifdef ROMA
  else if (Cmd>=EX_ROMA && Cmd<=EX_ROMA+26) Do_ROMA(vm,Cmd);
#endif
#ifdef SETS
  else if (Cmd>=EX_SETS && Cmd<=EX_SETS+26) Do_SETS(vm,Cmd);
#endif
#ifdef SGNE
  else if (Cmd>=EX_SGNE && Cmd<=EX_SGNE+26) Do_SGNE(vm,Cmd);
#endif
#ifdef SGNL
  else if (Cmd>=EX_SGNL && Cmd<=EX_SGNL+26) Do_SGNL(vm,Cmd);
#endif
#ifdef SMEM
  else if (Cmd>=EX_SMEM && Cmd<=EX_SMEM+26) Do_SMEM(vm,Cmd);
#endif
#ifdef SMPH
  else if (Cmd>=EX_SMPH && Cmd<=EX_SMPH+26) Do_SMPH(vm,Cmd);
#endif
#ifdef SCKE
  else if (Cmd>=EX_SCKE && Cmd<=EX_SCKE+26) Do_SCKE(vm,Cmd);
#endif
#ifdef SOCK
  else if (Cmd>=EX_SOCK && Cmd<=EX_SOCK+26) Do_SOCK(vm,Cmd);
#endif
#ifdef SORT
  else if (Cmd>=EX_SORT && Cmd<=EX_SORT+26) Do_SORT(vm,Cmd);
#endif
#ifdef STCK
  else if (Cmd>=EX_STCK && Cmd<=EX_STCK+26) Do_STCK(vm,Cmd);
#endif
#ifdef STRN
  else if (Cmd>=EX_STRN && Cmd<=EX_STRN+26) Do_STRN(vm,Cmd);
#endif
#ifdef SUBR
  else if (Cmd>=EX_SUBR && Cmd<=EX_SUBR+26) Do_SUBR(vm,Cmd);
#endif
#ifdef TIME
  else if (Cmd>=EX_TIME && Cmd<=EX_TIME+26) Do_TIME(vm,Cmd);
#endif
#ifdef TRDS
  else if (Cmd>=EX_TRDS && Cmd<=EX_TRDS+26) Do_TRDS(vm,Cmd);
#endif
#ifdef TRGR
  else if (Cmd>=EX_TRGR && Cmd<=EX_TRGR+26) Do_TRGR(vm,Cmd);
#endif
#ifdef TERM
  else if (Cmd>=EX_TERM && Cmd<=EX_TERM+26) Do_TERM(vm,Cmd);
#endif
#ifdef TOYS
  else if (Cmd>=EX_TOYS && Cmd<=EX_TOYS+26) Do_TOYS(vm,Cmd);
#endif
#ifdef WIND
  else if (Cmd>=EX_WIND && Cmd<=EX_WIND+26) Do_WIND(vm,Cmd);
#endif
#ifdef UNIX
  else if (Cmd>=EX_UNIX && Cmd<=EX_UNIX+26) Do_UNIX(vm,Cmd);
#endif
#ifdef TURT
  else if (Cmd>=EX_TURT && Cmd<=EX_TURT+26) Do_TURT(vm,Cmd);
#endif
#ifdef CFFI
  else if (Cmd>=EX_CFFI && Cmd<=EX_CFFI+26) Do_CFFI(vm,Cmd);
#endif
  else switch (Cmd) {
    case     1:Reflect(vm); break;                  /* default r */
    default   :Reflect(vm); break;
    }
}
