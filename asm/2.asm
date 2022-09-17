section .text
	global _start
_start:

	mov eax, 4
	mov ebx, 1
	mov ecx, msg1
	mov edx, len1
	int 0x80

	mov eax, 3
	mov ebx, 0
	mov ecx, num1
	mov edx, 2
	int 0x80

        mov eax, 4
        mov ebx, 1
        mov ecx, msg2
        mov edx, len2
        int 0x80

        mov eax, 3
        mov ebx, 0
        mov ecx, num2
        mov edx, 2
        int 0x80

	mov eax, 4
	mov ebx, 1
	mov ecx, msg
	mov edx, len
	int 0x80	

	mov al, [num1]
	sub al, '0'
	mov bl, [num2]
	sub bl, '0'
	add al, bl
	
	cmp al, 10
	jge  more10

less10:
	
	add al, '0'
	mov [num1], al

	mov eax, 4
        mov ebx, 1
        mov ecx, num1
        mov edx, 2
        int 0x80

	mov eax, 4
	mov ebx, 1
	mov ecx, prv
	mov edx, 1
	int 0x80

	jmp exit

more10:

	mov bl, 0x31
	mov [sum], bl

	add al, '0'
	sub al, 10
	mov [sum+1], al

	mov eax, 4
	mov ebx, 1
	mov ecx, sum
	mov edx, 2
	int 0x80

	mov eax, 4
        mov ebx, 1
        mov ecx, prv
        mov edx, 1
        int 0x80
exit:
	mov eax, 1
	int 0x80

section .data
	msg1 db "Enter the first number:", 0xA
	len1 equ $ -msg1

	msg2 db "Enter the second number:", 0xA
        len2 equ $ -msg2

	msg db "The result is:", 0xA
        len equ $ -msg

	prv db 0xA

segment .bss
	num1 resb 2
	num2 resb 2
	sum resb 2
