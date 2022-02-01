PROJECT=funge
CC=gcc
#DEFINES=-DBASE -DCPLI -DDIRF -DEVAR -DFILS -DFNGR -DFPDP -DFPSP -DFRTH -DFNUL\
#        -DFIXP -DHRTI -DIMAP -DIIPC -DINDV -DMODE -DMODU -DORTH -DPERL -DREFC\
#        -DROMA -DSOCK -DSTRN -DSUBR -DTIME -DTRDS -DTERM -DWIND -DSP3D -DTRGR\
#        -DTURT -DTOYS -DSTCK -DLONG -DSETS -DJSTR -DEXEC -DEMEM -DMACR -DFING\
#        -DREXP -DMSGQ -DSMEM -DSMPH -DPNTR -DDATE -DMVRS -DARRY -DRAND -DFPRT \
#	-DNCRS -DFOBJ -DSORT -DICAL -DSCKE -DIMTH -DBOOL -DSGNL -DFORK -DSGNE\
#	-DIPMD -DUNIX -DCFFI -DHQ9P\
#	-D$(PLATFORM) -Wall

DEFINES=-DBASE -DCPLI -DDIRF -DEVAR -DFILS -DFNGR -DFPDP -DFPSP -DFRTH -DFNUL\
        -DFIXP -DHRTI -DIMAP -DIIPC -DINDV -DMODE -DMODU -DORTH -DPERL -DREFC\
        -DROMA -DSOCK -DSTRN -DSUBR -DTIME -DTRDS -DTERM -DWIND -DSP3D -DTRGR\
        -DTURT -DTOYS -DSTCK -DLONG -DSETS -DJSTR -DEXEC -DEMEM -DMACR -DFING\
        -DREXP -DMSGQ -DSMEM -DSMPH -DPNTR -DDATE -DMVRS -DARRY -DRAND -DFPRT \
	-DNCRS -DFOBJ -DSORT -DICAL -DSCKE -DIMTH -DBOOL -DFORK -DSGNE\
	-DIPMD -DUNIX -DCFFI -DHQ9P\
	-D$(PLATFORM) -Wall

# solaris
#LIBS=-lm -lX11 -lsocket -lnsl
# INCPATH=-I /usr/openwin/include
# PLATFORM=UNIX

# linux
LIBS=-lm -lX11 -lncurses -lffi -ldl
INCPATH=-I /usr/openwin/include
LIBPATH= -L /usr/openwin/lib
PLATFORM=UNIX

# OSX
#LIBPATH = -L/usr/X11/lib/
#INCPATH = -I /usr/X11/include
#LIBS = -lm -lX11 -lncurses
#PLATFORM=OSX

OBJECTS=./bin/main.o\
	./bin/ip.o\
	./bin/vm.o\
        ./bin/ext.o\
        ./bin/mterm.o\
        ./bin/dyfp.o\
        ./bin/xfunge.o\
        ./bin/mem.o\
        ./bin/debugger.o\
        ./bin/stack.o\
        ./bin/version.o\
        ./bin/arry.o\
        ./bin/base.o\
        ./bin/bool.o\
        ./bin/cpli.o\
        ./bin/date.o\
        ./bin/dirf.o\
        ./bin/evar.o\
        ./bin/file.o\
        ./bin/fixp.o\
        ./bin/fngr.o\
        ./bin/fobj.o\
        ./bin/fork.o\
        ./bin/fpdp.o\
        ./bin/fprt.o\
        ./bin/fpsp.o\
        ./bin/frth.o\
        ./bin/hrti.o\
        ./bin/ical.o\
        ./bin/iipc.o\
        ./bin/imap.o\
        ./bin/imth.o\
        ./bin/ipmd.o\
        ./bin/mode.o\
        ./bin/modu.o\
        ./bin/ncrs.o\
        ./bin/orth.o\
        ./bin/perl.o\
        ./bin/indv.o\
        ./bin/rand.o\
        ./bin/refc.o\
        ./bin/roma.o\
        ./bin/sgne.o\
        ./bin/sgnl.o\
        ./bin/strn.o\
        ./bin/sock.o\
        ./bin/scke.o\
        ./bin/subr.o\
        ./bin/time.o\
        ./bin/trds.o\
        ./bin/term.o\
        ./bin/toys.o\
        ./bin/wind.o\
        ./bin/3dsp.o\
        ./bin/fing.o\
	./bin/turt.o\
        ./bin/stck.o\
        ./bin/long.o\
        ./bin/sets.o\
        ./bin/sort.o\
        ./bin/jstr.o\
        ./bin/exec.o\
        ./bin/emem.o\
        ./bin/macr.o\
        ./bin/trgr.o\
        ./bin/rexp.o\
	./bin/msgq.o\
        ./bin/smem.o\
        ./bin/smph.o\
        ./bin/unix.o\
	./bin/mvrs.o\
	./bin/cffi.o\
	./bin/hq9+.o

$(PROJECT):  $(OBJECTS)
	$(CC) $(LIBPATH) $(OBJECTS) $(LIBS) -o $(PROJECT)

./bin/main.o:	main.c funge.h
	$(CC) $(DEFINES) -c main.c -o ./bin/main.o

./bin/ip.o:	ip.c funge.h
	$(CC) $(DEFINES) -c ip.c -o ./bin/ip.o

./bin/vm.o:	vm.c funge.h
	$(CC) $(DEFINES) -c vm.c -o ./bin/vm.o

./bin/ext.o:		ext.c funge.h
	$(CC) $(DEFINES) -c ext.c -o ./bin/ext.o

./bin/mterm.o:	mterm.c
	$(CC) $(DEFINES) -c mterm.c -o ./bin/mterm.o

./bin/xfunge.o:	xfunge.c funge.h
	$(CC) $(DEFINES) $(INCPATH) -c xfunge.c -o ./bin/xfunge.o

./bin/mem.o:		mem.c funge.h
	$(CC) $(DEFINES) -c mem.c -o ./bin/mem.o

./bin/stack.o:	stack.c funge.h
	$(CC) $(DEFINES) -c stack.c -o ./bin/stack.o

./bin/version.o:	version.c funge.h
	$(CC) $(DEFINES) -c version.c -o ./bin/version.o

./bin/debugger.o:	debugger.c funge.h
	$(CC) $(DEFINES) -c debugger.c -o ./bin/debugger.o

./bin/dyfp.o:		ext/dyfp.c funge.h
	$(CC) $(DEFINES) -I. -c ext/dyfp.c -o ./bin/dyfp.o

./bin/arry.o:		ext/arry.c funge.h
	$(CC) $(DEFINES) -I. -c ext/arry.c -o ./bin/arry.o

./bin/bool.o:		ext/bool.c funge.h
	$(CC) $(DEFINES) -I. -c ext/bool.c -o ./bin/bool.o

./bin/base.o:		ext/base.c funge.h
	$(CC) $(DEFINES) -I. -c ext/base.c -o ./bin/base.o

./bin/cpli.o:		ext/cpli.c funge.h
	$(CC) $(DEFINES) -I. -c ext/cpli.c -o ./bin/cpli.o

./bin/date.o:		ext/date.c funge.h
	$(CC) $(DEFINES) -I. -c ext/date.c -o ./bin/date.o

./bin/dirf.o:		ext/dirf.c funge.h
	$(CC) $(DEFINES) -I. -c ext/dirf.c -o ./bin/dirf.o

./bin/evar.o:		ext/evar.c funge.h
	$(CC) $(DEFINES) -I. -c ext/evar.c -o ./bin/evar.o

./bin/emem.o:		ext/emem.c funge.h
	$(CC) $(DEFINES) -I. -c ext/emem.c -o ./bin/emem.o

./bin/exec.o:		ext/exec.c funge.h
	$(CC) $(DEFINES) -I. -c ext/exec.c -o ./bin/exec.o
	
./bin/file.o:		ext/file.c funge.h
	$(CC) $(DEFINES) -I. -c ext/file.c -o ./bin/file.o
	
./bin/fixp.o:		ext/fixp.c funge.h
	$(CC) $(DEFINES) -I. -c ext/fixp.c -o ./bin/fixp.o
	
./bin/fork.o:		ext/fork.c funge.h
	$(CC) $(DEFINES) -I. -c ext/fork.c -o ./bin/fork.o
	
./bin/fing.o:		ext/fing.c funge.h
	$(CC) $(DEFINES) -I. -c ext/fing.c -o ./bin/fing.o
	
./bin/fngr.o:		ext/fngr.c funge.h
	$(CC) $(DEFINES) -I. -c ext/fngr.c -o ./bin/fngr.o
	
./bin/fpdp.o:		ext/fpdp.c funge.h
	$(CC) $(DEFINES) -I. -c ext/fpdp.c -o ./bin/fpdp.o
	
./bin/fobj.o:		ext/fobj.c funge.h
	$(CC) $(DEFINES) -I. -c ext/fobj.c -o ./bin/fobj.o
	
./bin/fprt.o:		ext/fprt.c funge.h
	$(CC) $(DEFINES) -I. -c ext/fprt.c -o ./bin/fprt.o
	
./bin/fpsp.o:		ext/fpsp.c funge.h
	$(CC) $(DEFINES) -I. -c ext/fpsp.c -o ./bin/fpsp.o
	
./bin/frth.o:		ext/frth.c funge.h
	$(CC) $(DEFINES) -I. -c ext/frth.c -o ./bin/frth.o
	
./bin/hrti.o:		ext/hrti.c funge.h
	$(CC) $(DEFINES) -I. -c ext/hrti.c -o ./bin/hrti.o
	
./bin/ical.o:		ext/ical.c funge.h
	$(CC) $(DEFINES) -I. -c ext/ical.c -o ./bin/ical.o
	
./bin/iipc.o:		ext/iipc.c funge.h
	$(CC) $(DEFINES) -I. -c ext/iipc.c -o ./bin/iipc.o
	
./bin/imth.o:		ext/imth.c funge.h
	$(CC) $(DEFINES) -I. -c ext/imth.c -o ./bin/imth.o
	
./bin/imap.o:		ext/imap.c funge.h
	$(CC) $(DEFINES) -I. -c ext/imap.c -o ./bin/imap.o
	
./bin/ipmd.o:		ext/ipmd.c funge.h
	$(CC) $(DEFINES) -I. -c ext/ipmd.c -o ./bin/ipmd.o
	
./bin/jstr.o:		ext/jstr.c funge.h
	$(CC) $(DEFINES) -I. -c ext/jstr.c -o ./bin/jstr.o
	
./bin/long.o:		ext/long.c funge.h
	$(CC) $(DEFINES) -I. -c ext/long.c -o ./bin/long.o
	
./bin/mode.o:		ext/mode.c funge.h
	$(CC) $(DEFINES) -I. -c ext/mode.c -o ./bin/mode.o
	
./bin/modu.o:		ext/modu.c funge.h
	$(CC) $(DEFINES) -I. -c ext/modu.c -o ./bin/modu.o
	
./bin/msgq.o:		ext/msgq.c funge.h
	$(CC) $(DEFINES) -I. -c ext/msgq.c -o ./bin/msgq.o
	
./bin/mvrs.o:		ext/mvrs.c funge.h
	$(CC) $(DEFINES) -I. -c ext/mvrs.c -o ./bin/mvrs.o
	
./bin/ncrs.o:		ext/ncrs.c funge.h
	$(CC) $(DEFINES) -I. -c ext/ncrs.c -o ./bin/ncrs.o
	
./bin/orth.o:		ext/orth.c funge.h
	$(CC) $(DEFINES) -I. -c ext/orth.c -o ./bin/orth.o
	
./bin/perl.o:		ext/perl.c funge.h
	$(CC) $(DEFINES) -I. -c ext/perl.c -o ./bin/perl.o
	
./bin/indv.o:		ext/indv.c funge.h
	$(CC) $(DEFINES) -I. -c ext/indv.c -o ./bin/indv.o
	
./bin/macr.o:		ext/macr.c funge.h
	$(CC) $(DEFINES) -I. -c ext/macr.c -o ./bin/macr.o
	
./bin/rand.o:		ext/rand.c funge.h
	$(CC) $(DEFINES) -I. -c ext/rand.c -o ./bin/rand.o
	
./bin/refc.o:		ext/refc.c funge.h
	$(CC) $(DEFINES) -I. -c ext/refc.c -o ./bin/refc.o
	
./bin/rexp.o:		ext/rexp.c funge.h
	$(CC) $(DEFINES) -I. -c ext/rexp.c -o ./bin/rexp.o
	
./bin/roma.o:		ext/roma.c funge.h
	$(CC) $(DEFINES) -I. -c ext/roma.c -o ./bin/roma.o
	
./bin/sgne.o:		ext/sgne.c funge.h
	$(CC) $(DEFINES) -I. -c ext/sgne.c -o ./bin/sgne.o
	
./bin/sgnl.o:		ext/sgnl.c funge.h
	$(CC) $(DEFINES) -I. -c ext/sgnl.c -o ./bin/sgnl.o
	
./bin/smph.o:		ext/smph.c funge.h
	$(CC) $(DEFINES) -I. -c ext/smph.c -o ./bin/smph.o
	
./bin/smem.o:		ext/smem.c funge.h
	$(CC) $(DEFINES) -I. -c ext/smem.c -o ./bin/smem.o
	
./bin/sort.o:		ext/sort.c funge.h
	$(CC) $(DEFINES) -I. -c ext/sort.c -o ./bin/sort.o
	
./bin/scke.o:		ext/scke.c funge.h
	$(CC) $(DEFINES) -I. -c ext/scke.c -o ./bin/scke.o
	
./bin/sock.o:		ext/sock.c funge.h
	$(CC) $(DEFINES) -I. -c ext/sock.c -o ./bin/sock.o
	
./bin/strn.o:		ext/strn.c funge.h
	$(CC) $(DEFINES) -I. -c ext/strn.c -o ./bin/strn.o
	
./bin/subr.o:		ext/subr.c funge.h
	$(CC) $(DEFINES) -I. -c ext/subr.c -o ./bin/subr.o
	
./bin/time.o:		ext/time.c funge.h
	$(CC) $(DEFINES) -I. -c ext/time.c -o ./bin/time.o
	
./bin/trds.o:		ext/trds.c funge.h
	$(CC) $(DEFINES) -I. -c ext/trds.c -o ./bin/trds.o
	
./bin/turt.o:		ext/turt.c funge.h
	$(CC) $(DEFINES) -I. -c ext/turt.c -o ./bin/turt.o
	
./bin/term.o:		ext/term.c funge.h
	$(CC) $(DEFINES) -I. -c ext/term.c -o ./bin/term.o
	
./bin/toys.o:		ext/toys.c funge.h
	$(CC) $(DEFINES) -I. -c ext/toys.c -o ./bin/toys.o
	
./bin/trgr.o:		ext/trgr.c funge.h
	$(CC) $(DEFINES) -I. -c ext/trgr.c -o ./bin/trgr.o
	
./bin/wind.o:		ext/wind.c funge.h
	$(CC) $(DEFINES) -I. -c ext/wind.c -o ./bin/wind.o
	
./bin/3dsp.o:		ext/3dsp.c ext/vector.c funge.h
	$(CC) $(DEFINES) -I. -c ext/3dsp.c -o ./bin/3dsp.o

./bin/stck.o:		ext/stck.c funge.h
	$(CC) $(DEFINES) -I. -c ext/stck.c -o ./bin/stck.o

./bin/sets.o:		ext/sets.c funge.h
	$(CC) $(DEFINES) -I. -c ext/sets.c -o ./bin/sets.o

./bin/unix.o:		ext/unix.c funge.h
	$(CC) $(DEFINES) -I. -c ext/unix.c -o ./bin/unix.o
	
./bin/cffi.o:		ext/cffi.c funge.h
	$(CC) $(DEFINES) -I. -c ext/cffi.c -o ./bin/cffi.o 
./bin/hq9+.o:		ext/hq9+.c funge.h
	$(CC) $(DEFINES) -I. -c ext/hq9+.c -o ./bin/hq9+.o 
clean:
	-rm -f ./bin/*.o
	-rm -f $(PROJECT)

