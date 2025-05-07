.section .vectors
vector_table:
    .word boot_stack
    .word nautilus_entry
    .zero 400

.section .text
    .align 1
    .type reset_handler, %function
reset_handler:
    mov r1, #0x7
    mov r2, #0x3
    add r3, r1, r2
    bl .
.section .stack
    boot_stack:
    .space 4096
    boot_stack_end:

.global nautilus_entry

nautilus_entry: 
	mov r1, #0xABCD
	bl . 
