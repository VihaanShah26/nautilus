
ifdef NAUT_CONFIG_ARCH_X86
GCC_CROSS_COMPILE ?= 
endif

ifdef NAUT_CONFIG_ARCH_ARM64
GCC_CROSS_COMPILE ?= aarch64-linux-gnu-
LDFLAGS += -m aarch64elf
endif

ifdef NAUT_CONFIG_ARCH_RISCV
GCC_CROSS_COMPILE ?= riscv64-linux-gnu-
CFLAGS += -finline-atomics
endif

ifdef NAUT_CONFIG_ARCH_ARM
GCC_CROSS_COMPILE ?= arm-none-eabi-
CFLAGS += -B/usr/bin/arm-none-eabi-
AFLAGS += -B/usr/bin/arm-none-eabi-
endif

CC = $(GCC_CROSS_COMPILE)gcc
LD = $(GCC_CROSS_COMPILE)ld
AS = $(GCC_CROSS_COMPILE)as
CXX = $(GCC_CROSS_COMPILE)g++
CPP = $(GCC_CROSS_COMPILE)cpp
AR = $(GCC_CROSS_COMPILE)ar

OBJCOPY = $(GCC_CROSS_COMPILE)objcopy
OBJDUMP = $(GCC_CROSS_COMPILE)objdump

ifdef NAUT_CONFIG_COMPILE_FOR_SPEED
COMMON_FLAGS += -O$(NAUT_CONFIG_COMPILER_OPT_LEVEL)  -fno-delete-null-pointer-checks
endif 

ifdef NAUT_CONFIG_COMPILE_FOR_SIZE
COMMON_FLAGS += -Os
endif 
GCCVERSIONGTE6 := $(shell expr `$(CC) -dumpversion | cut -f1 -d.` \>= 6)
ifeq "$(GCCVERSIONGTE6)" "1"
  COMMON_FLAGS += -no-pie -fno-pic -fno-PIC -fno-PIE
endif

