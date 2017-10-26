%macro YKDispatcher1_run 0
	mov bx, [YKRdyList]		;set up the stack pointer
	mov sp, [bx]		;by restoring it from TCB
	pop word [ssTemp]
	pop ds
	pop si
	pop di
	pop es
	pop ax
	pop bx
	pop cx
	pop dx
	pop bp
	iret
%endmacro

%macro save_context 0
	push bp
	push dx
	push cx
	push bx
	push ax
	push es
	push di
	push si
	push ds
	mov [ssTemp], ss
	push word [ssTemp]
						;move current stack pointer on cTask struct
	mov bx, [oldTask]
	mov [bx], sp
%endmacro

YKDispatcherASM:
	mov [bxTemp], bx 	; This simply saves bx
	pop bx 				;we will pop the ip into bx here
	pushf 				;push the flags
	push cs 			; push cs
	push bx 			;push bx which is holding the ip
	mov bx, [bxTemp] 	;restore bx value 
	cmp word[saveContext], 0
	je YKDispatcher1
	save_context
YKDispatcher1:
	YKDispatcher1_run

YKEnterMutex:
	cli
	ret

YKExitMutex:
	sti
	ret


YKIdleTask:
	push bp
	push ax	
	mov bp, sp
	jmp while1

while1:
	cli
	inc word [YKIdleCount]
	sti
	jmp while1
