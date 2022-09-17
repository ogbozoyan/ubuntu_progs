%include "begend.inc"
%include "files.inc"
%include "stdio.inc"
memory
	stroka resb 101; 101 символ нужен, чтобы \n всегда попадал
	ans resb 100
	len resb 1
const
	gamma db "abcd"
	perenos db 0xA
begin
	read stroka, 101
	sub al, 1
	mov [len], al
	mov bl, 4
	div bl
	add al, 1
	xor ecx, ecx
	mov cl, al
	lea esi, [stroka]
	lea edi, [ans]
	cycle:
		lodsd
		xor eax, [gamma]
		stosd
	loop cycle
	xor edx, edx
	print ans, [len] 
end
