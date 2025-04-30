    .syntax unified
    .cpu cortex-m3          @ or cortex-m0/cortex-m4 etc.
    .thumb

    .section .isr_vector, "a", %progbits
    .align  2
_vector_table:
    .word   _estack         @ Initial stack pointer
    .word   Reset_Handler   @ Reset handler
    @ (you can put other vectors here, but for bare minimum you only need these two)

    .section .text
    .global Reset_Handler
    .type   Reset_Handler, %function
Reset_Handler:
    /* At this point:
       - MSP is already loaded from vector_table
       - CPU is in Thumb mode
       - All interrupts disabled
    */
    b       .               @ Infinite loop: we’ve “booted”!
