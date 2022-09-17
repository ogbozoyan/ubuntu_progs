section .data

msg1 db "Enter num: ",0xA
len1 equ $-msg1

section .bss
num1 resb 2
res resb 1
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
	mov eax,[num1]
	mov ebx,3
	div ebx
	add eax,'0'
	mov [res],eax
	
        mov eax,4
        mov ebx,1
        mov ecx,res
        mov edx,1
        int 80h

end:
        mov eax,1
        mov ebx,0
                   
