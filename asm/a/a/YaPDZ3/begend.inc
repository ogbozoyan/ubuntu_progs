%ifndef BEGEND
	%define BEGEND
	
	%define const section .data
	%define memory section .bss
	
	%macro begin 0
		section .text
		global _start
		_start:
	%endmacro
	
	%macro end 0
		mov eax, 1
		mov ebx, 0
		int 0x80
	%endmacro
%endif
