;sub ascii '0' to convert do decimial number
;add '0' to to convert the sum from decimal to ASCII
SYS_EXIT  equ 1
SYS_READ  equ 3
SYS_WRITE equ 4
STDIN     equ 0
STDOUT    equ 1

section .data
	msg1 db 'Enter a digit',10
	len1 equ $- msg1
	msg2 db 'Conveting from ascii to dec...',10
	len2 equ $- msg2
	msg3 db 'Done',10
	len3 equ $- msg3
section .bss
	num resb 4 ;int type
	res resb 100 
section .text
	global _start 
_start: ;main()
	mov eax , SYS_WRITE
	mov ebx , STDOUT
	mov ecx , msg1
	mov edx , len1
	int 0x80

	mov eax , SYS_READ
	mov ebx , STDIN
	mov ecx , num
	mov edx , 4
	int 0x80

	mov eax, SYS_WRITE
	mov ebx , STDOUT
	mov ecx , msg2
	mov edx , len2
	int 0x80

	;procedue of convertation

	mov eax , [num]
	sub eax , 0x30
	 
	mov [res] ,eax

	mov eax, SYS_WRITE
	mov ebx, STDOUT
	mov ecx, msg3
	mov edx, len3
	int 0x80

	mov eax, SYS_WRITE
	mov ebx, STDOUT
	mov ecx, res
	mov edx, 100
	int 0x80

	mov eax , SYS_EXIT
	int 0x80