#ifndef _ASM_ARM_BITOPS_H
#define _ASM_ARM_BITOPS_H

/*
 * Copyright 1992, Linus Torvalds.
 *
 * Note: inlines with more than a single statement should be marked
 * __always_inline to avoid problems with older gcc's inlining heuristics.
 */



#ifndef __BITOPS_H__
#error only <lib/bitops.h> can be included directly
#endif

#include <nautilus/atomic.h> 
#include <nautilus/intrinsics.h> 

/**
 * __clz - count leading zeros in word
 */
static inline unsigned long __clz(unsigned long word)
{
  return (unsigned long)__builtin_clz(word);
}

static inline int test_bit(unsigned int nr, const volatile unsigned int *addr){
	return 1U & (addr[BIT_WORD((uint32_t)nr)] >> ((uint32_t)nr % BITS_PER_INT)); 
}

static inline int test_and_set_bit(int nr, volatile unsigned int * addr)
{
    addr += BIT_WORD((uint32_t)nr);
    unsigned int bit = 1U<<((uint32_t)nr % BITS_PER_INT);

    unsigned int old;
    old = atomic_or(*(unsigned int*)addr, bit);
    return old & bit;
}

/**
 * test_and_clear_bit - Clear a bit and return its old value
 * @nr: Bit to clear
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */
static inline int test_and_clear_bit(int nr, volatile unsigned int * addr)
{
  addr += BIT_WORD((uint32_t)nr);
  unsigned int bit = 1U<<((uint32_t)nr % BITS_PER_INT);
  
  unsigned int old; 
  old = atomic_and(*(unsigned int*)addr, ~bit);
  return (old & bit);
}


/**
 * __ffs - find first set bit in word
 * @word: The word to search
 *
 * Undefined if no bit exists, so code should check against 0 first.
 */
static inline unsigned long __ffs(unsigned long word)
{
    int num = 0;

    if ((word & 0xffff) == 0) {
    	num += 16;
    	word >>= 16;
    }
    if ((word & 0xff) == 0) {
    	num += 8;
    	word >>= 8;
    }
    if ((word & 0xf) == 0) {
    	num += 4;
    	word >>= 4;
    }
    if ((word & 0x3) == 0) {
    	num += 2;
    	word >>= 2;
    }
    if ((word & 0x1) == 0) {
    	num += 1;
    }
    return num;
}

/**
 * ffz - find first zero bit in word
 * @word: The word to search
 *
 * Undefined if no zero exists, so code should check against ~0UL first.
 */
#define ffz(x) __ffs(~(x))

/**
 * __fls - find last (most-significant) set bit in a long word
 * @word: the word to search
 *
 * Undefined if no set bit exists, so code should check against 0 first.
 */
static inline unsigned long __fls(unsigned long word)
{
	int num = BITS_PER_LONG - 1;

	if (!(word & (~0ul << (BITS_PER_LONG-16)))) {
		num -= 16;
		word <<= 16;
	}
	if (!(word & (~0ul << (BITS_PER_LONG-8)))) {
		num -= 8;
		word <<= 8;
	}
	if (!(word & (~0ul << (BITS_PER_LONG-4)))) {
		num -= 4;
		word <<= 4;
	}
	if (!(word & (~0ul << (BITS_PER_LONG-2)))) {
		num -= 2;
		word <<= 2;
	}
	if (!(word & (~0ul << (BITS_PER_LONG-1))))
		num -= 1;
	return num;
}

/**
 * ffs - find first set bit in word
 * @x: the word to search
 *
 * This is defined the same way as the libc and compiler builtin ffs
 * routines, therefore differs in spirit from the other bitops.
 *
 * ffs(value) returns 0 if value is 0 or the position of the first
 * set bit if value is nonzero. The first (least significant) bit
 * is at position 1.
 */
static inline int ffs(int x)
{
    return __builtin_ffs(x);
}

/**
 * fls - find last (most-significant) bit set
 * @x: the word to search
 *
 * This is defined the same way as ffs.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */
static inline int fls(unsigned int x)
{
	int r = 32;

	if (!x)
		return 0;
	if (!(x & 0xffff0000u)) {
		x <<= 16;
		r -= 16;
	}
	if (!(x & 0xff000000u)) {
		x <<= 8;
		r -= 8;
	}
	if (!(x & 0xf0000000u)) {
		x <<= 4;
		r -= 4;
	}
	if (!(x & 0xc0000000u)) {
		x <<= 2;
		r -= 2;
	}
	if (!(x & 0x80000000u)) {
		x <<= 1;
		r -= 1;
	}
	return r;
}

#endif 
