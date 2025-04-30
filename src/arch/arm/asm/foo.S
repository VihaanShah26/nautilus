
# this is code from the youtube tutorial 
.section .vectors
vector_table:
    .word 0xABC0
    .word reset_handler
    .zero 400

.section .text
    .align 1
    .type reset_handler, %function
reset_handler:
    mov r1, #0x7
    mov r2, #0x3
    add r3, r1, r2
    bl .

