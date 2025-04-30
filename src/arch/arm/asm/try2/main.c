void main(void) {
    volatile unsigned int *led = (unsigned int *)0x40025038; // dummy address
    while (1) {
        *led = 0xFF;  // pretend to turn on LED
    }
}

