.386
PUBLIC _toHex@8
.model flat

.data
	n dd ?
	a dd ?
.code

; метод тетрад

_toHex@8 proc
	push ebp;
    mov ebp, esp; 
    mov eax, [ebp+8] ; n 
    mov n, eax;
    mov eax, [ebp+12] ; a 
    mov a, eax;
	mov esi, a

	mov ecx, 8
	mov dl, 28
	begin:
		push ecx
		mov eax, n
		mov cl, dl
		shr eax, cl
		and eax, 15
		cmp eax, 9
		jg gr
		add al, '0'
		mov [esi], al
		jmp cont
		gr:
		sub al, 10
		add al, 'A'
		mov [esi], al
		cont:
		add esi, 1
		sub dl, 4
		pop ecx
		loop begin

	mov al, 0
	mov [esi], al

	pop ebp
	ret 8
_toHex@8 endp

end
