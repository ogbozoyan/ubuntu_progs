SYS_EXIT  equ 1
SYS_READ  equ 3
SYS_WRITE equ 4
STDIN     equ 0
STDOUT    equ 1
section .data
	array db 1,2
	      db 2,3
	size equ $-array
section .text
	global _start
_start:
	mov eax, SYS_WRITE
	mov ebx, STDOUT
	mov ecx, array
	mod edx, size
	int 0x80

	mov eax, SYS_EXIT
	int 0x80
