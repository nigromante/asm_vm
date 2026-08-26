    global _start

_debug_start:
    push bp
    mov bp sp

    push 5 ;  5 times loop
    call _test_call

    mov sp bp
    pop bp
    stop

_start:
    push bp
    mov bp sp

    ; define variable  'n'
    num n
    store n 10

    sub sp 4
    call _test_call

    syscall 82
    mov sp bp
    pop bp
    stop

; ==============================
_test_call:
    ; parametros por la pila
    mov bx [bp+4]  

    ; si no esta en la pila
    ; usar variable n
    cmp bx 0
    jnz _test_begin
    load bx n

_test_begin:

    ; --- Prologue ---
    push bp
    mov bp sp
    
    ; Reserva 2 var int
    sub sp 8  

    ; --- Ini loop vars
    xor cx cx ; set 0 to cx

_test_loop:
    cmp bx cx
    jz _test_loop_end
    call _print 
    syscall 82
    inc cx 
    jmp _test_loop

_test_loop_end:
    syscall 82
    ; Return value
    mov rx 667

    ; --- Epilogue ---
    mov sp bp
    pop bp
    ret

_print:
    push bp
    mov bp sp

    syscall 82

    mov sp bp
    pop bp
    ret

