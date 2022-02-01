#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <regex.h>
#include <sys/types.h>

typedef unsigned char byte;

#define MAX_BREAKS   100
#define MAX_FFILES   100
#define MAX_MINIS    100
#define MAX_OVERS    100
#define MAX_VECTORS 1000
#define STACK_SIZE  1000
#define STACKS_SIZE  200
#define MINI_MAX_X    40
#define MINI_MAX_Y    10
#define MAX_EMEM     100

#define FILE_R         0
#define FILE_W         1

#define INT int32_t
#define DINT long long
#define UINT u_int32_t

#define VERSION      "2.03.00"
#define VERSIONINT   20300

#define EX_FIXP      500
#define EX_STRN      600
#define EX_BASE      700
#define EX_FRTH      1000
#define EX_WIND      2000
#define EX_ROMA      3000
#define EX_MODE      3100
#define EX_SUBR      4000
#define EX_FILE      5000
#define EX_REFC      5100
#define EX_ORTH      6000
#define EX_TOYS      7000
#define EX_MODU      7100
#define EX_PERL      7200
#define EX_FPSP      7300
#define EX_FPDP      7400
#define EX_INDV      7500
#define EX_HRTI      7600
#define EX_TERM      7700
#define EX_EVAR      7800
#define EX_IMAP      7900
#define EX_FNGR      8000
#define EX_DIRF      8100
#define EX_CPLI      8200
#define EX_3DSP      8300
#define EX_TRDS      8400
#define EX_SOCK      8500
#define EX_IIPC      8600
#define EX_TIME      8700
#define EX_TURT      8800
#define EX_STCK      8900
#define EX_LONG      9000
#define EX_SETS      9100
#define EX_JSTR      9200
#define EX_EXEC      9300
#define EX_EMEM      9400
#define EX_MACR      9500
#define EX_TRGR      9600
#define EX_FING      9700
#define EX_REXP      9800
#define EX_MSGQ      9900
#define EX_SMEM     10000
#define EX_SMPH     10100
#define EX_SCKE     10200
#define EX_DATE     10300
#define EX_MVRS     10400
#define EX_ARRY     10500
#define EX_RAND     10600
#define EX_FPRT     10700
#define EX_NCRS     10800
#define EX_FOBJ     10900
#define EX_SORT     11000
#define EX_ICAL     11100
#define EX_IMTH     11200
#define EX_DYFP     11300
#define EX_BOOL     11400
#define EX_SGNL     11500
#define EX_FORK     11600
#define EX_SGNE     11700
#define EX_IPMD     11800
#define EX_UNIX     11900
#define EX_CFFI     13000
#define EX_HQ9P     13100

#define FINGER_NORM     0
#define FINGER_ABS      1
#define FINGER_ROLL     2
#define FINGER_SWAP     3

#ifdef OSX
#define HANDPRINT    0x52435355
#endif
#ifdef UNIX
#define HANDPRINT    0x52435355
#endif
#ifdef MSDOS
#define HANDPRINT    0x52435344
#define INT          long int
#endif
#ifdef MSWIN
#define HANDPRINT    0x52435357
#define INT          long int
#endif


#ifdef MAIN
#define PREFIX
#else
#define PREFIX extern
#endif

typedef struct {
  byte Alloc;
  INT x,y,z;
  } VECTOR;

struct MINIFS {
  INT fs[MINI_MAX_X][MINI_MAX_Y];
};

struct _VM;

typedef struct {
  INT x;                               /* x position */
  INT y;                               /* y position */
  INT z;                               /* z position */
  INT StringMode;
  INT DeltaX;
  INT DeltaY;
  INT DeltaZ;
  INT uid;
  INT *Stack;
  INT StackSize;                       /* current size of stack */
  INT StackPtr;                        /* stack pointer */
  INT *Stacks;
  INT *StacksPtrs;
  INT StacksSize;
  INT StacksPtr;
  INT OffsetX;
  INT OffsetY;
  INT OffsetZ;
  int Debugger;
  INT parent;
  int dormant;
  long int Timer;
  long int  OverFinger[MAX_OVERS];
  INT Overloads[26][MAX_OVERS];
  INT NumOvers;
/* to delete 
  INT MiniAlloc[MAX_MINIS];
  struct MINIFS *MiniFs[MAX_MINIS];
  ******* */
  struct _VM*  FPVMs;
  INT    NumVMs;
/* FNGR */
  int FingerMode;
  int FingerSearch;
  int FNGRloaded;
/* ICAL */
  VECTOR NextStack[80];
  int    NextCount;
/* IPMD */
  int    IPMDMode;
/* MODE */
  int HoverMode;
  int InvertMode;
  int QueueMode;
  int SwitchMode;
/* MACR */
  INT mx,my,mz;                        /* Macro block location */
/* TRGR */
  INT tx,ty,tz;                        /* Trigger block location */
/* REXP */
  regex_t    preg;
/* SUBR */
  char       subr_mode;
/* TIME */
  char TimeMode;
/* TRDS */
  INT serial;
  INT RTSpX,RTSpY,RTSpZ;
  INT RTvX,RTvY,RTvZ;
  INT RTTime;
  INT RunTime;
  INT TSpX,TSpY,TSpZ;
  INT TvX,TvY,TvZ;
  INT TTime;
  char SpMode;
  char VMode;
  char TMode;
  INT Jumped;
} IP;

struct FILES {
  FILE *Handle;
  INT  BufferX;
  INT  BufferY;
  INT  BufferZ;
  };

struct MINIIP {
  INT x;
  INT y;
  INT StringMode;
  INT DeltaX;
  INT DeltaY;
  INT cip;
  struct MINIFS *fs;
};

typedef struct {
  INT uid;
  INT stx;
  INT sty;
  INT stz;
  INT dx;
  INT dy;
  INT dz;
  INT stime;
  INT dtime;
  INT serial;
  } TIME_JUMP;

typedef struct {
  INT x,v;
  } CELL;

typedef struct {
  INT   z,Row,Min,Max;
  CELL* Cells;
  int   NumCells;
} ROWS;

typedef struct _VM {
  ROWS        *dFspace;
  int         NumRows;
  INT         *PFs;               /* Storage for fixed memory model */
  INT         uid;                /* next uid to assign */
  INT         cip;                /* Current IP */
  IP          *IPs;               /* IP list */
  INT         NumIPs;             /* Number of IPs in list */
  INT         Mode;               /* number of dimensions */
  INT         TraceMode;
  INT         TraceNoStack;
  INT         WarnMode;
  int         Debugger;
  INT         RetCode;
  INT         Language;           /* running in Funge/93/98/108 mode */
  INT         XDim;               /* Largest used Funge-space cell */
  INT         YDim;
  INT         ZDim;
  INT         XMin;               /* Smallest used Funge-Space cell */
  INT         YMin;
  INT         ZMin;
  INT         MapScreen;
  INT         ModeY;
  long long   ExecCount;          /* Instructions executed */
  long long   CycleCount;         /* Cycle counter */
  INT         delay;
  char*       ProgName;
  int         StackSize;          /* Default stack size on new IPs */
  INT         ShowSummary;
  INT         LargestX;           /* These hold the largest cell */
  INT         LargestY;           /* loaded, relative to the */
  INT         LargestZ;           /* starting cell */
  char        VmType;             /* Type of VM */
  struct _VM* Parent;
  char        fpMode;             /* fingerprint mode */
  char        isDynamic;
/* Debugger */
  VECTOR      BreakPoints[MAX_BREAKS];
  int           NumBPs;
  char          Traps[128];
#ifdef IMAP
  char          Mapper[256];
#endif
#ifdef TRDS
  INT         StopTime;
  INT         PrintTime;
  int         TimeJumped;
/*  TIME_JUMP*  Jumps; */
  IP*         Jumps;
  int         NumJumps;
#endif
#ifdef FILS
  struct FILES Files[MAX_FFILES];
#endif
#ifdef REFC
  VECTOR      Vectors[MAX_VECTORS];
#endif
#ifdef EMEM
  byte*       emems[MAX_EMEM];
  int         ememSizes[MAX_EMEM];
#endif
#ifdef FOBJ
  struct _VM  **objs;
  INT         NumObjs;
#endif
  } VM;


PREFIX VM          *vms;
PREFIX INT         NumVMs;
PREFIX int         ArgC;
PREFIX char        ArgV[50][80];
PREFIX char        CmdLine[255];
PREFIX char        **Envp;
PREFIX char        Fields[40][30];
PREFIX int         NumFields;
PREFIX char        SandBox;
/* TURT */
PREFIX int         TURTOffX;
PREFIX int         TURTOffY;
PREFIX char        XEnabled;
/* TRDS */

/* MVRS */
PREFIX VM          NewVM;


/* vm.c */
PREFIX VM New_VM();
PREFIX void Del_VM(VM* vm);
PREFIX void CycleSubVM(VM* vm);
PREFIX VM Dup_VM(VM* vm);

/* ip.c */
PREFIX IP New_IP(VM* vm);
PREFIX void Insert_IP(VM* vm,IP ip);
PREFIX IP Dup_IP(IP old);
PREFIX void Del_IP(IP* ip);

/* stack.c */
PREFIX VECTOR Pop_Vector(VM* vm);
PREFIX void Push_Vector(VM* vm,VECTOR v);

/* ext.c */
PREFIX void Push_Semantic(VM* vm,int slot,int sem);
PREFIX void Load_Fingerprint_File(VM* vm,int InFile,IP* ip,int vmnum);

/* mem.c */
PREFIX void Find_Limits(VM* vm,INT* minX,INT* minY,INT* maxX,INT* maxY);


PREFIX INT Add_Cell(VM* vm,INT row,INT x,INT y,INT z);
PREFIX void Add_Delta(VM* vm);
PREFIX void Add_Delta_M(struct MINIIP *ip);
PREFIX INT Add_Row(VM* vm,INT y,INT z);
PREFIX INT Alloc_Mini_FS(VM* vm);
PREFIX INT Base_In(INT base);
PREFIX void Base_Out(INT base,UINT v);
PREFIX void Begin_Block(VM* vm,INT n);
PREFIX void Check_Wrap(VM* vm,int dir);
PREFIX void Check_Wrap_M(struct MINIIP *ip);
PREFIX void Clear_Fs(VM* vm);
PREFIX void Cycle(int i);
PREFIX void Cycle_M(VM* vm,struct MINIFS *fs);
PREFIX void Do_Overload(VM* vm,INT func);
PREFIX void End_Block(VM* vm,INT n);
PREFIX INT Exec(VM* vm,INT Cell,int dflag);
PREFIX INT Exec_M(VM* vm,INT Cell,struct MINIIP *ip);
PREFIX INT Find_Row(VM* vm,INT y,INT z);
PREFIX INT Get_Cell(VM* vm);
PREFIX INT Get_Cell_M(struct MINIIP *ip);
PREFIX INT Get_Funge(VM* vm,INT x,INT y,INT z);
PREFIX INT Get_Funge_M(INT x,INT y,struct MINIIP *ip);
PREFIX INT Load_Bin_File(VM* vm,char *FName,INT OffX,INT OffY,INT OffZ);
PREFIX INT Load_File(VM* vm,char *FName,INT OffX,INT OffY,INT OffZ);
PREFIX void Load_Fingerprint(VM* vm);
PREFIX INT Pop(VM* vm);
PREFIX INT Pop_soss(VM* vm);
PREFIX void Pop_String(VM* vm,char* Buffer);
PREFIX void Push(VM* vm,INT value);
PREFIX void Push_soss(VM* vm,INT value);
PREFIX void Push_String(VM* vm,char* Buffer);
PREFIX void Put_Funge(VM* vm,INT x,INT y,INT z,INT value);
PREFIX void Put_Funge_M(INT x,INT y,INT v,struct MINIIP *ip);
PREFIX void Random_Delta(VM* vm);
PREFIX void Random_Delta_M(struct MINIIP *ip);
PREFIX void Randomize();
PREFIX void Reflect(VM* vm);
PREFIX void Reflect_M(struct MINIIP *ip);
PREFIX INT rnd(INT limit);
PREFIX INT sgn(INT i);
PREFIX void Sub_Delta(VM* vm);
PREFIX void Sub_Delta_M(struct MINIIP *ip);
PREFIX void Sys_Info(VM* vm,INT flag);
PREFIX void Turn_Left(VM* vm);
PREFIX void Turn_Left_M(struct MINIIP *ip);
PREFIX void Turn_Right(VM* vm);
PREFIX void Turn_Right_M(struct MINIIP *ip);
PREFIX void Unload_Fingerprint(VM* vm);
PREFIX void Warn(VM* vm,char *msg,char Cell);
PREFIX INT Write_File(VM* vm,char *FName,INT x,INT y,INT z,INT sx,INT sy,INT sz,int f);
#ifdef WIND
PREFIX INT Box(INT w,INT x1,INT y1,INT x2,INT y2);
PREFIX INT Close_GC(INT w);
PREFIX INT Close_Window(INT w);
PREFIX INT Event(VM* vm,INT w);
PREFIX INT Install_Handler(INT w,INT evnt,INT x,INT y,INT z);
PREFIX INT Line(INT w,INT x1,INT y1,INT x2,INT y2);
PREFIX INT Lower_Window(INT w);
PREFIX INT Move_Window(INT w,INT x,INT y);
PREFIX INT New_Window(INT x,INT y,INT wd,INT h);
PREFIX INT Open_GC(INT w);
PREFIX INT Point(INT w,INT x,INT y);
PREFIX INT Raise_Window(INT w);
PREFIX INT Size_Window(INT w,INT x,INT y);
PREFIX INT Text(INT w,char *buffer,INT x,INT y);
PREFIX void Foreground_Color(INT w,int r,int g,int b);
PREFIX void Win_Init();
PREFIX void Copy_Backing(INT w);
#endif

extern int Debug(VM* vm,int cell);
extern void SwapFingerprint(VM* vm,int dest,int src);
extern void CopyFingerprint(VM* vm,int dest,int src);
extern void Delay(int sec);
extern void ClrScr();
extern void Output(char* Buffer);
extern void Input(char* Buffer);
extern void ClrEos();
extern void ClrEol();
extern void GotoXY(int x,int y);
extern void CursorDown(int num);
extern void CursorUp(int num);
extern int Parse(char *buffer);
extern void Cycle_TURT();
extern int Unload_Semantic(VM* vm,int slot);
extern void CopyStack(VM* vm,int dest,int src);
extern void version();
extern void Reset_VM(VM* vm);

extern void Load_DYFP(IP* ip);
extern void Do_DYFP(VM* vm,int Cmd);

/* *** Extensions *** */
extern void Load_3DSP(VM* vm,long int FingerPrint);
extern void Load_ARRY(VM* vm,long int FingerPrint);
extern void Load_BASE(VM* vm,long int FingerPrint);
extern void Load_BOOL(VM* vm,long int FingerPrint);
extern void Load_CPLI(VM* vm,long int FingerPrint);
extern void Load_DATE(VM* vm,long int FingerPrint);
extern void Load_DIRF(VM* vm,long int FingerPrint);
extern void Load_EMEM(VM* vm,long int FingerPrint);
extern void Load_EXEC(VM* vm,long int FingerPrint);
extern void Load_EVAR(VM* vm,long int FingerPrint);
extern void Load_FILE(VM* vm,long int FingerPrint);
extern void Load_FING(VM* vm,long int FingerPrint);
extern void Load_FIXP(VM* vm,long int FingerPrint);
extern void Load_FNGR(VM* vm,long int FingerPrint);
extern void Load_FOBJ(VM* vm,long int FingerPrint);
extern void Load_FORK(VM* vm,long int FingerPrint);
extern void Load_FPDP(VM* vm,long int FingerPrint);
extern void Load_FPRT(VM* vm,long int FingerPrint);
extern void Load_FPSP(VM* vm,long int FingerPrint);
extern void Load_FRTH(VM* vm,long int FingerPrint);
extern void Load_HRTI(VM* vm,long int FingerPrint);
extern void Load_ICAL(VM* vm,long int FingerPrint);
extern void Load_IIPC(VM* vm,long int FingerPrint);
extern void Load_IMAP(VM* vm,long int FingerPrint);
extern void Load_IMTH(VM* vm,long int FingerPrint);
extern void Load_INDV(VM* vm,long int FingerPrint);
extern void Load_IPMD(VM* vm,long int FingerPrint);
extern void Load_JSTR(VM* vm,long int FingerPrint);
extern void Load_LONG(VM* vm,long int FingerPrint);
extern void Load_MACR(VM* vm,long int FingerPrint);
extern void Load_MODE(VM* vm,long int FingerPrint);
extern void Load_MODU(VM* vm,long int FingerPrint);
extern void Load_MSGQ(VM* vm,long int FingerPrint);
extern void Load_MVRS(VM* vm,long int FingerPrint);
extern void Load_NCRS(VM* vm,long int FingerPrint);
extern void Load_ORTH(VM* vm,long int FingerPrint);
extern void Load_PERL(VM* vm,long int FingerPrint);
extern void Load_PNTR(VM* vm,long int FingerPrint);
extern void Load_RAND(VM* vm,long int FingerPrint);
extern void Load_REFC(VM* vm,long int FingerPrint);
extern void Load_REXP(VM* vm,long int FingerPrint);
extern void Load_ROMA(VM* vm,long int FingerPrint);
extern void Load_SCKE(VM* vm,long int FingerPrint);
extern void Load_SETS(VM* vm,long int FingerPrint);
extern void Load_SGNE(VM* vm,long int FingerPrint);
extern void Load_SGNL(VM* vm,long int FingerPrint);
extern void Load_SMEM(VM* vm,long int FingerPrint);
extern void Load_SMPH(VM* vm,long int FingerPrint);
extern void Load_SOCK(VM* vm,long int FingerPrint);
extern void Load_SORT(VM* vm,long int FingerPrint);
extern void Load_STCK(VM* vm,long int FingerPrint);
extern void Load_STRN(VM* vm,long int FingerPrint);
extern void Load_SUBR(VM* vm,long int FingerPrint);
extern void Load_TERM(VM* vm,long int FingerPrint);
extern void Load_TIME(VM* vm,long int FingerPrint);
extern void Load_TOYS(VM* vm,long int FingerPrint);
extern void Load_TRDS(VM* vm,long int FingerPrint);
extern void Load_TRGR(VM* vm,long int FingerPrint);
extern void Load_TURT(VM* vm,long int FingerPrint);
extern void Load_UNIX(VM* vm,long int FingerPrint);
extern void Load_WIND(VM* vm,long int FingerPrint);
extern void Load_CFFI(VM* vm,long int FingerPrint);
extern void Load_HQ9P(VM* vm,long int FingerPrint);

extern void Do_3DSP(VM* vm,int Cmd);
extern void Do_ARRY(VM* vm,int Cmd);
extern void Do_BASE(VM* vm,int Cmd);
extern void Do_BOOL(VM* vm,int Cmd);
extern void Do_CPLI(VM* vm,int Cmd);
extern void Do_DATE(VM* vm,int Cmd);
extern void Do_DIRF(VM* vm,int Cmd);
extern void Do_EMEM(VM* vm,int Cmd);
extern void Do_EVAR(VM* vm,int Cmd);
extern void Do_EXEC(VM* vm,int Cmd);
extern void Do_FILE(VM* vm,int Cmd);
extern void Do_FING(VM* vm,int Cmd);
extern void Do_FIXP(VM* vm,int Cmd);
extern void Do_FNGR(VM* vm,int Cmd);
extern void Do_FOBJ(VM* vm,int Cmd);
extern void Do_FORK(VM* vm,int Cmd);
extern void Do_FPDP(VM* vm,int Cmd);
extern void Do_FPRT(VM* vm,int Cmd);
extern void Do_FPSP(VM* vm,int Cmd);
extern void Do_FRTH(VM* vm,int Cmd);
extern void Do_HRTI(VM* vm,int Cmd);
extern void Do_ICAL(VM* vm,int Cmd);
extern void Do_IIPC(VM* vm,int Cmd);
extern void Do_IMAP(VM* vm,int Cmd);
extern void Do_IMTH(VM* vm,int Cmd);
extern void Do_INDV(VM* vm,int Cmd);
extern void Do_IPMD(VM* vm,int Cmd);
extern void Do_JSTR(VM* vm,int Cmd);
extern void Do_LONG(VM* vm,int Cmd);
extern void Do_MACR(VM* vm,int Cmd);
extern void Do_MODE(VM* vm,int Cmd);
extern void Do_MODU(VM* vm,int Cmd);
extern void Do_MSGQ(VM* vm,int Cmd);
extern void Do_MVRS(VM* vm,int Cmd);
extern void Do_NCRS(VM* vm,int Cmd);
extern void Do_ORTH(VM* vm,int Cmd);
extern void Do_PERL(VM* vm,int Cmd);
extern void Do_PNTR(VM* vm,int Cmd);
extern void Do_RAND(VM* vm,int Cmd);
extern void Do_REFC(VM* vm,int Cmd);
extern void Do_REXP(VM* vm,int Cmd);
extern void Do_ROMA(VM* vm,int Cmd);
extern void Do_SCKE(VM* vm,int Cmd);
extern void Do_SETS(VM* vm,int Cmd);
extern void Do_SGNE(VM* vm,int Cmd);
extern void Do_SGNL(VM* vm,int Cmd);
extern void Do_SMEM(VM* vm,int Cmd);
extern void Do_SMPH(VM* vm,int Cmd);
extern void Do_SOCK(VM* vm,int Cmd);
extern void Do_SORT(VM* vm,int Cmd);
extern void Do_STCK(VM* vm,int Cmd);
extern void Do_STRN(VM* vm,int Cmd);
extern void Do_SUBR(VM* vm,int Cmd);
extern void Do_TERM(VM* vm,int Cmd);
extern void Do_TIME(VM* vm,int Cmd);
extern void Do_TOYS(VM* vm,int Cmd);
extern void Do_TRDS(VM* vm,int Cmd);
extern void Do_TRGR(VM* vm,int Cmd);
extern void Do_TURT(VM* vm,int Cmd);
extern void Do_UNIX(VM* vm,int Cmd);
extern void Do_WIND(VM* vm,int Cmd);
extern void Do_CFFI(VM* vm,int Cmd);
extern void Do_HQ9P(VM* vm,int Cmd);

extern void Unload_3DSP(VM* vm);
extern void Unload_BASE(VM* vm);
extern void Unload_CPLI(VM* vm);
extern void Unload_DIRF(VM* vm);
extern void Unload_EVAR(VM* vm);
extern void Unload_FILE(VM* vm);
extern void Unload_FIXP(VM* vm);
extern void Unload_FNGR(VM* vm);
extern void Unload_FORK(VM* vm);
extern void Unload_FPDP(VM* vm);
extern void Unload_FPSP(VM* vm);
extern void Unload_FRTH(VM* vm);
extern void Unload_HRTI(VM* vm);
extern void Unload_IIPC(VM* vm);
extern void Unload_IMAP(VM* vm);
extern void Unload_INDV(VM* vm);
extern void Unload_MODE(VM* vm);
extern void Unload_MODU(VM* vm);
extern void Unload_ORTH(VM* vm);
extern void Unload_PERL(VM* vm);
extern void Unload_PNTR(VM* vm);
extern void Unload_REFC(VM* vm);
extern void Unload_ROMA(VM* vm);
extern void Unload_SOCK(VM* vm);
extern void Unload_STRN(VM* vm);
extern void Unload_SUBR(VM* vm);
extern void Unload_TERM(VM* vm);
extern void Unload_TIME(VM* vm);
extern void Unload_TOYS(VM* vm);
extern void Unload_TRDS(VM* vm);
extern void Unload_TURT(VM* vm);
extern void Unload_WIND(VM* vm);
extern void Unload_STCK(VM* vm);
extern void Unload_LONG(VM* vm);
extern void Unload_SETS(VM* vm);
extern void Unload_JSTR(VM* vm);
extern void Unload_EXEC(VM* vm);
extern void Unload_EMEM(VM* vm);
extern void Unload_MACR(VM* vm);
extern void Unload_TRGR(VM* vm);
extern void Unload_FING(VM* vm);
extern void Unload_REXP(VM* vm);
extern void Unload_MSGQ(VM* vm);
extern void Unload_SMEM(VM* vm);
extern void Unload_SMPH(VM* vm);
extern void Unload_SCKE(VM* vm);
extern void Unload_DATE(VM* vm);
extern void Unload_MVRS(VM* vm);
extern void Unload_RAND(VM* vm);
extern void Unload_FPRT(VM* vm);
extern void Unload_NCRS(VM* vm);
extern void Unload_FOBJ(VM* vm);
extern void Unload_SORT(VM* vm);
extern void Unload_ICAL(VM* vm);
extern void Unload_ARRY(VM* vm);
extern void Unload_IMTH(VM* vm);
extern void Unload_IPMD(VM* vm);
extern void Unload_BOOL(VM* vm);
extern void Unload_SGNE(VM* vm);
extern void Unload_SGNL(VM* vm);
extern void Unload_UNIX(VM* vm);
extern void Unload_CFFI(VM* vm);
extern void Unload_HQ9P(VM* vm);


