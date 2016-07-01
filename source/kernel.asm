BITS 16
[global _start]
[extern main]
[extern pcbs]

UpdateTimes equ 20

%macro WriteIVT 2
	mov ax,%1
	mov bx,4
	mul bx
	mov si,ax
	mov ax,%2
	mov [cs:si],ax ; offset
	mov ax,cs
	mov [cs:si + 2],ax
%endmacro

WriteIVT 08h, TimerInterupt
	
	;SetTimer
	mov al,34h
	out 43h,al ; write control word
	mov ax,1193182/UpdateTimes	;X times / seconds
	out 40h,al
	mov al,ah
	out 40h,al
	sti

	push 0
	call main

TimerInterupt:
	;stack: flags, cs, ip of program of RunID
	;new cs = cs of kernel
	;new ip = TimerInterupt
	
	mov [cs:TempAX], ax
	mov [cs:TempBX], bx
	mov [cs:TempCX], cx
	mov [cs:TempDX], dx
	;flags/cs/ip
	mov al, byte[cs:RunID]
	mov ah, 28
	mul ah 
	mov bx,ax ;bx = 28 * RunID
	;mov [cs:pcbs + bx + 16], ax  
	pop ax ; ax = ip
	;flags/cs
	mov [cs:pcbs + bx + 24], ax
	pop ax; ax = cs
	mov [cs:pcbs + bx + 6], ax
	pop ax; ax = FLAGS 
	mov [cs:pcbs + bx + 26], ax
	;stack: empty
	mov ax, sp
	mov [cs:pcbs + bx + 14], ax


	;es,ds,di,si,bp,bx,ax,cx,dx,ss

	mov ax, es
	mov [cs:pcbs + bx], ax
	mov ax, ds
	mov [cs:pcbs + bx + 2], ax
	mov ax, di
	mov [cs:pcbs + bx + 8], ax
	mov ax, si
	mov [cs:pcbs + bx + 10], ax
	mov ax, bp
	mov [cs:pcbs + bx + 12], ax
	mov ax, ss
	mov [cs:pcbs + bx + 4], ax 
	;bx,ax,cx,dx
	mov ax, [cs:TempAX]
	mov [cs:pcbs + bx + 16], ax
	mov ax, [cs:TempBX]
	mov [cs:pcbs + bx + 18], ax
	mov ax, [cs:TempCX]
	mov [cs:pcbs + bx + 20], ax
	mov ax, [cs:TempDX]
	mov [cs:pcbs + bx + 22], ax

	mov al, byte[cs:RunID]
	inc al
	cmp al, 5
	jb RUNIDNOTOVER
	mov al, 0
	RUNIDNOTOVER:
	mov byte[cs:RunID], al
;ReLoad		
	mov al, byte[cs:RunID]
	mov ah, 28
	mul ah
	mov bx,ax 
	
	mov ax, [cs:pcbs + bx]
	mov es, ax
	mov ax, [cs:pcbs + bx + 2]
	mov ds, ax
	mov ax, [cs:pcbs + bx + 4]
	mov ss, ax
	mov ax, [cs:pcbs + bx + 8]
	mov di, ax
	mov ax, [cs:pcbs + bx + 10]
	mov si, ax
	mov ax, [cs:pcbs + bx + 12]
	mov bp, ax
	mov ax, [cs:pcbs + bx + 14]
	mov sp, ax
	mov ax, [cs:pcbs + bx + 26]
	push ax
	mov ax, [cs:pcbs + bx + 6]
	push ax
	mov ax, [cs:pcbs + bx + 24]
	push ax
	;new stack:flags,cs,ip
	push word[cs:pcbs + bx + 16]
	pop ax
	push word[cs:pcbs + bx + 20]
	pop cx
	push word[cs:pcbs + bx + 22]
	pop dx

	push ax
	mov ax, [cs:pcbs + bx + 18]
	mov bx, ax
	pop ax

	push ax
	mov al,20h
	out 20h,al
	out 0A0h,al
	pop ax
	
	iret

RunID db 0
TempAX dw 0
TempBX dw 0
TempCX dw 0
TempDX dw 0
jmp $
