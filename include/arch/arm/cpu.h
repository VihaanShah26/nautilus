#ifdef __CPU_H__
#define pause()

#define PAUSE_WHILE(x)                                                         \
  while ((x)) {                                                                \
    pause();                                                                   \
  }
static inline void io_delay(void) {
  /* TODO(arm64) */
  pause();
}
#endif 
