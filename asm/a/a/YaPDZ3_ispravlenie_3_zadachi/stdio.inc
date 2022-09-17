%ifndef STDIO
	%define STDIO
	
	%macro read 2; read <куда> <сколько>
		mov eax, 3
		mov ebx, 0
		mov ecx, %1
		mov edx, %2
		int 0x80
	%endmacro
	
	%macro print 2; print <откдуа> <сколько>
		mov eax, 4
		mov ebx, 1
		mov ecx, %1
		mov edx, %2
		int 0x80
	%endmacro
	
%endif
