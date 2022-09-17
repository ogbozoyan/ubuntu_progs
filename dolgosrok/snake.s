	.file	"snake.c"
	.intel_syntax noprefix
	.text
	.comm	fi,16,4
	.comm	si,16,4
	.comm	sum1,4,4
	.comm	sum2,4,4
	.globl	work_flag
	.data
	.align 4
	.type	work_flag, @object
	.size	work_flag, 4
work_flag:
	.long	1
	.globl	i
	.bss
	.align 4
	.type	i, @object
	.size	i, 4
i:
	.zero	4
	.comm	fb_size,4,4
	.comm	map_size,4,4
	.comm	page_size,4,4
	.comm	fb,4,4
	.comm	info,160,32
	.comm	ptr,4,4
	.comm	thread,4,4
	.comm	thread2,4,4
	.comm	thread_key1,4,4
	.comm	thread_key2,4,4
	.comm	thread_send,4,4
	.comm	thread_recv,4,4
	.comm	thread_press,4,4
	.globl	ch1
	.align 4
	.type	ch1, @object
	.size	ch1, 4
ch1:
	.zero	4
	.globl	ch2
	.align 4
	.type	ch2, @object
	.size	ch2, 4
ch2:
	.zero	4
	.globl	way
	.align 4
	.type	way, @object
	.size	way, 4
way:
	.zero	4
	.globl	way2
	.align 4
	.type	way2, @object
	.size	way2, 4
way2:
	.zero	4
	.globl	sprava
	.align 4
	.type	sprava, @object
	.size	sprava, 4
sprava:
	.zero	4
	.globl	sleva
	.align 4
	.type	sleva, @object
	.size	sleva, 4
sleva:
	.zero	4
	.comm	me,16,4
	.comm	other,16,4
	.comm	my_fd,4,4
	.comm	other_fd,4,4
	.globl	size
	.data
	.align 4
	.type	size, @object
	.size	size, 4
size:
	.long	16
	.comm	f,4,4
	.section	.rodata
	.align 4
.LC0:
	.string	"%cLUE LOST GAME \nCongratulations to RED you earned %d bucks"
	.align 4
.LC1:
	.string	"%cED LOST GAME \nCongratulations to BLUE you earned %d bucks"
	.text
	.globl	win
	.type	win, @function
win:
.LFB6:
	.cfi_startproc
	endbr32
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	ebx
	sub	esp, 4
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	add	ebx, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	mov	eax, DWORD PTR map_size@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	edx
	push	eax
	call	munmap@PLT
	add	esp, 16
	mov	eax, DWORD PTR fb@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 12
	push	eax
	call	close@PLT
	add	esp, 16
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR 20[eax]
	cmp	eax, 66
	jne	.L2
	mov	edx, DWORD PTR i@GOTOFF[ebx]
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR 20[eax]
	sub	esp, 12
	push	edx
	push	eax
	lea	eax, .LC0@GOTOFF[ebx]
	push	eax
	push	0
	push	1
	call	mvprintw@PLT
	add	esp, 32
	jmp	.L3
.L2:
	mov	edx, DWORD PTR i@GOTOFF[ebx]
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR 20[eax]
	sub	esp, 12
	push	edx
	push	eax
	lea	eax, .LC1@GOTOFF[ebx]
	push	eax
	push	0
	push	1
	call	mvprintw@PLT
	add	esp, 32
.L3:
	mov	eax, DWORD PTR stdscr@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 12
	push	eax
	call	wrefresh@PLT
	add	esp, 16
	call	endwin@PLT
	sub	esp, 12
	push	0
	call	exit@PLT
	.cfi_endproc
.LFE6:
	.size	win, .-win
	.globl	handler
	.type	handler, @function
handler:
.LFB7:
	.cfi_startproc
	endbr32
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	ebx
	sub	esp, 4
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	add	ebx, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	mov	DWORD PTR work_flag@GOTOFF[ebx], 0
	mov	eax, DWORD PTR map_size@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	edx
	push	eax
	call	munmap@PLT
	add	esp, 16
	mov	eax, DWORD PTR fb@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 12
	push	eax
	call	close@PLT
	add	esp, 16
	call	endwin@PLT
	sub	esp, 12
	push	0
	call	exit@PLT
	.cfi_endproc
.LFE7:
	.size	handler, .-handler
	.globl	press_first_bike
	.type	press_first_bike, @function
press_first_bike:
.LFB8:
	.cfi_startproc
	endbr32
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	ebx
	sub	esp, 4
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	add	ebx, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
.L6:
	mov	eax, DWORD PTR stdscr@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 12
	push	eax
	call	wgetch@PLT
	add	esp, 16
	mov	DWORD PTR ch1@GOTOFF[ebx], eax
	mov	eax, DWORD PTR size@GOTOFF[ebx]
	mov	edx, eax
	mov	eax, DWORD PTR my_fd@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	edx
	mov	edx, DWORD PTR other@GOT[ebx]
	push	edx
	push	2048
	push	1
	lea	edx, ch1@GOTOFF[ebx]
	push	edx
	push	eax
	call	sendto@PLT
	add	esp, 32
	jmp	.L6
	.cfi_endproc
.LFE8:
	.size	press_first_bike, .-press_first_bike
	.globl	press_second_bike
	.type	press_second_bike, @function
press_second_bike:
.LFB9:
	.cfi_startproc
	endbr32
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	ebx
	sub	esp, 4
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	add	ebx, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
.L8:
	mov	eax, DWORD PTR my_fd@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	lea	edx, size@GOTOFF[ebx]
	push	edx
	mov	edx, DWORD PTR me@GOT[ebx]
	push	edx
	push	256
	push	1
	lea	edx, ch2@GOTOFF[ebx]
	push	edx
	push	eax
	call	recvfrom@PLT
	add	esp, 32
	jmp	.L8
	.cfi_endproc
.LFE9:
	.size	press_second_bike, .-press_second_bike
	.globl	keypress_first
	.type	keypress_first, @function
keypress_first:
.LFB10:
	.cfi_startproc
	endbr32
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 16
	call	__x86.get_pc_thunk.ax
	add	eax, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	mov	edx, DWORD PTR 8[ebp]
	mov	DWORD PTR -4[ebp], edx
	jmp	.L10
.L16:
	mov	edx, DWORD PTR ch1@GOTOFF[eax]
	cmp	edx, 119
	je	.L11
	cmp	edx, 119
	jg	.L17
	cmp	edx, 115
	je	.L13
	cmp	edx, 115
	jg	.L17
	cmp	edx, 97
	je	.L14
	cmp	edx, 100
	je	.L15
	jmp	.L12
.L11:
	mov	DWORD PTR way@GOTOFF[eax], 1
	mov	edx, DWORD PTR way@GOTOFF[eax]
	mov	ecx, edx
	mov	edx, DWORD PTR -4[ebp]
	mov	DWORD PTR 16[edx], ecx
	jmp	.L10
.L13:
	mov	DWORD PTR way@GOTOFF[eax], 2
	mov	edx, DWORD PTR way@GOTOFF[eax]
	mov	ecx, edx
	mov	edx, DWORD PTR -4[ebp]
	mov	DWORD PTR 16[edx], ecx
	jmp	.L10
.L14:
	mov	DWORD PTR way@GOTOFF[eax], 3
	mov	edx, DWORD PTR way@GOTOFF[eax]
	mov	ecx, edx
	mov	edx, DWORD PTR -4[ebp]
	mov	DWORD PTR 16[edx], ecx
	jmp	.L10
.L15:
	mov	DWORD PTR way@GOTOFF[eax], 4
	mov	edx, DWORD PTR way@GOTOFF[eax]
	mov	ecx, edx
	mov	edx, DWORD PTR -4[ebp]
	mov	DWORD PTR 16[edx], ecx
	jmp	.L10
.L12:
.L17:
	nop
.L10:
	mov	edx, DWORD PTR work_flag@GOTOFF[eax]
	test	edx, edx
	jne	.L16
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE10:
	.size	keypress_first, .-keypress_first
	.globl	keypress_second
	.type	keypress_second, @function
keypress_second:
.LFB11:
	.cfi_startproc
	endbr32
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 16
	call	__x86.get_pc_thunk.ax
	add	eax, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	mov	edx, DWORD PTR 8[ebp]
	mov	DWORD PTR -4[ebp], edx
	jmp	.L19
.L25:
	mov	edx, DWORD PTR ch2@GOTOFF[eax]
	cmp	edx, 119
	je	.L20
	cmp	edx, 119
	jg	.L26
	cmp	edx, 115
	je	.L22
	cmp	edx, 115
	jg	.L26
	cmp	edx, 97
	je	.L23
	cmp	edx, 100
	je	.L24
	jmp	.L21
.L20:
	mov	DWORD PTR way2@GOTOFF[eax], 1
	mov	edx, DWORD PTR way2@GOTOFF[eax]
	mov	ecx, edx
	mov	edx, DWORD PTR -4[ebp]
	mov	DWORD PTR 16[edx], ecx
	jmp	.L19
.L22:
	mov	DWORD PTR way2@GOTOFF[eax], 2
	mov	edx, DWORD PTR way2@GOTOFF[eax]
	mov	ecx, edx
	mov	edx, DWORD PTR -4[ebp]
	mov	DWORD PTR 16[edx], ecx
	jmp	.L19
.L23:
	mov	DWORD PTR way2@GOTOFF[eax], 3
	mov	edx, DWORD PTR way2@GOTOFF[eax]
	mov	ecx, edx
	mov	edx, DWORD PTR -4[ebp]
	mov	DWORD PTR 16[edx], ecx
	jmp	.L19
.L24:
	mov	DWORD PTR way2@GOTOFF[eax], 4
	mov	edx, DWORD PTR way2@GOTOFF[eax]
	mov	ecx, edx
	mov	edx, DWORD PTR -4[ebp]
	mov	DWORD PTR 16[edx], ecx
	jmp	.L19
.L21:
.L26:
	nop
.L19:
	mov	edx, DWORD PTR work_flag@GOTOFF[eax]
	test	edx, edx
	jne	.L25
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE11:
	.size	keypress_second, .-keypress_second
	.section	.rodata
.LC2:
	.string	"/dev/fb0"
.LC3:
	.string	"open"
.LC4:
	.string	"ioctl"
.LC5:
	.string	"Max value of X %d\tY %d\n"
.LC6:
	.string	"mmap"
	.text
	.globl	initialization
	.type	initialization, @function
initialization:
.LFB12:
	.cfi_startproc
	endbr32
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	ebx
	sub	esp, 20
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	add	ebx, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	sub	esp, 12
	push	30
	call	sysconf@PLT
	add	esp, 16
	mov	edx, eax
	mov	eax, DWORD PTR page_size@GOT[ebx]
	mov	DWORD PTR [eax], edx
	sub	esp, 8
	push	2
	lea	eax, .LC2@GOTOFF[ebx]
	push	eax
	call	open@PLT
	add	esp, 16
	mov	edx, DWORD PTR fb@GOT[ebx]
	mov	DWORD PTR [edx], eax
	mov	eax, DWORD PTR fb@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	test	eax, eax
	jns	.L28
	sub	esp, 12
	lea	eax, .LC3@GOTOFF[ebx]
	push	eax
	call	perror@PLT
	add	esp, 16
	mov	eax, 144
	jmp	.L27
.L28:
	mov	eax, DWORD PTR fb@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 4
	mov	edx, DWORD PTR info@GOT[ebx]
	push	edx
	push	17920
	push	eax
	call	ioctl@PLT
	add	esp, 16
	cmp	eax, -1
	jne	.L30
	sub	esp, 12
	lea	eax, .LC4@GOTOFF[ebx]
	push	eax
	call	perror@PLT
	add	esp, 16
	mov	eax, DWORD PTR fb@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 12
	push	eax
	call	close@PLT
	add	esp, 16
	mov	eax, 150
	jmp	.L27
.L30:
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	edx, DWORD PTR 8[eax]
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 12[eax]
	imul	eax, edx
	lea	edx, 0[0+eax*4]
	mov	eax, DWORD PTR fb_size@GOT[ebx]
	mov	DWORD PTR [eax], edx
	mov	eax, DWORD PTR page_size@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR fb_size@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	add	eax, edx
	lea	edx, -1[eax]
	mov	eax, DWORD PTR page_size@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	neg	eax
	and	edx, eax
	mov	eax, DWORD PTR map_size@GOT[ebx]
	mov	DWORD PTR [eax], edx
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR [eax]
	mov	edx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	cmp	edx, eax
	ja	.L31
	mov	eax, DWORD PTR 8[ebp]
	add	eax, 4
	mov	eax, DWORD PTR [eax]
	mov	edx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 12[eax]
	cmp	edx, eax
	jbe	.L32
.L31:
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	edx, DWORD PTR 12[eax]
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	sub	esp, 4
	push	edx
	push	eax
	lea	eax, .LC5@GOTOFF[ebx]
	push	eax
	call	printf@PLT
	add	esp, 16
	mov	eax, DWORD PTR map_size@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	edx
	push	eax
	call	munmap@PLT
	add	esp, 16
	mov	eax, DWORD PTR fb@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 12
	push	eax
	call	close@PLT
	add	esp, 16
	call	endwin@PLT
	sub	esp, 12
	push	0
	call	exit@PLT
.L32:
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR [eax]
	mov	edx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	DWORD PTR [eax], edx
	mov	eax, DWORD PTR 8[ebp]
	add	eax, 4
	mov	eax, DWORD PTR [eax]
	mov	edx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	DWORD PTR 4[eax], edx
	call	initscr@PLT
	test	eax, eax
	jne	.L33
	mov	eax, 167
	jmp	.L27
.L33:
	call	noecho@PLT
	sub	esp, 12
	push	2
	call	curs_set@PLT
	add	esp, 16
	mov	eax, DWORD PTR stdscr@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	1
	push	eax
	call	keypad@PLT
	add	esp, 16
	mov	eax, DWORD PTR fb@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR map_size@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	0
	push	edx
	push	1
	push	3
	push	eax
	push	0
	call	mmap@PLT
	add	esp, 32
	mov	edx, DWORD PTR ptr@GOT[ebx]
	mov	DWORD PTR [edx], eax
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	cmp	eax, -1
	jne	.L34
	sub	esp, 12
	lea	eax, .LC6@GOTOFF[ebx]
	push	eax
	call	perror@PLT
	add	esp, 16
	mov	eax, DWORD PTR fb@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 12
	push	eax
	call	close@PLT
	add	esp, 16
	mov	eax, 176
	jmp	.L27
.L34:
	mov	DWORD PTR -16[ebp], 0
	jmp	.L35
.L38:
	mov	DWORD PTR -12[ebp], 0
	jmp	.L36
.L37:
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	ecx, DWORD PTR 8[eax]
	mov	eax, DWORD PTR -12[ebp]
	imul	ecx, eax
	mov	eax, DWORD PTR -16[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	DWORD PTR [eax], 0
	add	DWORD PTR -12[ebp], 1
.L36:
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	edx, DWORD PTR 4[eax]
	mov	eax, DWORD PTR -12[ebp]
	cmp	edx, eax
	jnb	.L37
	add	DWORD PTR -16[ebp], 1
.L35:
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -16[ebp]
	cmp	edx, eax
	jnb	.L38
.L27:
	mov	ebx, DWORD PTR -4[ebp]
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE12:
	.size	initialization, .-initialization
	.globl	border_print
	.type	border_print, @function
border_print:
.LFB13:
	.cfi_startproc
	endbr32
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	ebx
	sub	esp, 16
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.ax
	add	eax, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	mov	DWORD PTR -20[ebp], 0
	jmp	.L40
.L41:
	mov	edx, DWORD PTR ptr@GOT[eax]
	mov	ecx, DWORD PTR [edx]
	mov	edx, DWORD PTR info@GOT[eax]
	mov	ebx, DWORD PTR 8[edx]
	mov	edx, DWORD PTR -20[ebp]
	imul	edx, ebx
	sal	edx, 2
	add	edx, ecx
	mov	DWORD PTR [edx], 9055202
	add	DWORD PTR -20[ebp], 1
.L40:
	mov	edx, DWORD PTR info@GOT[eax]
	mov	ecx, DWORD PTR 4[edx]
	mov	edx, DWORD PTR -20[ebp]
	cmp	ecx, edx
	ja	.L41
	mov	DWORD PTR -16[ebp], 0
	jmp	.L42
.L43:
	mov	edx, DWORD PTR ptr@GOT[eax]
	mov	edx, DWORD PTR [edx]
	mov	ecx, DWORD PTR -16[ebp]
	sal	ecx, 2
	add	edx, ecx
	mov	DWORD PTR [edx], 9055202
	add	DWORD PTR -16[ebp], 1
.L42:
	mov	edx, DWORD PTR info@GOT[eax]
	mov	ecx, DWORD PTR [edx]
	mov	edx, DWORD PTR -16[ebp]
	cmp	ecx, edx
	ja	.L43
	mov	DWORD PTR -12[ebp], 0
	jmp	.L44
.L45:
	mov	edx, DWORD PTR ptr@GOT[eax]
	mov	ecx, DWORD PTR [edx]
	mov	edx, DWORD PTR info@GOT[eax]
	mov	edx, DWORD PTR 4[edx]
	lea	ebx, -1[edx]
	mov	edx, DWORD PTR info@GOT[eax]
	mov	edx, DWORD PTR 8[edx]
	imul	ebx, edx
	mov	edx, DWORD PTR -12[ebp]
	add	edx, ebx
	sal	edx, 2
	add	edx, ecx
	mov	DWORD PTR [edx], 9055202
	add	DWORD PTR -12[ebp], 1
.L44:
	mov	edx, DWORD PTR info@GOT[eax]
	mov	ecx, DWORD PTR [edx]
	mov	edx, DWORD PTR -12[ebp]
	cmp	ecx, edx
	ja	.L45
	mov	DWORD PTR -8[ebp], 0
	jmp	.L46
.L47:
	mov	edx, DWORD PTR ptr@GOT[eax]
	mov	ecx, DWORD PTR [edx]
	mov	edx, DWORD PTR info@GOT[eax]
	mov	ebx, DWORD PTR 8[edx]
	mov	edx, DWORD PTR -8[ebp]
	imul	ebx, edx
	mov	edx, DWORD PTR info@GOT[eax]
	mov	edx, DWORD PTR [edx]
	add	edx, ebx
	sub	edx, 1
	sal	edx, 2
	add	edx, ecx
	mov	DWORD PTR [edx], 9055202
	add	DWORD PTR -8[ebp], 1
.L46:
	mov	edx, DWORD PTR info@GOT[eax]
	mov	ecx, DWORD PTR 4[edx]
	mov	edx, DWORD PTR -8[ebp]
	cmp	ecx, edx
	ja	.L47
	nop
	nop
	add	esp, 16
	pop	ebx
	.cfi_restore 3
	pop	ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE13:
	.size	border_print, .-border_print
	.globl	print_black_r
	.type	print_black_r, @function
print_black_r:
.LFB14:
	.cfi_startproc
	endbr32
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	ebx
	sub	esp, 84
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.ax
	add	eax, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	mov	ebx, DWORD PTR gs:20
	mov	DWORD PTR -12[ebp], ebx
	xor	ebx, ebx
	mov	edx, DWORD PTR 8[ebp]
	add	edx, 1
	mov	DWORD PTR -76[ebp], edx
	mov	edx, DWORD PTR 12[ebp]
	mov	DWORD PTR -72[ebp], edx
	mov	DWORD PTR -88[ebp], 0
	jmp	.L49
.L50:
	mov	ecx, DWORD PTR -76[ebp]
	mov	edx, DWORD PTR -88[ebp]
	add	ecx, edx
	mov	edx, DWORD PTR -88[ebp]
	mov	DWORD PTR -48[ebp+edx*4], ecx
	add	DWORD PTR -88[ebp], 1
.L49:
	cmp	DWORD PTR -88[ebp], 8
	jle	.L50
	mov	edx, DWORD PTR -72[ebp]
	sub	edx, 2
	mov	DWORD PTR -68[ebp], edx
	mov	edx, DWORD PTR -72[ebp]
	sub	edx, 1
	mov	DWORD PTR -64[ebp], edx
	mov	edx, DWORD PTR -72[ebp]
	mov	DWORD PTR -60[ebp], edx
	mov	edx, DWORD PTR -72[ebp]
	add	edx, 1
	mov	DWORD PTR -56[ebp], edx
	mov	edx, DWORD PTR -72[ebp]
	add	edx, 2
	mov	DWORD PTR -52[ebp], edx
	mov	DWORD PTR -84[ebp], 0
	jmp	.L51
.L54:
	mov	DWORD PTR -80[ebp], 0
	jmp	.L52
.L53:
	mov	edx, DWORD PTR ptr@GOT[eax]
	mov	ecx, DWORD PTR [edx]
	mov	edx, DWORD PTR -80[ebp]
	mov	edx, DWORD PTR -68[ebp+edx*4]
	mov	ebx, edx
	mov	edx, DWORD PTR info@GOT[eax]
	mov	edx, DWORD PTR 8[edx]
	imul	ebx, edx
	mov	edx, DWORD PTR -84[ebp]
	mov	edx, DWORD PTR -48[ebp+edx*4]
	add	edx, ebx
	sal	edx, 2
	add	edx, ecx
	mov	DWORD PTR [edx], 0
	add	DWORD PTR -80[ebp], 1
.L52:
	cmp	DWORD PTR -80[ebp], 4
	jle	.L53
	add	DWORD PTR -84[ebp], 1
.L51:
	cmp	DWORD PTR -84[ebp], 8
	jle	.L54
	nop
	mov	eax, DWORD PTR -12[ebp]
	xor	eax, DWORD PTR gs:20
	je	.L55
	call	__stack_chk_fail_local
.L55:
	add	esp, 84
	pop	ebx
	.cfi_restore 3
	pop	ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE14:
	.size	print_black_r, .-print_black_r
	.globl	print_black_l
	.type	print_black_l, @function
print_black_l:
.LFB15:
	.cfi_startproc
	endbr32
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	ebx
	sub	esp, 84
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.ax
	add	eax, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	mov	ebx, DWORD PTR gs:20
	mov	DWORD PTR -12[ebp], ebx
	xor	ebx, ebx
	mov	edx, DWORD PTR 8[ebp]
	sub	edx, 1
	mov	DWORD PTR -76[ebp], edx
	mov	edx, DWORD PTR 12[ebp]
	mov	DWORD PTR -72[ebp], edx
	mov	DWORD PTR -88[ebp], 0
	jmp	.L57
.L58:
	mov	edx, DWORD PTR -76[ebp]
	mov	ecx, edx
	sub	ecx, DWORD PTR -88[ebp]
	mov	edx, DWORD PTR -88[ebp]
	mov	DWORD PTR -48[ebp+edx*4], ecx
	add	DWORD PTR -88[ebp], 1
.L57:
	cmp	DWORD PTR -88[ebp], 8
	jle	.L58
	mov	edx, DWORD PTR -72[ebp]
	sub	edx, 2
	mov	DWORD PTR -68[ebp], edx
	mov	edx, DWORD PTR -72[ebp]
	sub	edx, 1
	mov	DWORD PTR -64[ebp], edx
	mov	edx, DWORD PTR -72[ebp]
	mov	DWORD PTR -60[ebp], edx
	mov	edx, DWORD PTR -72[ebp]
	add	edx, 1
	mov	DWORD PTR -56[ebp], edx
	mov	edx, DWORD PTR -72[ebp]
	add	edx, 2
	mov	DWORD PTR -52[ebp], edx
	mov	DWORD PTR -84[ebp], 0
	jmp	.L59
.L62:
	mov	DWORD PTR -80[ebp], 0
	jmp	.L60
.L61:
	mov	edx, DWORD PTR ptr@GOT[eax]
	mov	ecx, DWORD PTR [edx]
	mov	edx, DWORD PTR -80[ebp]
	mov	edx, DWORD PTR -68[ebp+edx*4]
	mov	ebx, edx
	mov	edx, DWORD PTR info@GOT[eax]
	mov	edx, DWORD PTR 8[edx]
	imul	ebx, edx
	mov	edx, DWORD PTR -84[ebp]
	mov	edx, DWORD PTR -48[ebp+edx*4]
	add	edx, ebx
	sal	edx, 2
	add	edx, ecx
	mov	DWORD PTR [edx], 0
	add	DWORD PTR -80[ebp], 1
.L60:
	cmp	DWORD PTR -80[ebp], 4
	jle	.L61
	add	DWORD PTR -84[ebp], 1
.L59:
	cmp	DWORD PTR -84[ebp], 8
	jle	.L62
	nop
	mov	eax, DWORD PTR -12[ebp]
	xor	eax, DWORD PTR gs:20
	je	.L63
	call	__stack_chk_fail_local
.L63:
	add	esp, 84
	pop	ebx
	.cfi_restore 3
	pop	ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE15:
	.size	print_black_l, .-print_black_l
	.globl	print_black_u
	.type	print_black_u, @function
print_black_u:
.LFB16:
	.cfi_startproc
	endbr32
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	ebx
	sub	esp, 84
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.ax
	add	eax, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	mov	ebx, DWORD PTR gs:20
	mov	DWORD PTR -12[ebp], ebx
	xor	ebx, ebx
	mov	edx, DWORD PTR 8[ebp]
	mov	DWORD PTR -76[ebp], edx
	mov	edx, DWORD PTR 12[ebp]
	sub	edx, 1
	mov	DWORD PTR -72[ebp], edx
	mov	DWORD PTR -88[ebp], 0
	jmp	.L65
.L66:
	mov	edx, DWORD PTR -72[ebp]
	mov	ecx, edx
	sub	ecx, DWORD PTR -88[ebp]
	mov	edx, DWORD PTR -88[ebp]
	mov	DWORD PTR -48[ebp+edx*4], ecx
	add	DWORD PTR -88[ebp], 1
.L65:
	cmp	DWORD PTR -88[ebp], 8
	jle	.L66
	mov	edx, DWORD PTR -76[ebp]
	sub	edx, 2
	mov	DWORD PTR -68[ebp], edx
	mov	edx, DWORD PTR -76[ebp]
	sub	edx, 1
	mov	DWORD PTR -64[ebp], edx
	mov	edx, DWORD PTR -76[ebp]
	mov	DWORD PTR -60[ebp], edx
	mov	edx, DWORD PTR -76[ebp]
	add	edx, 1
	mov	DWORD PTR -56[ebp], edx
	mov	edx, DWORD PTR -76[ebp]
	add	edx, 2
	mov	DWORD PTR -52[ebp], edx
	mov	DWORD PTR -84[ebp], 0
	jmp	.L67
.L70:
	mov	DWORD PTR -80[ebp], 0
	jmp	.L68
.L69:
	mov	edx, DWORD PTR ptr@GOT[eax]
	mov	ecx, DWORD PTR [edx]
	mov	edx, DWORD PTR -84[ebp]
	mov	edx, DWORD PTR -48[ebp+edx*4]
	mov	ebx, edx
	mov	edx, DWORD PTR info@GOT[eax]
	mov	edx, DWORD PTR 8[edx]
	imul	ebx, edx
	mov	edx, DWORD PTR -80[ebp]
	mov	edx, DWORD PTR -68[ebp+edx*4]
	add	edx, ebx
	sal	edx, 2
	add	edx, ecx
	mov	DWORD PTR [edx], 0
	add	DWORD PTR -80[ebp], 1
.L68:
	cmp	DWORD PTR -80[ebp], 4
	jle	.L69
	add	DWORD PTR -84[ebp], 1
.L67:
	cmp	DWORD PTR -84[ebp], 8
	jle	.L70
	nop
	mov	eax, DWORD PTR -12[ebp]
	xor	eax, DWORD PTR gs:20
	je	.L71
	call	__stack_chk_fail_local
.L71:
	add	esp, 84
	pop	ebx
	.cfi_restore 3
	pop	ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE16:
	.size	print_black_u, .-print_black_u
	.globl	print_black_d
	.type	print_black_d, @function
print_black_d:
.LFB17:
	.cfi_startproc
	endbr32
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	ebx
	sub	esp, 84
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.ax
	add	eax, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	mov	ebx, DWORD PTR gs:20
	mov	DWORD PTR -12[ebp], ebx
	xor	ebx, ebx
	mov	edx, DWORD PTR 8[ebp]
	mov	DWORD PTR -76[ebp], edx
	mov	edx, DWORD PTR 12[ebp]
	add	edx, 1
	mov	DWORD PTR -72[ebp], edx
	mov	DWORD PTR -88[ebp], 0
	jmp	.L73
.L74:
	mov	ecx, DWORD PTR -72[ebp]
	mov	edx, DWORD PTR -88[ebp]
	add	ecx, edx
	mov	edx, DWORD PTR -88[ebp]
	mov	DWORD PTR -48[ebp+edx*4], ecx
	add	DWORD PTR -88[ebp], 1
.L73:
	cmp	DWORD PTR -88[ebp], 8
	jle	.L74
	mov	edx, DWORD PTR -76[ebp]
	sub	edx, 2
	mov	DWORD PTR -68[ebp], edx
	mov	edx, DWORD PTR -76[ebp]
	sub	edx, 1
	mov	DWORD PTR -64[ebp], edx
	mov	edx, DWORD PTR -76[ebp]
	mov	DWORD PTR -60[ebp], edx
	mov	edx, DWORD PTR -76[ebp]
	add	edx, 1
	mov	DWORD PTR -56[ebp], edx
	mov	edx, DWORD PTR -76[ebp]
	add	edx, 2
	mov	DWORD PTR -52[ebp], edx
	mov	DWORD PTR -84[ebp], 0
	jmp	.L75
.L78:
	mov	DWORD PTR -80[ebp], 0
	jmp	.L76
.L77:
	mov	edx, DWORD PTR ptr@GOT[eax]
	mov	ecx, DWORD PTR [edx]
	mov	edx, DWORD PTR -84[ebp]
	mov	edx, DWORD PTR -48[ebp+edx*4]
	mov	ebx, edx
	mov	edx, DWORD PTR info@GOT[eax]
	mov	edx, DWORD PTR 8[edx]
	imul	ebx, edx
	mov	edx, DWORD PTR -80[ebp]
	mov	edx, DWORD PTR -68[ebp+edx*4]
	add	edx, ebx
	sal	edx, 2
	add	edx, ecx
	mov	DWORD PTR [edx], 0
	add	DWORD PTR -80[ebp], 1
.L76:
	cmp	DWORD PTR -80[ebp], 4
	jle	.L77
	add	DWORD PTR -84[ebp], 1
.L75:
	cmp	DWORD PTR -84[ebp], 8
	jle	.L78
	nop
	mov	eax, DWORD PTR -12[ebp]
	xor	eax, DWORD PTR gs:20
	je	.L79
	call	__stack_chk_fail_local
.L79:
	add	esp, 84
	pop	ebx
	.cfi_restore 3
	pop	ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE17:
	.size	print_black_d, .-print_black_d
	.globl	print_r
	.type	print_r, @function
print_r:
.LFB18:
	.cfi_startproc
	endbr32
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	ebx
	sub	esp, 116
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	add	ebx, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	mov	eax, DWORD PTR 8[ebp]
	mov	DWORD PTR -108[ebp], eax
	mov	eax, DWORD PTR gs:20
	mov	DWORD PTR -12[ebp], eax
	xor	eax, eax
	mov	eax, DWORD PTR 12[ebp]
	add	eax, 1
	mov	DWORD PTR -76[ebp], eax
	mov	eax, DWORD PTR 16[ebp]
	mov	DWORD PTR -72[ebp], eax
	mov	DWORD PTR -92[ebp], 0
	jmp	.L81
.L82:
	mov	edx, DWORD PTR -76[ebp]
	mov	eax, DWORD PTR -92[ebp]
	add	edx, eax
	mov	eax, DWORD PTR -92[ebp]
	mov	DWORD PTR -48[ebp+eax*4], edx
	add	DWORD PTR -92[ebp], 1
.L81:
	cmp	DWORD PTR -92[ebp], 8
	jle	.L82
	mov	eax, DWORD PTR -72[ebp]
	sub	eax, 2
	mov	DWORD PTR -68[ebp], eax
	mov	eax, DWORD PTR -72[ebp]
	sub	eax, 1
	mov	DWORD PTR -64[ebp], eax
	mov	eax, DWORD PTR -72[ebp]
	mov	DWORD PTR -60[ebp], eax
	mov	eax, DWORD PTR -72[ebp]
	add	eax, 1
	mov	DWORD PTR -56[ebp], eax
	mov	eax, DWORD PTR -72[ebp]
	add	eax, 2
	mov	DWORD PTR -52[ebp], eax
	mov	DWORD PTR -88[ebp], 0
	jmp	.L83
.L86:
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -88[ebp]
	mov	eax, DWORD PTR -68[ebp+eax*4]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	eax, ecx
	mov	ecx, DWORD PTR -16[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	eax, DWORD PTR [eax]
	cmp	DWORD PTR 20[ebp], eax
	je	.L84
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -88[ebp]
	mov	eax, DWORD PTR -68[ebp+eax*4]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	eax, ecx
	mov	ecx, DWORD PTR -16[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	eax, DWORD PTR [eax]
	cmp	eax, 9055202
	je	.L84
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -88[ebp]
	mov	eax, DWORD PTR -68[ebp+eax*4]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	eax, ecx
	mov	ecx, DWORD PTR -16[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -108[ebp]
	mov	eax, DWORD PTR 184[eax]
	cmp	edx, eax
	jne	.L85
.L84:
	mov	eax, DWORD PTR -108[ebp]
	mov	DWORD PTR [eax], 1
	sub	esp, 12
	push	DWORD PTR -108[ebp]
	call	win
	add	esp, 16
.L85:
	add	DWORD PTR -88[ebp], 1
.L83:
	cmp	DWORD PTR -88[ebp], 4
	jle	.L86
	mov	DWORD PTR -84[ebp], 0
	jmp	.L87
.L90:
	mov	DWORD PTR -80[ebp], 0
	jmp	.L88
.L89:
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -80[ebp]
	mov	eax, DWORD PTR -68[ebp+eax*4]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR -84[ebp]
	mov	eax, DWORD PTR -48[ebp+eax*4]
	add	eax, ecx
	sal	eax, 2
	add	edx, eax
	mov	eax, DWORD PTR -108[ebp]
	mov	eax, DWORD PTR 184[eax]
	mov	DWORD PTR [edx], eax
	add	DWORD PTR -80[ebp], 1
.L88:
	cmp	DWORD PTR -80[ebp], 4
	jle	.L89
	add	DWORD PTR -84[ebp], 1
.L87:
	cmp	DWORD PTR -84[ebp], 8
	jle	.L90
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -68[ebp]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR -76[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	DWORD PTR [eax], 0
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -64[ebp]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR -76[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	DWORD PTR [eax], 0
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -60[ebp]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR -76[ebp]
	add	eax, ecx
	sal	eax, 2
	add	edx, eax
	mov	eax, DWORD PTR -108[ebp]
	mov	eax, DWORD PTR 184[eax]
	mov	DWORD PTR [edx], eax
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -56[ebp]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR -76[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	DWORD PTR [eax], 0
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -52[ebp]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR -76[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	DWORD PTR [eax], 0
	mov	eax, DWORD PTR -76[ebp]
	add	eax, 9
	mov	edx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	ecx, DWORD PTR [eax]
	mov	eax, edx
	mov	edx, 0
	div	ecx
	mov	eax, edx
	mov	DWORD PTR 12[ebp], eax
	nop
	mov	eax, DWORD PTR -12[ebp]
	xor	eax, DWORD PTR gs:20
	je	.L91
	call	__stack_chk_fail_local
.L91:
	mov	ebx, DWORD PTR -4[ebp]
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE18:
	.size	print_r, .-print_r
	.globl	print_l
	.type	print_l, @function
print_l:
.LFB19:
	.cfi_startproc
	endbr32
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	ebx
	sub	esp, 116
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	add	ebx, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	mov	eax, DWORD PTR 8[ebp]
	mov	DWORD PTR -108[ebp], eax
	mov	eax, DWORD PTR gs:20
	mov	DWORD PTR -12[ebp], eax
	xor	eax, eax
	mov	eax, DWORD PTR 12[ebp]
	sub	eax, 1
	mov	DWORD PTR -76[ebp], eax
	mov	eax, DWORD PTR 16[ebp]
	mov	DWORD PTR -72[ebp], eax
	mov	DWORD PTR -92[ebp], 0
	jmp	.L93
.L94:
	mov	eax, DWORD PTR -76[ebp]
	sub	eax, DWORD PTR -92[ebp]
	mov	edx, eax
	mov	eax, DWORD PTR -92[ebp]
	mov	DWORD PTR -48[ebp+eax*4], edx
	add	DWORD PTR -92[ebp], 1
.L93:
	cmp	DWORD PTR -92[ebp], 8
	jle	.L94
	mov	eax, DWORD PTR -72[ebp]
	sub	eax, 2
	mov	DWORD PTR -68[ebp], eax
	mov	eax, DWORD PTR -72[ebp]
	sub	eax, 1
	mov	DWORD PTR -64[ebp], eax
	mov	eax, DWORD PTR -72[ebp]
	mov	DWORD PTR -60[ebp], eax
	mov	eax, DWORD PTR -72[ebp]
	add	eax, 1
	mov	DWORD PTR -56[ebp], eax
	mov	eax, DWORD PTR -72[ebp]
	add	eax, 2
	mov	DWORD PTR -52[ebp], eax
	mov	DWORD PTR -88[ebp], 0
	jmp	.L95
.L98:
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -88[ebp]
	mov	eax, DWORD PTR -68[ebp+eax*4]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	eax, ecx
	mov	ecx, DWORD PTR -16[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	eax, DWORD PTR [eax]
	cmp	DWORD PTR 20[ebp], eax
	je	.L96
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -88[ebp]
	mov	eax, DWORD PTR -68[ebp+eax*4]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	eax, ecx
	mov	ecx, DWORD PTR -16[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	eax, DWORD PTR [eax]
	cmp	eax, 9055202
	je	.L96
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -88[ebp]
	mov	eax, DWORD PTR -68[ebp+eax*4]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	eax, ecx
	mov	ecx, DWORD PTR -16[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -108[ebp]
	mov	eax, DWORD PTR 184[eax]
	cmp	edx, eax
	jne	.L97
.L96:
	mov	eax, DWORD PTR -108[ebp]
	mov	DWORD PTR [eax], 1
	sub	esp, 12
	push	DWORD PTR -108[ebp]
	call	win
	add	esp, 16
.L97:
	add	DWORD PTR -88[ebp], 1
.L95:
	cmp	DWORD PTR -88[ebp], 4
	jle	.L98
	mov	DWORD PTR -84[ebp], 0
	jmp	.L99
.L102:
	mov	DWORD PTR -80[ebp], 0
	jmp	.L100
.L101:
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -80[ebp]
	mov	eax, DWORD PTR -68[ebp+eax*4]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR -84[ebp]
	mov	eax, DWORD PTR -48[ebp+eax*4]
	add	eax, ecx
	sal	eax, 2
	add	edx, eax
	mov	eax, DWORD PTR -108[ebp]
	mov	eax, DWORD PTR 184[eax]
	mov	DWORD PTR [edx], eax
	add	DWORD PTR -80[ebp], 1
.L100:
	cmp	DWORD PTR -80[ebp], 4
	jle	.L101
	add	DWORD PTR -84[ebp], 1
.L99:
	cmp	DWORD PTR -84[ebp], 8
	jle	.L102
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -68[ebp]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR -76[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	DWORD PTR [eax], 0
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -64[ebp]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR -76[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	DWORD PTR [eax], 0
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -60[ebp]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR -76[ebp]
	add	eax, ecx
	sal	eax, 2
	add	edx, eax
	mov	eax, DWORD PTR -108[ebp]
	mov	eax, DWORD PTR 184[eax]
	mov	DWORD PTR [edx], eax
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -56[ebp]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR -76[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	DWORD PTR [eax], 0
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -52[ebp]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR -76[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	DWORD PTR [eax], 0
	mov	eax, DWORD PTR -76[ebp]
	add	eax, 9
	mov	edx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	ecx, DWORD PTR [eax]
	mov	eax, edx
	mov	edx, 0
	div	ecx
	mov	eax, edx
	mov	DWORD PTR 12[ebp], eax
	nop
	mov	eax, DWORD PTR -12[ebp]
	xor	eax, DWORD PTR gs:20
	je	.L103
	call	__stack_chk_fail_local
.L103:
	mov	ebx, DWORD PTR -4[ebp]
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE19:
	.size	print_l, .-print_l
	.globl	print_u
	.type	print_u, @function
print_u:
.LFB20:
	.cfi_startproc
	endbr32
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	ebx
	sub	esp, 116
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	add	ebx, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	mov	eax, DWORD PTR 8[ebp]
	mov	DWORD PTR -108[ebp], eax
	mov	eax, DWORD PTR gs:20
	mov	DWORD PTR -12[ebp], eax
	xor	eax, eax
	mov	eax, DWORD PTR 12[ebp]
	mov	DWORD PTR -76[ebp], eax
	mov	eax, DWORD PTR 16[ebp]
	sub	eax, 1
	mov	DWORD PTR -72[ebp], eax
	mov	DWORD PTR -92[ebp], 0
	jmp	.L105
.L106:
	mov	eax, DWORD PTR -72[ebp]
	sub	eax, DWORD PTR -92[ebp]
	mov	edx, eax
	mov	eax, DWORD PTR -92[ebp]
	mov	DWORD PTR -48[ebp+eax*4], edx
	add	DWORD PTR -92[ebp], 1
.L105:
	cmp	DWORD PTR -92[ebp], 8
	jle	.L106
	mov	eax, DWORD PTR -76[ebp]
	sub	eax, 2
	mov	DWORD PTR -68[ebp], eax
	mov	eax, DWORD PTR -76[ebp]
	sub	eax, 1
	mov	DWORD PTR -64[ebp], eax
	mov	eax, DWORD PTR -76[ebp]
	mov	DWORD PTR -60[ebp], eax
	mov	eax, DWORD PTR -76[ebp]
	add	eax, 1
	mov	DWORD PTR -56[ebp], eax
	mov	eax, DWORD PTR -76[ebp]
	add	eax, 2
	mov	DWORD PTR -52[ebp], eax
	mov	DWORD PTR -88[ebp], 0
	jmp	.L107
.L110:
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -16[ebp]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR -88[ebp]
	mov	eax, DWORD PTR -68[ebp+eax*4]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	eax, DWORD PTR [eax]
	cmp	DWORD PTR 20[ebp], eax
	je	.L108
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -16[ebp]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR -88[ebp]
	mov	eax, DWORD PTR -68[ebp+eax*4]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	eax, DWORD PTR [eax]
	cmp	eax, 9055202
	je	.L108
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -16[ebp]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR -88[ebp]
	mov	eax, DWORD PTR -68[ebp+eax*4]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -108[ebp]
	mov	eax, DWORD PTR 184[eax]
	cmp	edx, eax
	jne	.L109
.L108:
	mov	eax, DWORD PTR -108[ebp]
	mov	DWORD PTR [eax], 1
	sub	esp, 12
	push	DWORD PTR -108[ebp]
	call	win
	add	esp, 16
.L109:
	add	DWORD PTR -88[ebp], 1
.L107:
	cmp	DWORD PTR -88[ebp], 4
	jle	.L110
	mov	DWORD PTR -84[ebp], 0
	jmp	.L111
.L114:
	mov	DWORD PTR -80[ebp], 0
	jmp	.L112
.L113:
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -84[ebp]
	mov	eax, DWORD PTR -48[ebp+eax*4]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR -80[ebp]
	mov	eax, DWORD PTR -68[ebp+eax*4]
	add	eax, ecx
	sal	eax, 2
	add	edx, eax
	mov	eax, DWORD PTR -108[ebp]
	mov	eax, DWORD PTR 184[eax]
	mov	DWORD PTR [edx], eax
	add	DWORD PTR -80[ebp], 1
.L112:
	cmp	DWORD PTR -80[ebp], 4
	jle	.L113
	add	DWORD PTR -84[ebp], 1
.L111:
	cmp	DWORD PTR -84[ebp], 8
	jle	.L114
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	ecx, DWORD PTR 8[eax]
	mov	eax, DWORD PTR -72[ebp]
	imul	eax, ecx
	mov	ecx, DWORD PTR -68[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	DWORD PTR [eax], 0
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	ecx, DWORD PTR 8[eax]
	mov	eax, DWORD PTR -72[ebp]
	imul	eax, ecx
	mov	ecx, DWORD PTR -64[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	DWORD PTR [eax], 0
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	ecx, DWORD PTR 8[eax]
	mov	eax, DWORD PTR -72[ebp]
	imul	eax, ecx
	mov	ecx, DWORD PTR -60[ebp]
	add	eax, ecx
	sal	eax, 2
	add	edx, eax
	mov	eax, DWORD PTR -108[ebp]
	mov	eax, DWORD PTR 184[eax]
	mov	DWORD PTR [edx], eax
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	ecx, DWORD PTR 8[eax]
	mov	eax, DWORD PTR -72[ebp]
	imul	eax, ecx
	mov	ecx, DWORD PTR -56[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	DWORD PTR [eax], 0
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	ecx, DWORD PTR 8[eax]
	mov	eax, DWORD PTR -72[ebp]
	imul	eax, ecx
	mov	ecx, DWORD PTR -52[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	DWORD PTR [eax], 0
	mov	eax, DWORD PTR -72[ebp]
	sub	eax, 9
	mov	edx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	ecx, DWORD PTR 4[eax]
	mov	eax, edx
	mov	edx, 0
	div	ecx
	mov	eax, edx
	mov	DWORD PTR 16[ebp], eax
	nop
	mov	eax, DWORD PTR -12[ebp]
	xor	eax, DWORD PTR gs:20
	je	.L115
	call	__stack_chk_fail_local
.L115:
	mov	ebx, DWORD PTR -4[ebp]
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE20:
	.size	print_u, .-print_u
	.globl	print_d
	.type	print_d, @function
print_d:
.LFB21:
	.cfi_startproc
	endbr32
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	ebx
	sub	esp, 116
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	add	ebx, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	mov	eax, DWORD PTR 8[ebp]
	mov	DWORD PTR -108[ebp], eax
	mov	eax, DWORD PTR gs:20
	mov	DWORD PTR -12[ebp], eax
	xor	eax, eax
	mov	eax, DWORD PTR 12[ebp]
	mov	DWORD PTR -76[ebp], eax
	mov	eax, DWORD PTR 16[ebp]
	add	eax, 1
	mov	DWORD PTR -72[ebp], eax
	mov	DWORD PTR -92[ebp], 0
	jmp	.L117
.L118:
	mov	edx, DWORD PTR -72[ebp]
	mov	eax, DWORD PTR -92[ebp]
	add	edx, eax
	mov	eax, DWORD PTR -92[ebp]
	mov	DWORD PTR -48[ebp+eax*4], edx
	add	DWORD PTR -92[ebp], 1
.L117:
	cmp	DWORD PTR -92[ebp], 8
	jle	.L118
	mov	eax, DWORD PTR -76[ebp]
	sub	eax, 2
	mov	DWORD PTR -68[ebp], eax
	mov	eax, DWORD PTR -76[ebp]
	sub	eax, 1
	mov	DWORD PTR -64[ebp], eax
	mov	eax, DWORD PTR -76[ebp]
	mov	DWORD PTR -60[ebp], eax
	mov	eax, DWORD PTR -76[ebp]
	add	eax, 1
	mov	DWORD PTR -56[ebp], eax
	mov	eax, DWORD PTR -76[ebp]
	add	eax, 2
	mov	DWORD PTR -52[ebp], eax
	mov	DWORD PTR -88[ebp], 0
	jmp	.L119
.L122:
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -16[ebp]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR -88[ebp]
	mov	eax, DWORD PTR -68[ebp+eax*4]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	eax, DWORD PTR [eax]
	cmp	DWORD PTR 20[ebp], eax
	je	.L120
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -16[ebp]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR -88[ebp]
	mov	eax, DWORD PTR -68[ebp+eax*4]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	eax, DWORD PTR [eax]
	cmp	eax, 9055202
	je	.L120
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -16[ebp]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR -88[ebp]
	mov	eax, DWORD PTR -68[ebp+eax*4]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -108[ebp]
	mov	eax, DWORD PTR 184[eax]
	cmp	edx, eax
	jne	.L121
.L120:
	mov	eax, DWORD PTR -108[ebp]
	mov	DWORD PTR [eax], 1
	sub	esp, 12
	push	DWORD PTR -108[ebp]
	call	win
	add	esp, 16
.L121:
	add	DWORD PTR -88[ebp], 1
.L119:
	cmp	DWORD PTR -88[ebp], 4
	jle	.L122
	mov	DWORD PTR -84[ebp], 0
	jmp	.L123
.L126:
	mov	DWORD PTR -80[ebp], 0
	jmp	.L124
.L125:
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -84[ebp]
	mov	eax, DWORD PTR -48[ebp+eax*4]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR -80[ebp]
	mov	eax, DWORD PTR -68[ebp+eax*4]
	add	eax, ecx
	sal	eax, 2
	add	edx, eax
	mov	eax, DWORD PTR -108[ebp]
	mov	eax, DWORD PTR 184[eax]
	mov	DWORD PTR [edx], eax
	add	DWORD PTR -80[ebp], 1
.L124:
	cmp	DWORD PTR -80[ebp], 4
	jle	.L125
	add	DWORD PTR -84[ebp], 1
.L123:
	cmp	DWORD PTR -84[ebp], 8
	jle	.L126
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	ecx, DWORD PTR 8[eax]
	mov	eax, DWORD PTR -72[ebp]
	imul	eax, ecx
	mov	ecx, DWORD PTR -68[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	DWORD PTR [eax], 0
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	ecx, DWORD PTR 8[eax]
	mov	eax, DWORD PTR -72[ebp]
	imul	eax, ecx
	mov	ecx, DWORD PTR -64[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	DWORD PTR [eax], 0
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	ecx, DWORD PTR 8[eax]
	mov	eax, DWORD PTR -72[ebp]
	imul	eax, ecx
	mov	ecx, DWORD PTR -60[ebp]
	add	eax, ecx
	sal	eax, 2
	add	edx, eax
	mov	eax, DWORD PTR -108[ebp]
	mov	eax, DWORD PTR 184[eax]
	mov	DWORD PTR [edx], eax
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	ecx, DWORD PTR 8[eax]
	mov	eax, DWORD PTR -72[ebp]
	imul	eax, ecx
	mov	ecx, DWORD PTR -56[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	DWORD PTR [eax], 0
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	ecx, DWORD PTR 8[eax]
	mov	eax, DWORD PTR -72[ebp]
	imul	eax, ecx
	mov	ecx, DWORD PTR -52[ebp]
	add	eax, ecx
	sal	eax, 2
	add	eax, edx
	mov	DWORD PTR [eax], 0
	mov	eax, DWORD PTR -72[ebp]
	add	eax, 9
	mov	edx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	ecx, DWORD PTR 4[eax]
	mov	eax, edx
	mov	edx, 0
	div	ecx
	mov	eax, edx
	mov	DWORD PTR 16[ebp], eax
	nop
	mov	eax, DWORD PTR -12[ebp]
	xor	eax, DWORD PTR gs:20
	je	.L127
	call	__stack_chk_fail_local
.L127:
	mov	ebx, DWORD PTR -4[ebp]
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE21:
	.size	print_d, .-print_d
	.globl	print
	.type	print, @function
print:
.LFB22:
	.cfi_startproc
	endbr32
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	ebx
	sub	esp, 4
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	add	ebx, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR 16[ebp]
	mov	eax, DWORD PTR [eax]
	mov	ecx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	imul	ecx, eax
	mov	eax, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR [eax]
	add	eax, ecx
	sal	eax, 2
	add	edx, eax
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR 184[eax]
	mov	DWORD PTR [edx], eax
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR 16[eax]
	cmp	eax, 1
	jne	.L129
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR 12[eax]
	cmp	eax, 97
	jne	.L130
	mov	eax, DWORD PTR 16[ebp]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	edx
	push	eax
	call	print_black_l
	add	esp, 16
.L130:
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR 12[eax]
	cmp	eax, 100
	jne	.L131
	mov	eax, DWORD PTR 16[ebp]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	edx
	push	eax
	call	print_black_r
	add	esp, 16
.L131:
	mov	eax, DWORD PTR 8[ebp]
	mov	DWORD PTR 12[eax], 119
	mov	eax, DWORD PTR 16[ebp]
	mov	eax, DWORD PTR [eax]
	mov	edx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 4[eax]
	add	eax, edx
	lea	edx, -1[eax]
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	ecx, DWORD PTR 4[eax]
	mov	eax, edx
	mov	edx, 0
	div	ecx
	mov	eax, edx
	mov	edx, eax
	mov	eax, DWORD PTR 16[ebp]
	mov	DWORD PTR [eax], edx
.L129:
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR 16[eax]
	cmp	eax, 2
	jne	.L132
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR 12[eax]
	cmp	eax, 97
	jne	.L133
	mov	eax, DWORD PTR 16[ebp]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	edx
	push	eax
	call	print_black_l
	add	esp, 16
.L133:
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR 12[eax]
	cmp	eax, 100
	jne	.L134
	mov	eax, DWORD PTR 16[ebp]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	edx
	push	eax
	call	print_black_r
	add	esp, 16
.L134:
	mov	eax, DWORD PTR 8[ebp]
	mov	DWORD PTR 12[eax], 115
	mov	eax, DWORD PTR 16[ebp]
	mov	eax, DWORD PTR [eax]
	add	eax, 1
	mov	edx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	ecx, DWORD PTR 4[eax]
	mov	eax, edx
	mov	edx, 0
	div	ecx
	mov	eax, edx
	mov	edx, eax
	mov	eax, DWORD PTR 16[ebp]
	mov	DWORD PTR [eax], edx
.L132:
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR 16[eax]
	cmp	eax, 3
	jne	.L135
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR 12[eax]
	cmp	eax, 119
	jne	.L136
	mov	eax, DWORD PTR 16[ebp]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	edx
	push	eax
	call	print_black_u
	add	esp, 16
.L136:
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR 12[eax]
	cmp	eax, 115
	jne	.L137
	mov	eax, DWORD PTR 16[ebp]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	edx
	push	eax
	call	print_black_d
	add	esp, 16
.L137:
	mov	eax, DWORD PTR 8[ebp]
	mov	DWORD PTR 12[eax], 97
	mov	eax, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR [eax]
	mov	edx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	add	eax, edx
	lea	edx, -1[eax]
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	ecx, DWORD PTR [eax]
	mov	eax, edx
	mov	edx, 0
	div	ecx
	mov	eax, edx
	mov	edx, eax
	mov	eax, DWORD PTR 12[ebp]
	mov	DWORD PTR [eax], edx
.L135:
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR 16[eax]
	cmp	eax, 4
	jne	.L138
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR 12[eax]
	cmp	eax, 119
	jne	.L139
	mov	eax, DWORD PTR 16[ebp]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	edx
	push	eax
	call	print_black_u
	add	esp, 16
.L139:
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR 12[eax]
	cmp	eax, 115
	jne	.L140
	mov	eax, DWORD PTR 16[ebp]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	edx
	push	eax
	call	print_black_d
	add	esp, 16
.L140:
	mov	eax, DWORD PTR 8[ebp]
	mov	DWORD PTR 12[eax], 100
	mov	eax, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR [eax]
	add	eax, 1
	mov	edx, eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	ecx, DWORD PTR [eax]
	mov	eax, edx
	mov	edx, 0
	div	ecx
	mov	eax, edx
	mov	edx, eax
	mov	eax, DWORD PTR 12[ebp]
	mov	DWORD PTR [eax], edx
.L138:
	call	border_print
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR 16[eax]
	cmp	eax, 1
	jne	.L141
	mov	eax, DWORD PTR 16[ebp]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR [eax]
	push	DWORD PTR 20[ebp]
	push	edx
	push	eax
	push	DWORD PTR 8[ebp]
	call	print_u
	add	esp, 16
.L141:
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR 16[eax]
	cmp	eax, 2
	jne	.L142
	mov	eax, DWORD PTR 16[ebp]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR [eax]
	push	DWORD PTR 20[ebp]
	push	edx
	push	eax
	push	DWORD PTR 8[ebp]
	call	print_d
	add	esp, 16
.L142:
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR 16[eax]
	cmp	eax, 3
	jne	.L143
	mov	eax, DWORD PTR 16[ebp]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR [eax]
	push	DWORD PTR 20[ebp]
	push	edx
	push	eax
	push	DWORD PTR 8[ebp]
	call	print_l
	add	esp, 16
.L143:
	mov	eax, DWORD PTR 8[ebp]
	mov	eax, DWORD PTR 16[eax]
	cmp	eax, 4
	jne	.L144
	mov	eax, DWORD PTR 16[ebp]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR [eax]
	push	DWORD PTR 20[ebp]
	push	edx
	push	eax
	push	DWORD PTR 8[ebp]
	call	print_r
	add	esp, 16
.L144:
	nop
	mov	ebx, DWORD PTR -4[ebp]
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE22:
	.size	print, .-print
	.section	.rodata
.LC7:
	.string	"SLEVA %d sum1\t %d sum2\n"
.LC8:
	.string	"SPRava %d sum1\t %d sum2\n"
	.text
	.globl	init_bikes_and_cikl
	.type	init_bikes_and_cikl, @function
init_bikes_and_cikl:
.LFB23:
	.cfi_startproc
	endbr32
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	ebx
	sub	esp, 436
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	add	ebx, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	mov	eax, DWORD PTR 8[ebp]
	mov	DWORD PTR -428[ebp], eax
	mov	eax, DWORD PTR gs:20
	mov	DWORD PTR -12[ebp], eax
	xor	eax, eax
	mov	eax, DWORD PTR sum2@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR sum1@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	cmp	edx, eax
	jle	.L146
	mov	eax, DWORD PTR sum2@GOT[ebx]
	mov	ecx, DWORD PTR [eax]
	mov	eax, DWORD PTR sum1@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR f@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	push	ecx
	push	edx
	lea	edx, .LC7@GOTOFF[ebx]
	push	edx
	push	eax
	call	fprintf@PLT
	add	esp, 16
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	eax, 10
	mov	DWORD PTR -392[ebp], eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 4[eax]
	sub	eax, 30
	mov	DWORD PTR -388[ebp], eax
	mov	DWORD PTR -212[ebp], 16816537
	mov	DWORD PTR -380[ebp], 0
	mov	DWORD PTR -384[ebp], 46
	mov	DWORD PTR -396[ebp], 0
	mov	DWORD PTR -200[ebp], 10
	mov	DWORD PTR -196[ebp], 10
	mov	DWORD PTR -20[ebp], 16711680
	mov	DWORD PTR -188[ebp], 0
	mov	DWORD PTR -192[ebp], 46
	mov	DWORD PTR -204[ebp], 0
	mov	eax, DWORD PTR -380[ebp]
	mov	DWORD PTR way@GOTOFF[ebx], eax
	mov	eax, DWORD PTR -188[ebp]
	mov	DWORD PTR way2@GOTOFF[ebx], eax
	mov	DWORD PTR -376[ebp], 66
	mov	DWORD PTR -184[ebp], 82
	push	0
	lea	eax, press_first_bike@GOTOFF[ebx]
	push	eax
	push	0
	mov	eax, DWORD PTR thread_key1@GOT[ebx]
	push	eax
	call	pthread_create@PLT
	add	esp, 16
	push	0
	lea	eax, press_second_bike@GOTOFF[ebx]
	push	eax
	push	0
	mov	eax, DWORD PTR thread_key2@GOT[ebx]
	push	eax
	call	pthread_create@PLT
	add	esp, 16
	lea	eax, -396[ebp]
	push	eax
	lea	eax, keypress_first@GOTOFF[ebx]
	push	eax
	push	0
	mov	eax, DWORD PTR thread@GOT[ebx]
	push	eax
	call	pthread_create@PLT
	add	esp, 16
	lea	eax, -204[ebp]
	push	eax
	lea	eax, keypress_second@GOTOFF[ebx]
	push	eax
	push	0
	mov	eax, DWORD PTR thread2@GOT[ebx]
	push	eax
	call	pthread_create@PLT
	add	esp, 16
	jmp	.L147
.L148:
	mov	eax, DWORD PTR -20[ebp]
	push	eax
	lea	eax, -396[ebp]
	add	eax, 8
	push	eax
	lea	eax, -396[ebp]
	add	eax, 4
	push	eax
	lea	eax, -396[ebp]
	push	eax
	call	print
	add	esp, 16
	mov	eax, DWORD PTR -212[ebp]
	push	eax
	lea	eax, -204[ebp]
	add	eax, 8
	push	eax
	lea	eax, -204[ebp]
	add	eax, 4
	push	eax
	lea	eax, -204[ebp]
	push	eax
	call	print
	add	esp, 16
	mov	eax, DWORD PTR i@GOTOFF[ebx]
	add	eax, 1
	mov	DWORD PTR i@GOTOFF[ebx], eax
	sub	esp, 12
	push	62500
	call	usleep@PLT
	add	esp, 16
.L147:
	mov	eax, DWORD PTR work_flag@GOTOFF[ebx]
	test	eax, eax
	jne	.L148
	mov	eax, DWORD PTR thread_key1@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	0
	push	eax
	call	pthread_join@PLT
	add	esp, 16
	mov	eax, DWORD PTR thread_key2@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	0
	push	eax
	call	pthread_join@PLT
	add	esp, 16
	mov	eax, DWORD PTR thread@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	0
	push	eax
	call	pthread_join@PLT
	add	esp, 16
	mov	eax, DWORD PTR thread2@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	0
	push	eax
	call	pthread_join@PLT
	add	esp, 16
	jmp	.L149
.L146:
	mov	eax, DWORD PTR sum1@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR sum2@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	cmp	edx, eax
	jle	.L149
	mov	eax, DWORD PTR sum2@GOT[ebx]
	mov	ecx, DWORD PTR [eax]
	mov	eax, DWORD PTR sum1@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR f@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	push	ecx
	push	edx
	lea	edx, .LC8@GOTOFF[ebx]
	push	edx
	push	eax
	call	fprintf@PLT
	add	esp, 16
	mov	DWORD PTR -392[ebp], 10
	mov	DWORD PTR -388[ebp], 10
	mov	DWORD PTR -212[ebp], 16711680
	mov	DWORD PTR -380[ebp], 0
	mov	DWORD PTR -384[ebp], 46
	mov	DWORD PTR -396[ebp], 0
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	eax, 10
	mov	DWORD PTR -200[ebp], eax
	mov	eax, DWORD PTR info@GOT[ebx]
	mov	eax, DWORD PTR 4[eax]
	sub	eax, 30
	mov	DWORD PTR -196[ebp], eax
	mov	DWORD PTR -20[ebp], 16816537
	mov	DWORD PTR -188[ebp], 0
	mov	DWORD PTR -192[ebp], 46
	mov	DWORD PTR -204[ebp], 0
	mov	eax, DWORD PTR -380[ebp]
	mov	DWORD PTR way@GOTOFF[ebx], eax
	mov	eax, DWORD PTR -188[ebp]
	mov	DWORD PTR way2@GOTOFF[ebx], eax
	mov	DWORD PTR -376[ebp], 82
	mov	DWORD PTR -184[ebp], 66
	push	0
	lea	eax, press_first_bike@GOTOFF[ebx]
	push	eax
	push	0
	lea	eax, -404[ebp]
	push	eax
	call	pthread_create@PLT
	add	esp, 16
	push	0
	lea	eax, press_second_bike@GOTOFF[ebx]
	push	eax
	push	0
	lea	eax, -400[ebp]
	push	eax
	call	pthread_create@PLT
	add	esp, 16
	lea	eax, -396[ebp]
	push	eax
	lea	eax, keypress_first@GOTOFF[ebx]
	push	eax
	push	0
	lea	eax, -412[ebp]
	push	eax
	call	pthread_create@PLT
	add	esp, 16
	lea	eax, -204[ebp]
	push	eax
	lea	eax, keypress_second@GOTOFF[ebx]
	push	eax
	push	0
	lea	eax, -408[ebp]
	push	eax
	call	pthread_create@PLT
	add	esp, 16
	jmp	.L150
.L151:
	mov	eax, DWORD PTR -20[ebp]
	push	eax
	lea	eax, -396[ebp]
	add	eax, 8
	push	eax
	lea	eax, -396[ebp]
	add	eax, 4
	push	eax
	lea	eax, -396[ebp]
	push	eax
	call	print
	add	esp, 16
	mov	eax, DWORD PTR -212[ebp]
	push	eax
	lea	eax, -204[ebp]
	add	eax, 8
	push	eax
	lea	eax, -204[ebp]
	add	eax, 4
	push	eax
	lea	eax, -204[ebp]
	push	eax
	call	print
	add	esp, 16
	mov	eax, DWORD PTR i@GOTOFF[ebx]
	add	eax, 1
	mov	DWORD PTR i@GOTOFF[ebx], eax
	sub	esp, 12
	push	62500
	call	usleep@PLT
	add	esp, 16
.L150:
	mov	eax, DWORD PTR work_flag@GOTOFF[ebx]
	test	eax, eax
	jne	.L151
	mov	eax, DWORD PTR -404[ebp]
	sub	esp, 8
	push	0
	push	eax
	call	pthread_join@PLT
	add	esp, 16
	mov	eax, DWORD PTR -400[ebp]
	sub	esp, 8
	push	0
	push	eax
	call	pthread_join@PLT
	add	esp, 16
	mov	eax, DWORD PTR -412[ebp]
	sub	esp, 8
	push	0
	push	eax
	call	pthread_join@PLT
	add	esp, 16
	mov	eax, DWORD PTR -408[ebp]
	sub	esp, 8
	push	0
	push	eax
	call	pthread_join@PLT
	add	esp, 16
.L149:
	nop
	mov	ecx, DWORD PTR -12[ebp]
	xor	ecx, DWORD PTR gs:20
	je	.L152
	call	__stack_chk_fail_local
.L152:
	mov	ebx, DWORD PTR -4[ebp]
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE23:
	.size	init_bikes_and_cikl, .-init_bikes_and_cikl
	.section	.rodata
	.align 4
.LC9:
	.string	"Usage: %s Xres Yres Your_ip Enemy_ip\n"
.LC10:
	.string	"%d.%d.%d.%d"
.LC11:
	.string	"w"
.LC12:
	.string	"debug.txt"
.LC13:
	.string	"MAIN %d sum1\t %d sum2\n"
.LC14:
	.string	"socket creation failed"
.LC15:
	.string	"bind failed"
	.text
	.globl	main
	.type	main, @function
main:
.LFB24:
	.cfi_startproc
	endbr32
	lea	ecx, 4[esp]
	.cfi_def_cfa 1, 0
	and	esp, -16
	push	DWORD PTR -4[ecx]
	push	ebp
	mov	ebp, esp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	push	esi
	push	ebx
	push	ecx
	.cfi_escape 0xf,0x3,0x75,0x74,0x6
	.cfi_escape 0x10,0x6,0x2,0x75,0x7c
	.cfi_escape 0x10,0x3,0x2,0x75,0x78
	sub	esp, 44
	call	__x86.get_pc_thunk.bx
	add	ebx, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	mov	esi, ecx
	mov	eax, DWORD PTR 4[esi]
	mov	DWORD PTR -44[ebp], eax
	mov	eax, DWORD PTR gs:20
	mov	DWORD PTR -28[ebp], eax
	xor	eax, eax
	sub	esp, 8
	lea	eax, handler@GOTOFF[ebx]
	push	eax
	push	2
	call	signal@PLT
	add	esp, 16
	cmp	DWORD PTR [esi], 4
	jg	.L154
	mov	eax, DWORD PTR -44[ebp]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	eax
	lea	eax, .LC9@GOTOFF[ebx]
	push	eax
	call	printf@PLT
	add	esp, 16
	sub	esp, 12
	push	0
	call	exit@PLT
.L154:
	mov	eax, DWORD PTR -44[ebp]
	add	eax, 4
	mov	eax, DWORD PTR [eax]
	sub	esp, 12
	push	eax
	call	atoi@PLT
	add	esp, 16
	mov	DWORD PTR -36[ebp], eax
	mov	eax, DWORD PTR -44[ebp]
	add	eax, 8
	mov	eax, DWORD PTR [eax]
	sub	esp, 12
	push	eax
	call	atoi@PLT
	add	esp, 16
	mov	DWORD PTR -32[ebp], eax
	mov	eax, DWORD PTR -44[ebp]
	add	eax, 12
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	mov	edx, DWORD PTR fi@GOT[ebx]
	lea	edx, 12[edx]
	push	edx
	mov	edx, DWORD PTR fi@GOT[ebx]
	lea	edx, 8[edx]
	push	edx
	mov	edx, DWORD PTR fi@GOT[ebx]
	lea	edx, 4[edx]
	push	edx
	mov	edx, DWORD PTR fi@GOT[ebx]
	push	edx
	lea	edx, .LC10@GOTOFF[ebx]
	push	edx
	push	eax
	call	__isoc99_sscanf@PLT
	add	esp, 32
	mov	eax, DWORD PTR -44[ebp]
	add	eax, 16
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	mov	edx, DWORD PTR si@GOT[ebx]
	lea	edx, 12[edx]
	push	edx
	mov	edx, DWORD PTR si@GOT[ebx]
	lea	edx, 8[edx]
	push	edx
	mov	edx, DWORD PTR si@GOT[ebx]
	lea	edx, 4[edx]
	push	edx
	mov	edx, DWORD PTR si@GOT[ebx]
	push	edx
	lea	edx, .LC10@GOTOFF[ebx]
	push	edx
	push	eax
	call	__isoc99_sscanf@PLT
	add	esp, 32
	mov	eax, DWORD PTR fi@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR fi@GOT[ebx]
	mov	eax, DWORD PTR 4[eax]
	add	edx, eax
	mov	eax, DWORD PTR fi@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	add	edx, eax
	mov	eax, DWORD PTR fi@GOT[ebx]
	mov	eax, DWORD PTR 12[eax]
	add	edx, eax
	mov	eax, DWORD PTR sum1@GOT[ebx]
	mov	DWORD PTR [eax], edx
	mov	eax, DWORD PTR si@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR si@GOT[ebx]
	mov	eax, DWORD PTR 4[eax]
	add	edx, eax
	mov	eax, DWORD PTR si@GOT[ebx]
	mov	eax, DWORD PTR 8[eax]
	add	edx, eax
	mov	eax, DWORD PTR si@GOT[ebx]
	mov	eax, DWORD PTR 12[eax]
	add	edx, eax
	mov	eax, DWORD PTR sum2@GOT[ebx]
	mov	DWORD PTR [eax], edx
	sub	esp, 8
	lea	eax, .LC11@GOTOFF[ebx]
	push	eax
	lea	eax, .LC12@GOTOFF[ebx]
	push	eax
	call	fopen@PLT
	add	esp, 16
	mov	edx, DWORD PTR f@GOT[ebx]
	mov	DWORD PTR [edx], eax
	mov	eax, DWORD PTR sum2@GOT[ebx]
	mov	ecx, DWORD PTR [eax]
	mov	eax, DWORD PTR sum1@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR f@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	push	ecx
	push	edx
	lea	edx, .LC13@GOTOFF[ebx]
	push	edx
	push	eax
	call	fprintf@PLT
	add	esp, 16
	sub	esp, 8
	push	DWORD PTR -44[ebp]
	lea	eax, -36[ebp]
	push	eax
	call	initialization
	add	esp, 16
	sub	esp, 4
	push	0
	push	2
	push	2
	call	socket@PLT
	add	esp, 16
	mov	edx, DWORD PTR my_fd@GOT[ebx]
	mov	DWORD PTR [edx], eax
	mov	eax, DWORD PTR my_fd@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	test	eax, eax
	jns	.L155
	sub	esp, 12
	lea	eax, .LC14@GOTOFF[ebx]
	push	eax
	call	perror@PLT
	add	esp, 16
	mov	eax, DWORD PTR map_size@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	edx
	push	eax
	call	munmap@PLT
	add	esp, 16
	call	endwin@PLT
	sub	esp, 12
	push	1
	call	exit@PLT
.L155:
	mov	eax, DWORD PTR me@GOT[ebx]
	mov	WORD PTR [eax], 2
	mov	eax, DWORD PTR -44[ebp]
	add	eax, 12
	mov	eax, DWORD PTR [eax]
	sub	esp, 12
	push	eax
	call	inet_addr@PLT
	add	esp, 16
	mov	edx, DWORD PTR me@GOT[ebx]
	mov	DWORD PTR 4[edx], eax
	sub	esp, 12
	push	12345
	call	htons@PLT
	add	esp, 16
	mov	edx, DWORD PTR me@GOT[ebx]
	mov	WORD PTR 2[edx], ax
	mov	eax, DWORD PTR my_fd@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 4
	push	16
	mov	edx, DWORD PTR me@GOT[ebx]
	push	edx
	push	eax
	call	bind@PLT
	add	esp, 16
	test	eax, eax
	jns	.L156
	sub	esp, 12
	lea	eax, .LC15@GOTOFF[ebx]
	push	eax
	call	perror@PLT
	add	esp, 16
	mov	eax, DWORD PTR map_size@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	edx
	push	eax
	call	munmap@PLT
	add	esp, 16
	call	endwin@PLT
	sub	esp, 12
	push	1
	call	exit@PLT
.L156:
	sub	esp, 4
	push	0
	push	2
	push	2
	call	socket@PLT
	add	esp, 16
	mov	edx, DWORD PTR other_fd@GOT[ebx]
	mov	DWORD PTR [edx], eax
	mov	eax, DWORD PTR other_fd@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	test	eax, eax
	jns	.L157
	sub	esp, 12
	lea	eax, .LC14@GOTOFF[ebx]
	push	eax
	call	perror@PLT
	add	esp, 16
	mov	eax, DWORD PTR map_size@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	edx
	push	eax
	call	munmap@PLT
	add	esp, 16
	call	endwin@PLT
	sub	esp, 12
	push	1
	call	exit@PLT
.L157:
	mov	eax, DWORD PTR other@GOT[ebx]
	mov	WORD PTR [eax], 2
	mov	eax, DWORD PTR -44[ebp]
	add	eax, 16
	mov	eax, DWORD PTR [eax]
	sub	esp, 12
	push	eax
	call	inet_addr@PLT
	add	esp, 16
	mov	edx, DWORD PTR other@GOT[ebx]
	mov	DWORD PTR 4[edx], eax
	sub	esp, 12
	push	12345
	call	htons@PLT
	add	esp, 16
	mov	edx, DWORD PTR other@GOT[ebx]
	mov	WORD PTR 2[edx], ax
	push	0
	lea	eax, init_bikes_and_cikl@GOTOFF[ebx]
	push	eax
	push	0
	lea	eax, -40[ebp]
	push	eax
	call	pthread_create@PLT
	add	esp, 16
	mov	eax, DWORD PTR -40[ebp]
	sub	esp, 8
	push	0
	push	eax
	call	pthread_join@PLT
	add	esp, 16
	mov	eax, DWORD PTR map_size@GOT[ebx]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR ptr@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	edx
	push	eax
	call	munmap@PLT
	add	esp, 16
	mov	eax, DWORD PTR fb@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 12
	push	eax
	call	close@PLT
	add	esp, 16
	mov	eax, DWORD PTR f@GOT[ebx]
	mov	eax, DWORD PTR [eax]
	sub	esp, 12
	push	eax
	call	fclose@PLT
	add	esp, 16
	call	endwin@PLT
	mov	eax, 0
	mov	ecx, DWORD PTR -28[ebp]
	xor	ecx, DWORD PTR gs:20
	je	.L159
	call	__stack_chk_fail_local
.L159:
	lea	esp, -12[ebp]
	pop	ecx
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	pop	ebx
	.cfi_restore 3
	pop	esi
	.cfi_restore 6
	pop	ebp
	.cfi_restore 5
	lea	esp, -4[ecx]
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE24:
	.size	main, .-main
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
.LFB25:
	.cfi_startproc
	mov	eax, DWORD PTR [esp]
	ret
	.cfi_endproc
.LFE25:
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB26:
	.cfi_startproc
	mov	ebx, DWORD PTR [esp]
	ret
	.cfi_endproc
.LFE26:
	.hidden	__stack_chk_fail_local
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 4
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 4
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 4
4:
