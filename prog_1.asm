section .data

num1 dd 6d
num2 dd 6d

res dd 0d

section .text

global _start

_start:
	mov eax,[num1]
	mov ebx,[num2]
	add eax,ebx
	
	;add eax,'0'
	
	mov [res],eax
	xor eax,eax
	mov eax , 4
	mov ebx , 1
	mov ecx , res
	mov edx ,4
	int 0x80
	
	mov eax ,1
	mov ebx ,0
	int 0x80
	
