#include<nautilus/arch.h>
#include<nautilus/of/numa.h>
#include<nautilus/of/mem.h>
#include<nautilus/atomic.h>
#include<nautilus/interrupt.h>

#include<arch/arm/sys_reg.h>
#include<arch/arm/unimpl.h>

// Double checking some macros
#ifndef NAUT_CONFIG_ARCH_ARM
#error "NAUT_CONFIG_ARCH_ARM is not defined yet arm objects are being compiled!"
#endif

void arch_enable_ints(void) {
#ifdef NAUT_CONFIG_BEANDIP
  atomic_lock_release(in_time_hook);
//#else
  //__asm__ __volatile__ ("cpsie i");
#endif
}
void arch_disable_ints(void) {
#ifdef NAUT_CONFIG_BEANDIP
  while(atomic_lock_test_and_set(in_time_hook,1)) {}
//#else
//  __asm__ __volatile__ ("cpsid i");
#endif
}
int arch_ints_enabled(void) {
uint_t prim = 0;

    // MRS (Move from Special register) → read PRIMASK into 'prim'
     //__asm__ __volatile__ (
       // "mrs %0, primask\n"
        //: "=r" (prim)    // output: prim ← PRIMASK
        //:                // no inputs
        //:                // no clobbers (FLAGS are untouched)
    //);

    // PRIMASK == 0 ⇒ interrupts enabled.  Return 1 in that case.
    return (prim == 0);
}

nk_irq_t arch_xcall_irq(void) {
	return NK_NULL_IRQ; 
}

void arm_print_regs_extended(struct nk_regs *r) {
#define PRINT_REG(REG) printk("\t"#REG" = 0x%x = %u\n", r->REG, r->REG)
 }

void arch_print_regs(struct nk_regs *r) {
#define PRINT_REG(REG) printk("\t"#REG" = 0x%x = %u\n", r->REG, r->REG)
 }

void *arch_read_sp(void) {
  void *stack_ptr;
  __asm__ __volatile__ (
      "mov %0, sp"
      : "=r" (stack_ptr)
      :
      );
  return stack_ptr;
}

int arch_little_endian(void) {
  // Technically only refers to data accesses not instruction but that's good enough
	printk("TO BE IMPLEMENTED");
	return 0;
}

void arch_detect_mem_map(mmap_info_t *mm_info, mem_map_entry_t *memory_map,
                         unsigned long mbd) {
  //TODO
  return;
}
void arch_reserve_boot_regions(unsigned long mbd) {
  // TODO
  return;
}

void arch_relax(void) {
 // __asm__ __volatile__ ("yield");
}
