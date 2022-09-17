section .data

msg db "He: ",0xA
len1 equ $-msg

section .bss

string resb 10

section .text

global _start

_start:
	mov eax,4
	mov ebx,1
	mov ecx,msg
	mov edx,len1
	int 80h
	
	mov eax,3
	mov ebx,0
	mov ecx,string
	mov edx,10
	int 80h
	
	mov al,[string]
	mov ah,[string+3]
	mov [string],ah
	mov [string+3],al

	mov eax,4
	mov ebx,1
	mov ecx,string
	mov edx,10
	int 80h
	
	mov eax,1
	mov ebx,0
	int 80h
