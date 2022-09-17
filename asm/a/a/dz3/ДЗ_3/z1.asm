; Написать программу, осуществляющую уничтожение файла путем перезаписи всех
; его байт элементами байтовой последовательности, полученной по формуле
; xi+1 = (17 ∗ xi + 11)mod256
; Пусть первый элемент последовательности x0 = 195.

section .data
    complite db "File killed :^)", 0Ah
    complite_len equ $-complite
    error db "Something wrong", 0Ah
    error_len equ $-error

section .bss
    tmp resb 1
    fd resb 4
    x_l resb 1
    size_file resb 4
    
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
    ; open argv[1] with mode r-w
    mov eax, 5
    mov ecx, 2
    int 80h
        cmp eax, 0
        jle .error
    mov [fd], eax 
    mov byte [x_l], 195
    ; get file size
    ; fseek(fd, 0, SEEK_END)
    mov eax, 19
    mov ebx, [fd]
    mov ecx, 0
    mov edx, 2
    int 80h
    ; save file size
    mov [size_file], eax
    cmp eax, 0
    je _end
    ; fseek(fd, 0, SEEK_SET)
    mov eax, 19
    mov ebx, [fd]
    mov ecx, 0
    mov edx, 0
    int 80h
    mov ecx, [size_file]
    
.change_and_write:
    ; change byte
    xor dx, dx
    xor eax, eax
    mov al, [x_l]
    mov bl, 17
    mul bl
    add ax, 11
    mov bx, 256
    div bx
    mov [x_l], dl
    ; write changed byte
    push ecx
    mov eax, 4
    mov ebx, [fd]
    mov ecx, x_l
    mov edx, 1 
    int 80h
        cmp eax, 0
        jle .error
    pop ecx
    loop .change_and_write

.close_file:
    mov eax, 6
    mov ebx, [fd]
    int 80h
    mov eax, 4
    mov ebx, 1
    mov ecx, complite
    mov edx, complite_len
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