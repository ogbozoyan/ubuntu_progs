BITS 16
mov ax, 07c0h
mov ds, ax
mov ax, 0b800h
mov es, ax
or bx, bx
mov ax, 3
int 10h

mov ax, 0f030h
mov [es:bx], ax
jmp $
times 510-($-$$) db 0
dw 0xaa55
times 1024*1024-($-$$) db 0