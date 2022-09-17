%ifndef FILESMACROS
	%define FILESMACROS
	
	%macro fread 3; fread <указатель> <куда> <сколько>
		mov eax, 3
		mov ebx, [%1]
		mov ecx, %2
		mov edx, %3
		int 0x80
	%endmacro
	
	%macro fprint 3; fprint <указатель> <откуда> <сколько>
		mov eax, 4
		mov ebx, [%1]
		mov ecx, %2
		mov edx, %3
		int 0x80
	%endmacro
	
	%macro fseek 3; fseek <указатель> <отступ> <от чего>
		mov eax, 19
		mov ebx, [%1]
		mov ecx, %2
		mov edx, %3
		int 0x80
	%endmacro
	%define SEEK_SET 0
	%define SEEK_CUR 1
	%define SEEK_END 2
	
	%macro fcreate 2; fcreate <имя> <указатель>
		mov eax, 8
		mov ebx, %1
		mov ecx, 420
		int 0x80
		mov [%2], eax
	%endmacro
	
	%macro fopen 3; fopen <имя> <указатель> <режим>
		mov eax, 5
		mov ebx, %1
		mov ecx, %3
		mov edx, 0
		int 0x80
		mov [%2], eax
	%endmacro
	%define R 0
	%define W 1
	%define RW 2
	
	%macro fclose 1; fclose <указатель>
		mov eax, 6
		mov ebx, [%1]
		int 0x80
	%endmacro
	
	%macro fstcreate 1; fstcreate <указатель>
		mov eax, 8
		pop ebx
		mov ecx, 420
		int 0x80
		mov [%1], eax
	%endmacro
	
	%macro fstopen 2; fstopen <указатель> <режим>
		mov eax, 5
		pop ebx
		mov ecx, %2
		mov edx, 0
		int 0x80
		mov [%1], eax
	%endmacro
%endif
		
