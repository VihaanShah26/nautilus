#ifdef __CPU_H__
#define pause()

#define PAUSE_WHILE(x)                                                         \
  while ((x)) {                                                                \
    pause();                                                                   \
  }
#define mbarrier() __sync_synchronize()
#define BARRIER_WHILE(x) \
	while ((x)) { \
		mbarrier(); \
	}
static inline void halt(void) {
#ifndef NAUT_CONFIG_BEANDIP
  asm volatile ("wfi");
#endif
}

static inline void invlpg(unsigned int addr) {}

static inline void wbinvd(void) {}

static inline void clflush(void *ptr) {}

static inline void clflush_unaligned(void *ptr, int size) {}

/**
 * Flush all non-global entries in the calling CPU's TLB.
 *
 * Flushing non-global entries is the common-case since user-space
 * does not use global pages (i.e., pages mapped at the same virtual
 * address in *all* processes).
 *
 */
static inline void tlb_flush(void) { /* TODO(arm) */ }

static inline void io_delay(void) {
  /* TODO(arm) */
  pause();
}

static void udelay(uint_t n) { 
	while (n--) {
		io_delay(); 
	}
}

#endif 
