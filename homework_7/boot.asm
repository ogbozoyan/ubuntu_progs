BITS 16
    mov ax, 07c0h   
    mov ds, ax
    mov ax, 0b800h 
    mov es, ax
    or bx, bx
    mov ax, 3       
    int 10h
    mov ah, 02h    
    xor bh,bh      
    mov dh, 26      
    mov dl, 1       
    int 10h         

    mov cx, 480
set_center:         
    mov ah, 0x40    
    xor al,al
    mov [es:bx], ax
    add bx, 2
    loop set_center
    mov cx, 420
set_center1:
    mov ah, 0x10    
    xor al,al
    mov [es:bx], ax
    add bx, 2
    loop set_center1

    mov si, pass_ent  
    mov cx, passentlen         

log_in:  ;login
    mov ah, 1Eh
    mov al, [si]
    mov [es:bx], ax
 
    add bx, 2
    inc si
loop log_in
    mov cx,114
set_center2:
    mov ah, 0x10   
    xor al,al
    mov [es:bx], ax
    add bx, 2
    loop set_center2
    mov cx,480
set_center4:
    mov ah, 0x66  
    xor al,al
    mov [es:bx], ax
    add bx, 2
    loop set_center4

    mov si, pswd 
get_char:
    mov ah, 10h     
    int 16h         
    
    inc cx
    cmp ah, 1ch     
    jz exit         
    mov [si], al   
    
    mov bx,0
    mov bx,1850
    mov ah, 1Eh    
    mov [es:bx], ax ; 
    add bx, 2       
jmp get_char
exit:

decrypt_name:
    mov si, name
    mov di, pswd
    mov cx, name_len
char_decrypt:
    mov al, [si] 
    xor al, [di]
    mov [si], al
    inc si
    loop char_decrypt
    mov bx,0
       
     mov cx, 980
set_center3:
    mov ah, 0x00
    xor al,al
    mov [es:bx], ax
    add bx, 2
loop set_center3

    mov si, name
    mov cx, name_len
print_name:  
    mov ah, 0x0b
    mov al, [si]
    mov [es:bx], ax

    add bx, 2
    inc si
loop print_name
int 10h
    mov cx,520
set_center5:
    mov ah, 0x00
    xor al,al
    mov [es:bx], ax
    add bx, 2
loop set_center5

    name db 'Bozoyan Oganes KKSO-03-20'
    name_len equ $-name
    
    pass_ent db 'Enter your password: '
    passentlen equ $-pass_ent

    pswd db 0 
    len_pswd equ 1
    
    jmp $
    times 510-($-$$) db 0
    dw 0xaa55
    times 1024*1024-($-$$) db 0
    
