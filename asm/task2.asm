section .data

numf db "Enter first num: ",10
lenf equ $-numf
nums db "Enter second num: ",10
lens equ $-nums
sln equ 0xA
section .bss

num1 resb 2
num2 resb 2
resu resb 2 

section .text
	global _start

_start:
	mov eax,4
	mov ebx,1
	mov ecx,numf
	mov edx,lenf
	int 0x80
	
	mov eax,3
	mov ebx,0
	mov ecx,num1
	mov edx,2
	int 0x80
	
	mov eax,4
	mov ebx,1
	mov ecx,nums
	mov edx,lens
	int 0x80

	mov eax,3
	mov ebx,0
	mov ecx,num2
	mov edx,2
	int 0x80
	
	mov al,[num1]
	sub al,'0' ;atoi
	mov bl,[num2]
	sub bl,'0' ;atoi
	add al,bl
	
	cmp al, 10
	
	jl less
	jge debug

end:	mov eax,1
	mov ebx,0
	int 0x80
less:
	add al,'0';itoa to string
	mov [resu],al

	mov eax,4
	mov ebx,1
	mov ecx,resu
	mov edx,4
	int 0x80
	jmp end
debug:
	mov bl,0x31
	mov [resu],bl
	add al,'0' ;itoa to string
	sub al,10 ; downgrade razryad //12 -> 2
	add [resu + 1],al
	mov eax,4
	mov ebx,1
	mov ecx,resu
	mov edx,4
	int 80h
	jmp end
