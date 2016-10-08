.386
PUBLIC @aF@8
.model flat
.code
 
@aF@8 proc
 
    mov edi, ecx
    mov esi, edx
    mov al, 0 ; используем регистр на 1 байт для чаров
    mov [esi], al
    mov ebx, 1   
    mov ecx, 0
    begin: 
        mov al,[edi+ecx]
        cmp al,0
        je end_
        cmp al,'\'
        je change
        cmp al,':'
        je change
        cmp al,'.'
        je change
        add ecx, 1
        jmp begin
    change:
        add ecx, 1
        mov [esi+ebx*4], ecx
        add ebx, 1
        jmp begin
    end_:
    mov eax, ebx;
    ret
@aF@8 endp
end