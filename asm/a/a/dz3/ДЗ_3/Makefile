all: build

build: z1.exe z2.exe z3.exe z4.exe
	@echo "Build complete\n"

%.o: %.asm
	@nasm -felf32 $<
 
%.exe: %.o
	@ld -m elf_i386 $< -o $@

clean:
	@rm -f *.o *.exe