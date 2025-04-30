.section .isr_vector, "a", %progbits
.type _vector_table, %object
.global _vector_table

_vector_table:
    .word _stack_top
    .word Reset_Handler

.section .text.Reset_Handler, "ax", %progbits
.global Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    // Zero .bss
    ldr r0, =_bss_start
    ldr r1, =_bss_end
    movs r2, #0
zero_bss:
    cmp r0, r1
    strlt r2, [r0], #4
    addlt r0, r0, #4
    blt zero_bss

    // Copy .data
    ldr r0, =_data_load_start
    ldr r1, =_data_start
    ldr r2, =_data_end
copy_data:
    cmp r1, r2
    ldrlt r3, [r0], #4
    strlt r3, [r1], #4
    addlt r0, r0, #4
    addlt r1, r1, #4
    blt copy_data

    bl main
hang: b hang

