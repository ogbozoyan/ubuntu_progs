; Написать программу, реализующую сложение двух упакованных BCD-чисел с ис-
; пользованием команды DAA. Программа должна корректно вычислять как сумму
; двузначных чисел, так и сумму со слагаемыми из одной цифры.
; Например, пользователь вводит 98 8. Результат работы программы: Sum = 106

section .data
    complite db "Sum = "
    complite_len equ $-complite
    error db "Something wrong", 0Ah
    error_len equ $-error
    slashn db 0Ah
    one db '1'

section .bss
    ; input_data resb 5
    ; input_len resb 1
    num1 resb 1
    num2 resb 1
    tmp resb 1

section .text
    global _start
_start:
    ; read first symbol
    mov eax, 3
    mov ebx, 0
    mov ecx, tmp
    mov edx, 1
    int 80h
    cmp byte[tmp], ' '
    je _start
    cmp byte[tmp], '0'
    jb .error
    cmp byte[tmp], '9'
    ja .error
.read1:
    mov al, [num1]
    shl al, 4
    mov bl, [tmp]
    sub bl, '0'
    add al, bl
    mov [num1], al
    ; read next symbol
    mov eax, 3
    mov ebx, 0
    mov ecx, tmp
    mov edx, 1
    int 80h
    cmp byte[tmp], ' '
    je .read_num2
    cmp byte[tmp], '0'
    jb .error
    cmp byte[tmp], '9'
    ja .error
    jmp .read1
.read_num2:
    ; read second number
    mov eax, 3
    mov ebx, 0
    mov ecx, tmp
    mov edx, 1
    int 80h
    cmp byte[tmp], ' '
    je .read_num2
    cmp byte[tmp], '0'
    jb .error
    cmp byte[tmp], '9'
    ja .error
.read2:
    mov al, [num2]
    shl al, 4
    mov bl, [tmp]
    sub bl, '0'
    add al, bl
    mov [num2], al
    ; read next symbol
    mov eax, 3
    mov ebx, 0
    mov ecx, tmp
    mov edx, 1
    int 80h
    cmp byte[tmp], ' '
    je .sum
    cmp byte[tmp], 0Ah
    je .sum
    cmp byte[tmp], '0'
    jb .error
    cmp byte[tmp], '9'
    ja .error
    jmp .read2
.sum:
    mov al, [num1]
    mov bl, [num2]
    add al, bl
    daa
    mov [tmp], al
    ; print complite
    mov eax, 4
    mov ebx, 1
    mov ecx, complite
    mov edx, complite_len
    int 80h
    ; ----------    
    jnc .print_sum
    mov eax, 4
    mov ebx, 1
    mov ecx, one
    mov edx, 1
    int 80h
.print_sum:
    mov al, [tmp]
    and al, 00001111b
    add al, '0'
    mov [num1], al
    mov al, [tmp]
    shr al, 4
    add al, '0'
    mov [num2], al
    ; print number
    mov eax, 4
    mov ebx, 1
    mov ecx, num2
    mov edx, 1
    int 80h
    mov eax, 4
    mov ebx, 1
    mov ecx, num1
    mov edx, 1
    int 80h
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