%include "begend.inc"
%include "files.inc"
%include "stdio.inc"
const
	velichina db " bytes", 0xA, 0x0
	len equ $ - velichina
	errmsg db "Error: cannot open a file", 0xA, 0x0
	lenmsg equ $ - errmsg
	bigmsg db ">9999 bytes", 0xA, 0x0
	lenbig equ $ - bigmsg
memory
	buf resb 1
	fsize resb 4
	fd resb 4
begin
	pop eax
	pop eax
	fstopen fd, R
	cmp [fd], dword -2
	jne alright
	print errmsg, lenmsg
	jmp konec
	alright:
	fseek fd, 0, SEEK_END
	cmp eax, 9999
	jg big
	mov bl, 100
	div bl
	mov [buf], ah
	xor ah, ah
	mov bl, 10
	div bl
	mov [fsize], al
	mov [fsize+1], ah
	xor ax, ax
	mov al, [buf]
	div bl
	mov [fsize+2], al
	mov [fsize+3], ah
	add [fsize], dword 0x30303030
	print fsize, 4
	print velichina, len
	fclose fd
	jmp konec
	big:
	print bigmsg, lenbig
	fclose fd
konec:	
end
