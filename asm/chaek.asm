section .text
	global _start
_start:

mov eax, 3
mov ebx, 0
mov ecx, num
mov edx, 1
int 0x80

mov byte [x], 'A'

mov ecx, [num]
sub ecx, '0'

point1:

push ecx

mov eax, 4
mov ebx, 1
mov ecx, x
mov edx, 1
int 0x80

mov eax, 4
mov ebx, 1
mov ecx, space
mov edx, 1
int 0x80

pop ecx

add byte [x], 1

loop point1

mov eax, 1
int 0x80

section .bss
	x resb 1
	num resb 1

section .data
	space db " "
