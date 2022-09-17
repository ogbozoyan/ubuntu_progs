%include "begend.inc"
%include "files.inc"
%include "stdio.inc"
const
	velichina db " bytes", 0xA, 0x0
	len equ $ - velichina
	errmsg db "Error: cannot open a file", 0xA, 0x0
	lenmsg equ $ - errmsg
memory
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
	aam
	xchg ah, al
	add eax, 0x3030
	mov [fsize], eax
	print fsize, 4
	print velichina, len
	fclose fd
konec:	
end
