#include<nautilus/naut_types.h>
#include<nautilus/printk.h>


#define LOAD_SYS_REG(name, raw) \
  __asm__ __volatile__ (\
      "mrs %0,"#name : "=r" (raw) ::)

#define STORE_SYS_REG(name, raw) \
  __asm__ __volatile__ (\
      "msr "#name", %0" :: "r" (raw) :)

#define ASSERT_SYS_REG_SIZE(type, size) \
      _Static_assert(sizeof(type) == size, "System Register struct: " #type " is not exactly " #size " bytes wide!");


typedef union apsr {
  uint32_t raw;
  struct {
    uint_t rsvd1 : 16; 
    uint_t ge : 4;
    uint_t rsvd2 : 7;
    uint_t Q : 1;
    uint_t V : 1;
    uint_t C : 1;
    uint_t Z : 1;
    uint_t N : 1;
  } fields __attribute__((packed));
} apsr_t;
ASSERT_SYS_REG_SIZE(apsr_t, 4);

typedef union ipsr {
  uint32_t raw;
  struct {
    uint_t exception_number : 9; 
    uint_t rsvd : 23;
  } fields __attribute__((packed));
} ipsr_t;

ASSERT_SYS_REG_SIZE(ipsr_t, 4);


typedef union epsr {
  uint32_t raw;
  struct {
    uint_t rsvd : 10; 
    uint_t it_or_ici : 6;
    uint_t rsvd2 : 8; 
    uint_t T : 1; 
    uint_t it_or_ici2 : 2;
    uint_t rsvd3 : 5; 
  } fields __attribute__((packed));
} epsr_t;
ASSERT_SYS_REG_SIZE(epsr_t, 4);

typedef struct xpsr {
    apsr_t apsr_reg; 
    ipsr_t ipsr_reg; 
    epsr_t epsr_reg; 
} xpsr_t;
ASSERT_SYS_REG_SIZE(xpsr_t, 12);


typedef union primask {
  uint32_t raw;
  struct {
    uint_t pm : 1; 
    uint_t res0 : 31;
  } fields __attribute__((packed));
} primask_t;
ASSERT_SYS_REG_SIZE(primask_t, 4);

typedef union faultmask {
  uint32_t raw;
  struct {
    uint_t fm : 1; 
    uint_t res0 : 31;
  } fields __attribute__((packed));
} faultmask_t;
ASSERT_SYS_REG_SIZE(faultmask_t, 4);

typedef union basepri {
  uint32_t raw;
  struct {
    uint_t basepri_field : 8; 
    uint_t res0 : 24;
  } fields __attribute__((packed));
} basepri_t;
ASSERT_SYS_REG_SIZE(basepri_t, 4);


typedef union control {
  uint32_t raw;
  struct {
    uint_t nprev : 1; 
    uint_t spsel : 1;
    uint_t fpca : 1;
    uint_t sfpa : 1; 
    uint_t res0 : 28; 
  } fields __attribute__((packed));
} control_t;
ASSERT_SYS_REG_SIZE(control_t, 4);


typedef union psplim {
  uint32_t raw;
  struct {
    uint_t res0 : 3; 
    uint_t limit : 29;
  } fields __attribute__((packed));
} psplim_t;
ASSERT_SYS_REG_SIZE(psplim_t, 4);


typedef union nsplim {
  uint32_t raw;
  struct {
    uint_t res0 : 3; 
    uint_t limit : 29;
  } fields __attribute__((packed));
} nsplim_t;
ASSERT_SYS_REG_SIZE(nsplim_t, 4);
