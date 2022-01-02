/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#define MAIN
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "funge.h"

/* ************************************************************* */
/* **** This function copies the stack of one IP to another **** */
/* ************************************************************* */
void CopyStack(VM* vm,int dest,int src)
{
  int i;
  for (i=0;i<vm->StackSize;i++)
    vm->IPs[dest].Stack[i]=vm->IPs[src].Stack[i];
}

INT sgn(INT i)
{
  if (i<0) return -1;
  else if (i>0) return 1;
  else return 0;
}

void Randomize()
{
  time_t t;
  t=time(&t);
  t&=0xfffff;
  srand(t);
}

INT rnd(INT limit)
{
  float val;
  val=(float)rand()/(float)RAND_MAX;
  val*=(float)limit;
  return (INT)(val);
}

void Warn(VM* vm,char *msg,char Cell) {
  if (vm->WarnMode!=0) printf("%s%c (%d)\n",msg,Cell,Cell);
  }

/* *************************************************************************
   *** This function was modified by Jesse Van Herk to allow for loading ***
   *** of funge/3d files                                                 ***
   ************************************************************************* */
INT Load_File(VM* vm,char *FName,INT OffX,INT OffY,INT OffZ) {
  INT x,y,z;
  int count;
  char lineEnd;
  int InFile;
  unsigned char *Ptr;
  unsigned char Buffer[1000];
  lineEnd = 0;
  x=OffX; y=OffY; z=OffZ;
  vm->LargestX=0; vm->LargestY=0; vm->LargestZ=0;
  InFile=open(FName,O_RDONLY);
  if (InFile != -1) {
    while ((count=read(InFile,Buffer,1000)) > 0) {
      Ptr=Buffer;
      while (count > 0) {
        if (*Ptr == 12) {
          if (vm->Mode > 2) {
            z++;
            x = OffX;
            y = OffY;
            }
          }
        else if (*Ptr == 10 || *Ptr == 13) {
          if (lineEnd == 0) lineEnd = *Ptr;
          if (*Ptr == lineEnd && lineEnd != 0) {
            y++;
            x = OffX;
            }
          }
        else {
          if (x>vm->LargestX) vm->LargestX=x;
          if (y>vm->LargestY) vm->LargestY=y;
          if (z>vm->LargestZ) vm->LargestZ=z;
          if (*Ptr != ' ') Put_Funge(vm,x++,y,z,*Ptr);
            else x++;
          }
        Ptr++;
        count--;
        }
      }
    vm->LargestX=vm->LargestX-OffX+1;
    vm->LargestY=vm->LargestY-OffY+1;
    vm->LargestZ=vm->LargestZ-OffZ+1;
    return 1;
    }
  else return 0;
}


INT Load_Bin_File(VM* vm,char *FName,INT OffX,INT OffY,INT OffZ)
{
  INT x,y,z;
  int InFile;
  char Buffer[1000];
  y=OffY; z=OffZ;
  vm->LargestX=0; vm->LargestY=0; vm->LargestZ=0;
  InFile = open(FName,O_RDONLY);
  x=OffX;
  if (InFile != -1) {
    while (read(InFile,Buffer,1) == 1) {
      Put_Funge(vm,x++,y,z,Buffer[0]);
      if (x>vm->LargestX && Buffer[0] != ' ') vm->LargestX=x; /* JVH */
      if (y>vm->LargestY && Buffer[0] != ' ') vm->LargestY=y; /* JVH */
      }
    close(InFile);
    vm->LargestX=vm->LargestX-OffX;
    vm->LargestY=vm->LargestY-OffY;
    vm->LargestZ=vm->LargestZ-OffZ;
    return 1;
    }
  else return 0;
}

INT Write_File(VM* vm,char *FName,INT x,INT y,INT z,INT sx,INT sy,INT sz,int f)
{
  INT ix,iy,iz,c;
  FILE *OutFile;
  int Spaces;
  OutFile=fopen(FName,"wb");
  if (OutFile!=NULL) {
    for (iz=z;iz<z+sz;iz++)
      for (iy=y;iy<y+sy;iy++) {
        Spaces=0;
        for (ix=x;ix<x+sx;ix++) {
          c=Get_Funge(vm,ix,iy,iz);
          if (c!=32 && Spaces>0 && f!=0) {
            while ((Spaces--)>0) fprintf(OutFile," ");
            Spaces=0;
            }
            if (c!=32 || f==0)
              fprintf(OutFile,"%c",Get_Funge(vm,ix,iy,iz));
              else if (c==32) Spaces++;
           }
        if (y!=(y+sy)) fprintf(OutFile,"\n");
        }
   
    fclose(OutFile);
    return 1;
    }
  else return 0;
}

int main(INT argc,char *argv[],char *envp[])
{
  INT i,j,f;
  long sclk,eclk;
  float rclk,rexec;
  Envp=envp;
  Randomize();
#ifdef WIND
  Win_Init();
#endif
  f=0;
  SandBox = 'N';
  XEnabled = 'N';
  strcpy(CmdLine,argv[0]);
  for (i=1;i<argc;i++) {
    strcpy(ArgV[i],argv[i]);
    }
  ArgC=argc;
  i=1;
  vms = (VM*)malloc(sizeof(VM));
  if (vms == NULL) {
    printf("Could not allocate VM memory. Aborting.\n");
    exit(-1);
    }
  vms[0] = New_VM();
  NumVMs = 1;
  while (i<argc) {
    if (strcmp(argv[i],"-h")==0) {
      printf("Usage: funge [options] file\n\n");
      printf("Options:\n");
      printf("  -1      - Operate in Unefunge mode\n");
      printf("  -2      - Operate in Befunge mode\n");
      printf("  -3      - Operate in Treefunge mode\n");
      printf("  -93     - Allow only Funge/93 instrutions\n");
      printf("  -98     - Run in Funge/98 Mode (default)\n");
      printf("  -108    - Run in Funge/98 Mode\n");
      printf("  -d      - Enable debugger\n");
      printf("  -D      - Delay between instruction execution\n");
      printf("  -i n    - Change stack size (def 1000)\n");
      printf("  -s      - Map Funge-space to screen\n");
      printf("  -sb     - Enable sandbox mode\n");
      printf("  -S      - Suppress summary\n");
      printf("  -t      - Enable tracing mode\n");
      printf("  -ux     - Use XWdinows for TURT\n");
      printf("  -v      - Show version\n");
      printf("  -w      - Enable warnings\n");
      printf("  -x n    - Change X size for fixed model (def 100)\n");
      printf("  -y n    - Change Y size for fixed model (def 100)\n");
      printf("  -z n    - Change Z size for fixed model (def 1)\n");
      printf("  -Y      - Use official version of 'y' command\n");
      exit(0);
      }
    else if (strcmp(argv[i],"-vm")==0) {
      NumVMs++;
      vms = (VM*)realloc(vms,sizeof(VM)*NumVMs);
      if (vms == NULL) {
        printf("Could not allocate VM memory. Aborting.\n");
        exit(-1);
        }
      vms[NumVMs-1] = New_VM();
      }
    else if (strcmp(argv[i],"-1")==0) vms[NumVMs-1].Mode=1;
    else if (strcmp(argv[i],"-2")==0) vms[NumVMs-1].Mode=2;
    else if (strcmp(argv[i],"-3")==0) vms[NumVMs-1].Mode=3;
    else if (strcmp(argv[i],"-93")==0) vms[NumVMs-1].Language = 93;
    else if (strcmp(argv[i],"-98")==0) vms[NumVMs-1].Language = 98;
    else if (strcmp(argv[i],"-108")==0) vms[NumVMs-1].Language = 108;
    else if (strcmp(argv[i],"-f2")==0) vms[NumVMs-1].fpMode='B';
    else if (strcmp(argv[i],"-d")==0) {
      vms[NumVMs-1].Debugger=1;
      vms[NumVMs-1].TraceMode=0;
      }
    else if (strcmp(argv[i],"-i")==0) {
      i++;
      sscanf(argv[i],"%d",&(vms[NumVMs-1].StackSize));
      }
    else if (strcmp(argv[i],"-D")==0) vms[NumVMs-1].delay=1;
    else if (strcmp(argv[i],"-s")==0) { vms[NumVMs-1].MapScreen=1; setbuf(stdout,NULL); ClrScr(); }
    else if (strcmp(argv[i],"-sb")==0) SandBox = 'Y';
    else if (strcmp(argv[i],"-S")==0) vms[NumVMs-1].ShowSummary=0;
    else if (strcmp(argv[i],"-t")==0) vms[NumVMs-1].TraceMode=1;
    else if (strcmp(argv[i],"-ns")==0) vms[NumVMs-1].TraceNoStack=1;
    else if (strcmp(argv[i],"-ux")==0) XEnabled = 'Y';
    else if (strcmp(argv[i],"-w")==0) vms[NumVMs-1].WarnMode=1;
    else if (strcmp(argv[i],"-Y")==0) vms[NumVMs-1].ModeY=0;
    else if (strcmp(argv[i],"-v")==0) {
      version();
      }
    else if (vms[NumVMs-1].ProgName == NULL) {
      Clear_Fs(&(vms[NumVMs-1]));
      Insert_IP(&(vms[NumVMs-1]),New_IP(&(vms[NumVMs-1])));
      f=f|Load_File(&(vms[NumVMs-1]),argv[i],0,0,0);
      if (f == 1) {
        vms[NumVMs-1].ProgName = (char*)malloc(strlen(argv[i])+1);
        if (vms[NumVMs-1].ProgName == NULL) {
          printf("Could not allocate memory for vms[0].ProgName\n");
          exit(-1);
          }
        strcpy(vms[NumVMs-1].ProgName,argv[i]);
        }
      }
    i++;
    }
  f = 0;
  ArgC = 0;
  for (i=1;i<argc;i++) {
    if (vms[0].ProgName != NULL && strcmp(argv[i],vms[0].ProgName) == 0) f = 1;
    if (f==1) {
      strcpy(ArgV[ArgC],argv[i]);
      ArgC++;
      }
    }
  sclk=clock();
  if (f==1)  while (NumVMs>0) {
    for (i=0; i<NumVMs; i++) {
      Cycle(i);
      if (vms[i].NumIPs == 0) {
        if (vms[i].ShowSummary==1) {
          eclk=clock()-sclk;
          printf("\n");
          printf("VM %s ended\n",vms[i].ProgName);
          printf("  Instructions Executed: %lld in %lld cycles\n",vms[i].ExecCount,vms[i].CycleCount);
          rclk=eclk; rclk/=CLOCKS_PER_SEC;
          printf("        Execution time : %-6.2f seconds\n",rclk);
          rexec=vms[i].ExecCount;
          printf("Instructions per second: %-10.2f\n",rexec/rclk);
          }
        if (NumVMs != 0) {
          for (j=i; j<NumVMs-1; j++) vms[j] = vms[j+1];
          if (i>0) i--;
          }
        NumVMs--;
        }
      }
    }
  printf("Exiting with return code = %d\n",vms[0].RetCode);
/*
  for (i=0; i<MAX_EMEM; i++)
    if (emems[i] != NULL) free(emems[i]);
  if (ProgName != NULL) {
    free(ProgName);
    }
#if TRDS
  if (Jumps != NULL) free(Jumps);
#endif
*/
  return vms[0].RetCode;
}

