    global _start

_debug_start:
    push bp
    mov bp sp

    push 5 ;  5 times loop
    call _test_fn_start

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
    call _test_fn_call

    mov sp bp
    pop bp
    stop

; ==============================
_test_fn_call:
    ; parametros por la pila
    mov bx [bp+4]  

    ; si no esta en la pila
    ; usar variable n
    cmp bx 0
    jnz _test_fn_begin
    load bx n

_test_fn_begin:

    ; --- Prologue ---
    push bp
    mov bp sp
    
    ; Reserva 2 var int
    sub sp 8  

    ; --- Ini loop vars
    xor cx cx ; set 0 to cx

_test_fn_loop:
    cmp bx cx
    jz _test_fn_loop_end
    call _test_int_80 
    inc cx 
    jmp _test_fn_loop

_test_fn_loop_end:
    ; Return value
    mov rx 667

    ; --- Epilogue ---
    mov sp bp
    pop bp
    ret

_test_int_80:
    push bp
    mov bp sp

    syscall 80

    mov sp bp
    pop bp
    ret

