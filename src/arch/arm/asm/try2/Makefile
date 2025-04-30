TARGET = main
OBJS = boot.o main.o

CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
AS = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -mcpu=cortex-m3 -mthumb -nostdlib -Wall -Wextra -ffreestanding
LDFLAGS = -T linker.ld

all: $(TARGET).bin

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

run: $(TARGET).bin
	qemu-system-arm -M lm3s6965evb -nographic -kernel $(TARGET).bin

clean:
	rm -f *.o *.elf *.bin

