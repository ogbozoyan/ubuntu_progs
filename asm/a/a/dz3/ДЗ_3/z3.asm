; Написать программу, выводящую на экран размер файла, имя которого передается
; как параметр при запуске.

section .data
    result db "Size: "
    result_len equ $-result
    error db "Something wrong", 0Ah
    error_len equ $-error
    slashn db 0Ah
    str_fsize db ' ',' ',' ',' ',' ',' ',' '

section .bss
    fd resb 4
    fsize resb 4

section .text
    global _start
    
_start:
    ; get argc
    pop eax
    cmp eax, 2
    jne .error
    ; if argc == 2 then
    ; get argv[0]
    pop ebx
    ;get argv[1]
    pop ebx
    ; open argv[1] with mode r--
    mov eax, 5
    mov ecx, 0
    int 80h
        cmp eax, 0
        jle .error
    mov [fd], eax 
    ; get file size
    ; fseek(fd, 0, SEEK_END)
    mov eax, 19
    mov ebx, [fd]
    mov ecx, 0
    mov edx, 2
    int 80h
    ; save file size
    mov [fsize], eax
    ;close file:
    mov eax, 6
    mov ebx, [fd]
    int 80h
    ; print "Size: "
    mov eax, 4
    mov ebx, 1
    mov ecx, result
    mov edx, result_len
    int 80h
    ; eax = fsize
    mov eax, [fsize]
    ; constant for div
    mov ebx, 10
    ;index
    mov ecx, 0
    ; address destination
    mov edi, str_fsize

.content_to_str:
    xor edx, edx
    ; (edx:eax) div ebx => edx = (edx:eax)%ebx, eax = (edx:eax)/ebx  
    div ebx
    ; (edx:eax)%ebx, ebx == 10 => (edx:eax)%ebx in dl
    add dl, '0'
    mov [edi + ecx], dl
    cmp eax, 0
    je .invert_print
    inc ecx
    jmp .content_to_str

.invert_print:
    ; index last digit = ecx
    mov eax, ecx
    mov ecx, str_fsize
    add ecx, eax
    mov eax, 4
    mov ebx, 1
    mov edx, 1

.print:
    int 80h
    dec ecx
    cmp ecx, str_fsize
    jb .end_print
    mov eax, 4
    jmp .print

.end_print:
    ;print \n
    mov eax, 4
    mov ebx, 1
    mov ecx, slashn
    mov edx, 1
    int 80h
    jmp _end

.error:
    mov eax, 4
    mov ebx, 1
    mov ecx, error
    mov edx, error_len
    int 80h

_end:
    mov eax, 1
    mov ebx, 0 
    int 80h