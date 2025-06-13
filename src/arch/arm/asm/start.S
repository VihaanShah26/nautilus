.syntax unified
// might need to add details about cpu and specify that instructions are in thumb mode 
.section .vectors
vector_table:
    .word boot_stack
    .word reset_handler + 1
    .word NMI_Handler
    .word HardFault_Handler
    .word MemManage_Handler
    .zero 44
    .word IRQ0Handler
    .word IRQ1Handler
    .zero 1908


.section .text
    .type reset_handler, %function
    .type nautilus_entry, %function

.align 12
.global reset_handler
reset_handler:
	b .
	ldr r0, =boot_stack 
	mov sp, r0
	ldr r0, =_dataStart
	ldr r1, =_dataEnd
	movs r3, #0
	b LoopCopyDataInit

CopyDataInit:
	ldr r4, [r2, r3]
	str r4, [r0, r3]
	adds r3, r3, #4

LoopCopyDataInit:
	adds r4, r0, r3
	cmp r4, r1
	bcc CopyDataInit

	ldr r2, =_bssStart
	ldr r4, =_bssEnd
	movs r3, #0
	b LoopFillZerobss

FillZerobss:
	str  r3, [r2]
	adds r2, r2, #4

LoopFillZerobss:
	cmp r2, r4
	bcc FillZerobss

// TODO: complete the booting process 


.global nautilus_entry
nautilus_entry: 
	b . 


.section .stack
    boot_stack:
    .align 12
    .space 4096
    boot_stack_end:


