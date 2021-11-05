includes = ../include
built_ins = ../built_in
binaries = ../bin

objects = main.o hssh.o cmd.o token.o $(built_ins)/echo.o $(built_ins)/exit.o $(built_ins)/pwd.o $(built_ins)/cd.o

$(shell mkdir -p ../bin)

all: core ls cat touch mkdir

core: $(objects)
	cc -o core $(objects) -lreadline

ls: ../ls/ls.o
	cc -o $(binaries)/ls ../ls/ls.o

cat: ../cat/cat.o
	cc -o $(binaries)/cat ../cat/cat.o

touch: ../touch/touch.o
	cc -o $(binaries)/touch ../touch/touch.o

mkdir: ../mkdir/mkdir.o
	cc -o $(binaries)/mkdir ../mkdir/mkdir.o

main.o: $(includes)/cmd.h

hssh.o: $(includes)/color.h $(includes)/hsshdef.h
cmd.o:	$(includes)/exit.h $(includes)/pwd.h $(includes)/cd.h $(includes)/ls.h
token.o:$(includes)/hssh.h

cd.o:	$(includes)/hssh.h
exit.o: $(includes)/hsshdef.h
pwd.o:	$(includes)/hssh.h

.PHONY: clean

clean:
	rm -rf core $(binaries) $(objects) ../ls/ls.o ../mkdir/mkdir.o ../touch/touch.o ../cat/cat.o
