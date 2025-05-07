
CC = clang
LD = ld.lld
AS = clang-as
CXX = clang++
CPP = cpp

OBJCOPY = llvm-objcopy
OBJDUMP = llvm-objdump

ifdef NAUT_CONFIG_COMPILE_FOR_SPEED
COMMON_FLAGS += -O$(NAUT_CONFIG_COMPILER_OPT_LEVEL)  # -fno-delete-null-pointer-checks
endif 

ifdef NAUT_CONFIG_COMPILE_FOR_SIZE
COMMON_FLAGS += -Os
endif 

ifdef NAUT_CONFIG_ARCH_X86
COMMON_FLAGS += -mcmodel=large \
		        --target=x86_64
endif

ifdef NAUT_CONFIG_ARCH_RISCV
COMMON_FLAGS += --target=riscv64 \
                -mno-relax
LDFLAGS += -m elf64lriscv
endif

ifdef NAUT_CONFIG_ARCH_ARM64
COMMON_FLAGS += -mcmodel=large \
		        --target=aarch64
LDFLAGS += -m aarch64elf
endif
