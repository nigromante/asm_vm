    global _start

_debug_start:

    ; define variable  'n'
    number n
    store n 3
    call _test_fn_loop_start
    stop

_start:
    ; define variable  'n'
    MOV cx 99
    num n 
    store n 10
    call _test_fn_loop_start
    stop

_test_fn_loop_start:
    push bp
    mov bp sp
    xor cx cx ; set 0 to cx
    load bx n

_test_fn_loop:
    cmp bx cx
    jz _test_fn_loop_end
    call _test_int_80 
    inc cx 
    jmp _test_fn_loop

_test_fn_loop_end:
    mov sp bp
    pop bp
    ret

_test_int_80:
    push bp
    mov bp sp
    int 80
    mov sp bp
    pop bp
    ret

