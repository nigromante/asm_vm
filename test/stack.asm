

    global _start

_start:
    mov cx 123
    int 80
    inc cx
    call _prueba

    push dx
    mov cx dx
    int 80
    pop ax
    end

_prueba:
    ;push bp
    ;mov bp sp
    ; sub sp 4
    int 80
    ;mov sp bp
    ;pop bp
    ret

