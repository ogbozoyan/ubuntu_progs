%include "begend.inc"
%include "files.inc"
%include "stdio.inc"
const
	errmsg db "Error: cannot open a file", 0xA, 0x0
	lenmsg equ $ - errmsg
memory
	x resb 1
	fd resb 4
begin
	mov [x], byte 195
	pop ebx
	pop ebx
	fstopen fd, RW
	cmp [fd], dword -2
	jne alright
	print errmsg, lenmsg
	jmp konec
	alright:
	fseek fd, 0, SEEK_END
	push eax
	fseek fd, 0, SEEK_SET
	pop ecx
	cycle:
		push ecx
		fprint fd, x, 1
		mov al, [x]
		mov bl, 17
		mul bl
		add al, 11
		mov bx, 256
		div bx
		mov [x], dl
		pop ecx
	loop cycle
	fclose fd
konec:
end
		 
