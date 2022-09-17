section .data

msg1 db "Enter num: ",0xA
len1 equ $-msg1

section .bss
num1 resb 2

section .text

	global _start
_start:
	mov eax,4
	mov ebx,1
	mov ecx,msg1
	mov edx,len1
	int 80h

	mov eax,3
	mov ebx,0
	mov ecx,num1
	mov edx,2
	int 80h
	
	mov ecx,[num1]
	sub ecx,'0'
	mov [num1],ecx
	mov ah,[num1]
	mov al,2
	mul ah;ax = num1*2
	add ax,'0'
	mov [num1],ax 	

	mov eax,4
	mov ebx,1
	mov ecx,num1
	mov edx,2
	int 80h

end:
	mov eax,1
	mov ebx,0
	int 80h
