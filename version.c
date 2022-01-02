#include "funge.h"

void version() {
  int j;
    printf("\n");
      printf("RC/Funge-98 V%s Build:12/19/2008\n",VERSION);
      printf("By Michael H. Riley\n");
      printf("Handprint: 0x%x\n",HANDPRINT);
      printf("Fingerprints: "); j=0;
#ifdef SP3D
      printf("\"3DSP\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef ARRY
      printf("\"ARRY\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef BASE
      printf("\"BASE\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef BOOL
      printf("\"BOOL\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef CPLI
      printf("\"CPLI\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef DATE
      printf("\"DATE\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef DIRF
      printf("\"DIRF\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef EMEM
      printf("\"EMEM\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef EVAR
      printf("\"EVAR\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef EXEC
      printf("\"EXEC\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef FILS
      printf("\"FILE\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef FING
      printf("\"FING\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef FIXP
      printf("\"FIXP\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef FNGR
      printf("\"FNGR\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef FPDP
      printf("\"FPDP\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef FOBJ
      printf("\"FOBJ\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef FORK
      printf("\"FORK\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef FPRT
      printf("\"FPRT\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef FPSP
      printf("\"FPSP\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef FRTH
      printf("\"FRTH\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef HRTI
      printf("\"HRTI\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef ICAL
      printf("\"ICAL\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef IIPC
      printf("\"IIPC\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef IMAP
      printf("\"IMAP\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef IMTH
      printf("\"IMTH\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef INDV
      printf("\"INDV\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef IPMD
      printf("\"IPMD\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef JSTR
      printf("\"JSTR\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef LONG
      printf("\"LONG\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef MACR
      printf("\"MACR\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef MODE
      printf("\"MODE\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef MODU
      printf("\"MODU\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef MSGQ
      printf("\"MSGQ\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef MVRS
      printf("\"MVRS\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef NCRS
      printf("\"NCRS\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef FNUL
      printf("\"NULL\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef ORTH
      printf("\"ORTH\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef PERL
      printf("\"PERL\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef PNTR
      printf("\"PNTR\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef RAND
      printf("\"RAND\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef REFC
      printf("\"REFC\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef REXP
      printf("\"REXP\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef ROMA
      printf("\"ROMA\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef SETS
      printf("\"SETS\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef SGNE
      printf("\"SGNE\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef SGNL
      printf("\"SGNL\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef SMEM
      printf("\"SMEM\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef SMPH
      printf("\"SMPH\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef SCKE
      printf("\"SCKE\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef SOCK
      printf("\"SOCK\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef SORT
      printf("\"SORT\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef STCK
      printf("\"STCK\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef STRN
      printf("\"STRN\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef SUBR
      printf("\"SUBR\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef TIME
      printf("\"TIME\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef TRDS
      printf("\"TRDS\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef TERM
      printf("\"TERM\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef TRGR
      printf("\"TRGR\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef TOYS
      printf("\"TOYS\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef TURT
      printf("\"TURT\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef UNIX
      printf("\"UNIX\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
#ifdef WIND
      printf("\"WIND\" ");
      if (++j==8) { printf("\n%14c",' '); j=0; }
#endif
      printf("\n");
      }
