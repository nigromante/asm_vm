
    global _start

_start:
    MOV DI 123 
    call _test_fn_loop_start
    end

_test_fn_loop_start:
    ; --- Prologue ---
    push bp
    mov bp sp

    mov cx di
    syscall 80

    mov rx 22

    ; Epilogue
    mov sp bp
    pop bp
    ret


