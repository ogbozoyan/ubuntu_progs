CC=gcc
CFLAGS=-Wall

LD=$(CC)
LDFLAGS_EXE=-ldl -lncurses -ltinfo
LDFLAGS_LIB=-shared -fPIC

all: small.exe large.exe liblifo.so librr.so
	@echo "Build done"
large.exe: main.c
	@echo "(BUILD) $@"
	@$(CC) $(CFLAGS) -DDYNAMIC_PROCESS_COUNT $< -o $@ $(LDFLAGS_EXE)
small.exe: main.c
	@echo "(BUILD) $@"
	@$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS_EXE)
liblifo.so: lifo.c
	@echo "(BUILD) $@"
	@$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS_LIB)
librr.so: rr.c
	@echo "(BUILD) $@"
	@$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS_LIB)
clean:
	@echo "Clean project"
	@rm -fv  *.exe *.so
