%include "begend.inc"
%include "files.inc"
%include "stdio.inc"
%macro pack_to_unpack 2
	print msg%2, len%2
	read x, 2
	sub [x], word 0x3030
	mov %1x, [x]
	cmp %1h, 9
	jg clear%2
	cmp %1h, 0
	jge reverse%2
	clear%2:
	xor %1h, %1h
	jmp alright%2
	reverse%2:
	push e%1x
	read x, 1
	pop e%1x
	rol %1h, 4
	rol %1x, 4
	alright%2:
%endmacro
memory
	x resb 2
	ans resb 2
const
	msg1 db "Enter first number: ", 0x0
	len1 equ $ - msg1
	msg2 db "Enter second number: ", 0x0
	len2 equ $ - msg2
	msg3 db "Sum = ", 0x0
	len3 equ $ - msg3
	perenos db 0xA
	symone db 0x31
begin
	pack_to_unpack a, 1
	push eax
	pack_to_unpack b, 2
	pop eax
	add al, bl
	daa
	jnc enternumber
	push eax
	print symone, 1
	pop eax
	enternumber:
	mov [ans+1], al
	xor ax, ax
	rol word[ans], 4
	ror byte[ans+1], 4
	add word[ans], 0x3030
	print ans, 2
	print perenos, 1
end
