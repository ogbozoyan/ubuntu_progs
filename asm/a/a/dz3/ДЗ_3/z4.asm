; В программе считать из терминала строку (от 20 до 100 символов) и вывести на
; экран, наложив на нее 4-байтную гамму. Гамма должна представлять собой слу-
; чайные 4 байта, которые могут быть заданы как константные значения. Наложение
; байтов гаммы на байты строки происходит с помощью операции исключающего или
; (XOR).

section .data
    error db "Something wrong", 0Ah
    error_len equ $-error
    need db "Need more symbols!!!", 0Ah
    need_len equ $-need
    slashn db 0Ah
    gamma dd "lime"

section .bss
    tmp resb 4
    data resb 100
    count_symbol resb 1
section .text
    global _start
_start:
    ; address destination
    mov edi, data
    ; for print
    mov ebx, 0
    mov edx, 4
.read:
    mov eax, 3
    mov ecx, edi
    int 80h  
        cmp eax, 4
        jb .end_read
        cmp byte [edi+3], 0Ah
        je .end_read
    mov dword eax, [gamma]
    xor dword [edi], eax
    add edi, 4
    mov ecx, edi
    sub ecx, data
    cmp ecx, 100
    je .print
    jmp .read
    ; mov eax, 0
    ; xor dword eax, [gamma]
    ; mov [tmp], eax
.end_read:
    ; in eax count symbols after reading, eax-1 is index \n
    cmp eax, 1
    je .print
    ; get count of bytes which are read without \n, it is eax-1
    sub eax, 1
    mov dword ebx, [gamma]
    xor dword [edi], ebx
    ;"SSSSSSSSSSSSSSSSSSSSSSSSSSS[\n] "
    ; |->data                     |->edi => size of data is edi-data
    add edi, eax
    
.print:
    mov ecx, edi
    sub ecx, data
    cmp ecx, 20
    jb .need
    ; save in tmp size of data
    sub edi, data
    mov dword [tmp], edi
    mov eax, 4
    mov ebx, 1
    mov ecx, data
    mov dword edx, [tmp]
    int 80h
    cmp eax, 0
    jle .error
    jmp _end
.need:
    mov eax, 4
    mov ebx, 1
    mov ecx, need
    mov edx, need_len
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