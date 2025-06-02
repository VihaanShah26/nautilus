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
#else
  __asm__ __volatile__ ("cpsie i");
#endif
}
void arch_disable_ints(void) {
#ifdef NAUT_CONFIG_BEANDIP
  while(atomic_lock_test_and_set(in_time_hook,1)) {}
#else
  __asm__ __volatile__ ("cpsid i");
#endif
}
int arch_ints_enabled(void) {
uint_t prim;

    // MRS (Move from Special register) → read PRIMASK into 'prim'
    __asm__ __volatile__ (
        "mrs %0, primask\n"
        : "=r" (prim)    // output: prim ← PRIMASK
        :                // no inputs
        :                // no clobbers (FLAGS are untouched)
    );

    // PRIMASK == 0 ⇒ interrupts enabled.  Return 1 in that case.
    return (prim == 0);
}

nk_irq_t arch_xcall_irq(void) {
	return NK_NULL_IRQ; 
}

void arch_relax(void) {
  __asm__ __volatile__ ("yield");
}
