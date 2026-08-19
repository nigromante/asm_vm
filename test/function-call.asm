
    global _start

_start:
    MOV DI 123 
    call _test_fn_loop_start

    mov cx rx

    syscall 80

    end

_test_fn_loop_start:
    ; --- Prologue ---
    push bp
    mov bp sp
    inc sp

    mov cx di
    syscall 80

    mov rx 22

    dec sp
    ; Epilogue
    mov sp bp
    pop bp
    ret


