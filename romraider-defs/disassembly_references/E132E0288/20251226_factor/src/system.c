/*
 * system.c - System Utilities and Initialization
 * Startup, EEPROM, lookup tables, math utilities
 * ~100 functions
 */

#include "../include/types.h"
#include "../include/runtime_vars.h"

void system_init(void) { }
void eeprom_read(void) { }
void eeprom_write(void) { }
void copyCAL2RAM(void) { }
void copyCOD2RAM(void) { }
void lookup_2D_uint16_interpolated(int size, ushort x, uint16_t *x_axis, uint16_t *table) { }
void libc_memcpy(void *dest, void *src, size_t n) { }
void libc_memset(void *s, int c, size_t n) { }
void busy_wait_50k(void) { }
/* + ~90 more system functions */
