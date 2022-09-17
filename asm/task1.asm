section .data
welcome db "Enter: ",10
len db $-welcome
section .bss
buf resb 1

section .text
global _start

_start:
	mov eax,4
	mov ebx,1
	mov ecx,welcome
	mov edx,len
	int 0x80
	
	;scanf
	mov eax,3
	mov ebx,0
	mov ecx,buf
	mov edx,1
	int 0x80
        
	xor eax,eax
	
	mov eax,[buf]
	sub eax,'0';atoi
	inc eax
	add eax,'0';itoa
	mov [buf],eax
	
	xor eax,eax

	mov eax,4
	mov ebx,1
	mov ecx,buf
	mov edx,1
	int 0x80	
		
	jmp endprog

endprog:
	mov eax,1
	mov ebx,0
	int 0x80
