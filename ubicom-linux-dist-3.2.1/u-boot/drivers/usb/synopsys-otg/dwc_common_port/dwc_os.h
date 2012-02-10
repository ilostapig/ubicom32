/*
 * (C) Copyright 2010, Ubicom, Inc.
 *
 * This file is part of the Ubicom32 Linux Kernel Port.
 *
 * The Ubicom32 Linux Kernel Port is free software: you can redistribute
 * it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 2 of the
 * License, or (at your option) any later version.
 *
 * The Ubicom32 Linux Kernel Port is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 * the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Ubicom32 Linux Kernel Port.  If not,
 * see <http://www.gnu.org/licenses/>.
 *
 */

/* =========================================================================
 * $File: //dwh/usb_iip/dev/software/dwc_common_port/dwc_os.h $
 * $Revision: #2 $
 * $Date: 2009/04/02 $
 * $Change: 1224130 $
 *
 * Synopsys Portability Library Software and documentation
 * (hereinafter, "Software") is an Unsupported proprietary work of
 * Synopsys, Inc. unless otherwise expressly agreed to in writing
 * between Synopsys and you.
 *
 * The Software IS NOT an item of Licensed Software or Licensed Product
 * under any End User Software License Agreement or Agreement for
 * Licensed Product with Synopsys or any supplement thereto. You are
 * permitted to use and redistribute this Software in source and binary
 * forms, with or without modification, provided that redistributions
 * of source code must retain this notice. You may not view, use,
 * disclose, copy or distribute this file or any information contained
 * herein except pursuant to this license grant from Synopsys. If you
 * do not agree with this notice, including the disclaimer below, then
 * you are not authorized to use the Software.
 *
 * THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS"
 * BASIS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE HEREBY DISCLAIMED. IN NO EVENT SHALL
 * SYNOPSYS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 * ========================================================================= */
#ifndef _DWC_OS_H_
#define _DWC_OS_H_

/** @file
 *
 * DWC portability library, low level os-wrapper functions
 *
 */

/* These basic types need to be defined by some OS header file or custom header
 * file for your specific target architecture.
 *
 * uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t, uint64_t, int64_t
 *
 * Any custom or alternate header file must be added and enabled here.
 */
#include <common.h>
#include <linux/types.h>
#include "dwc_ubicom.h"

/** @name Primitive Types and Values */

/** We define a boolean type for consistency.  Can be either YES or NO */
typedef uint8_t dwc_bool_t;
#define YES  1
#define NO   0

/** @todo make them positive and return the negative error code */
/** @name Error Codes */
#define DWC_E_INVALID         1001
#define DWC_E_NO_MEMORY       1002
#define DWC_E_NO_DEVICE       1003
#define DWC_E_NOT_SUPPORTED   1004
#define DWC_E_TIMEOUT         1005
#define DWC_E_BUSY            1006
#define DWC_E_AGAIN           1007
#define DWC_E_RESTART         1008
#define DWC_E_ABORT           1009
#define DWC_E_SHUTDOWN        1010
#define DWC_E_NO_DATA         1011
#define DWC_E_DISCONNECT      2000
#define DWC_E_UNKNOWN         3000
#define DWC_E_NO_STREAM_RES   4001
#define DWC_E_COMMUNICATION   4002
#define DWC_E_OVERFLOW        4003
#define DWC_E_PROTOCOL        4004
#define DWC_E_IN_PROGRESS     4005
#define DWC_E_PIPE            4006
#define DWC_E_IO              4007
#define DWC_E_NO_SPACE        4008

/** @name Tracing/Logging Functions
 *
 * These function provide the capability to add tracing, debugging, and error
 * messages, as well exceptions as assertions.  The WUDEV uses these
 * extensively.  These could be logged to the main console, the serial port, an
 * internal buffer, etc.  These functions could also be no-op if they are too
 * expensive on your system.  By default undefining the DEBUG macro already
 * no-ops some of these functions. */

/** Returns "IRQ" if DWC_IN_IRQ is true. */
static inline char *dwc_irq(void) {
        return "";
}

/**
 * A vprintf() clone.  Just call vprintf if you've got it.
 */
extern void DWC_VPRINTF(char *format, va_list args);
#define dwc_vprintf DWC_VPRINTF

/**
 * printf() clone.  Just call printf if you've go it.
 */
extern void DWC_PRINTF(char *format, ...)
/* This provides compiler level static checking of the parameters if you're
 * using GCC. */
#ifdef __GNUC__
	__attribute__ ((format(printf, 1, 2)));
#else
  ;
#endif
#define dwc_printf DWC_PRINTF

/**
 * sprintf() clone.  Just call sprintf if you've got it.
 */
extern int DWC_SPRINTF(char *string, char *format, ...)
#ifdef __GNUC__
     __attribute__ ((format(printf, 2, 3)));
#else
     ;
#endif
#define dwc_sprintf DWC_SPRINTF

/**
 * Prints a WARNING message.  On systems that don't differentiate between
 * warnings and regular log messages, just print it.  Indicates that something
 * may be wrong with the driver.  Works like printf().
 *
 * Use the DWC_WARN macro to call this function.
 */
extern void __DWC_WARN(char *format, ...)
#ifdef __GNUC__
     __attribute__ ((format(printf, 1, 2)));
#else
     ;
#endif

/**
 * Prints an error message.  On systems that don't differentiate between errors
 * and regular log messages, just print it.  Indicates that something went wrong
 * with the driver, but it can be recovered from.  Works like printf().
 *
 * Use the DWC_ERROR macro to call this function.
 */
extern void __DWC_ERROR(char *format, ...)
#ifdef __GNUC__
     __attribute__ ((format(printf, 1, 2)));
#else
     ;
#endif

/**
 * Prints an exception error message and takes some user-defined action such as
 * print out a backtrace or trigger a breakpoint.  Indicates that something went
 * abnormally wrong with the driver such as programmer error, or other
 * exceptional condition.  It should not be ignored so even on systems without
 * printing capability, some action should be taken to notify the developer of
 * it.  Works like printf().
 */
extern void DWC_EXCEPTION(char *format, ...)
#ifdef __GNUC__
     __attribute__ ((format(printf, 1, 2)));
#else
     ;
#endif
#define dwc_exception DWC_EXCEPTION

#ifdef CONFIG_DWC_DEBUG
/**
 * Prints out a debug message.  Used for logging/trace messages.
 *
 * Use the DWC_DEBUG macro to call this function
 */
extern void __DWC_DEBUG(char *format, ...)
#ifdef __GNUC__
     __attribute__ ((format(printf, 1, 2)));
#else
     ;
#endif
#else
#define __DWC_DEBUG(...)
#endif

/**
 * Prints out a Debug message.
 */
#define DWC_DEBUG(_format, _args...) __DWC_DEBUG("DEBUG:%s:%s: " _format "\n", __func__, dwc_irq(), ## _args)
#define dwc_debug DWC_DEBUG
/**
 * Prints out an informative message.
 */
#define DWC_INFO(_format, _args...) DWC_PRINTF("INFO:%s: " _format "\n", dwc_irq(), ## _args)
#define dwc_info DWC_INFO
/**
 * Prints out a warning message.
 */
#define DWC_WARN(_format, _args...) __DWC_WARN("WARN:%s:%s:%d: " _format "\n", dwc_irq(), __func__, __LINE__, ## _args)
#define dwc_warn DWC_WARN
/**
 * Prints out an error message.
 */
#define DWC_ERROR(_format, _args...) __DWC_ERROR("ERROR:%s:%s:%d: " _format "\n", dwc_irq(), __func__, __LINE__, ## _args)
#define dwc_error DWC_ERROR

#define DWC_PROTO_ERROR(_format, _args...) __DWC_WARN("ERROR:%s:%s:%d: " _format "\n", dwc_irq(), __func__, __LINE__, ## _args)
#define dwc_proto_error DWC_PROTO_ERROR

#ifdef CONFIG_DWC_DEBUG
/** Prints out a exception error message if the _expr expression fails.  Disabled
 * if DEBUG is not enabled. */
#define DWC_ASSERT(_expr, _format, _args...) if (!(_expr)) { DWC_EXCEPTION("%s:%s:%d: " _format "\n", dwc_irq(), __FILE__, __LINE__, ## _args); }
#else
#define DWC_ASSERT(_x...)
#endif
#define dwc_assert DWC_ASSERT

/** @name Byter Ordering
 * The following functions are for conversions between processor's byte ordering
 * and specific ordering you want.
 */

#undef __LITTLE_ENDIAN

/** Converts 32 bit data in CPU byte ordering to little endian. */
extern uint32_t DWC_CPU_TO_LE32(void *p);
#define dwc_cpu_to_le32 DWC_CPU_TO_LE32
/** Converts 32 bit data in CPU byte orderint to big endian. */
extern uint32_t DWC_CPU_TO_BE32(void *p);
#define dwc_cpu_to_be32 DWC_CPU_TO_BE32

/** Converts 32 bit little endian data to CPU byte ordering. */
extern uint32_t DWC_LE32_TO_CPU(void *p);
#define dwc_le32_to_cpu DWC_LE32_TO_CPU
/** Converts 32 bit big endian data to CPU byte ordering. */
extern uint32_t DWC_BE32_TO_CPU(void *p);
#define dwc_be32_to_cpu DWC_BE32_TO_CPU

/** Converts 16 bit data in CPU byte ordering to little endian. */
extern uint16_t DWC_CPU_TO_LE16(void *p);
#define dwc_cpu_to_le16 DWC_CPU_TO_LE16
/** Converts 16 bit data in CPU byte orderint to big endian. */
extern uint16_t DWC_CPU_TO_BE16(void *p);
#define dwc_cpu_to_be16 DWC_CPU_TO_BE16

/** Converts 16 bit little endian data to CPU byte ordering. */
extern uint16_t DWC_LE16_TO_CPU(void *p);
#define dwc_le16_to_cpu DWC_LE16_TO_CPU
/** Converts 16 bit bi endian data to CPU byte ordering. */
extern uint16_t DWC_BE16_TO_CPU(void *p);
#define dwc_be16_to_cpu DWC_BE16_TO_CPU

/** @name Register Read/Write
 *
 * The following five functions should be implemented to read/write registers of
 * 32-bit and 64-bit sizes.  All modules use this to read/write register values.
 * The reg value is a pointer to the register calculated from the void *base
 * variable passed into the driver when it is started.  */

/** Reads the content of a 32-bit register. */
extern uint32_t DWC_READ_REG32(uint32_t volatile *reg);
#define dwc_read_reg32 DWC_READ_REG32
/** Reads the content of a 64-bit register. */
extern uint64_t DWC_READ_REG64(uint64_t volatile *reg);
#define dwc_read_reg64 DWC_READ_REG64
/** Writes to a 32-bit register. */
extern void DWC_WRITE_REG32(uint32_t volatile *reg, uint32_t value);
#define dwc_write_reg32 DWC_WRITE_REG32
/** Writes to a 64-bit register. */
extern void DWC_WRITE_REG64(uint64_t volatile *reg, uint64_t value);
#define dwc_write_reg64 DWC_WRITE_REG64
/**  
 * Modify bit values in a register.  Using the
 * algorithm: (reg_contents & ~clear_mask) | set_mask.
 */
extern void DWC_MODIFY_REG32(uint32_t volatile *reg, uint32_t clear_mask, uint32_t set_mask);
#define dwc_modify_reg32 DWC_MODIFY_REG32

/** @cond */

/** @name Some convenience MACROS used internally.  Define DEBUG_REGS to log the
 * register writes. */

#ifdef DEBUG_REGS

#define dwc_define_read_write_reg_n(_reg,_container_type) \
static inline uint32_t dwc_read_##_reg##_n(_container_type *container, int num) { \
	return DWC_READ_REG32(&container->regs->_reg[num]); \
} \
static inline void dwc_write_##_reg##_n(_container_type *container, int num, uint32_t data) { \
        DWC_DEBUG("WRITING %8s[%d]: %p: %08x", #_reg, num, &(((uint32_t*)container->regs->_reg)[num]), data); \
	DWC_WRITE_REG32(&(((uint32_t*)container->regs->_reg)[num]), data); \
}

#define dwc_define_read_write_reg(_reg,_container_type) \
static inline uint32_t dwc_read_##_reg(_container_type *container) { \
	return DWC_READ_REG32(&container->regs->_reg); \
} \
static inline void dwc_write_##_reg(_container_type *container, uint32_t data) { \
        DWC_DEBUG("WRITING %11s: %p: %08x", #_reg, &container->regs->_reg, data); \
	DWC_WRITE_REG32(&container->regs->_reg, data); \
}

#else

#define dwc_define_read_write_reg_n(_reg,_container_type) \
static inline uint32_t dwc_read_##_reg##_n(_container_type *container, int num) { \
	return DWC_READ_REG32(&container->regs->_reg[num]); \
} \
static inline void dwc_write_##_reg##_n(_container_type *container, int num, uint32_t data) { \
	DWC_WRITE_REG32(&(((uint32_t*)container->regs->_reg)[num]), data); \
}

#define dwc_define_read_write_reg(_reg,_container_type) \
static inline uint32_t dwc_read_##_reg(_container_type *container) { \
	return DWC_READ_REG32(&container->regs->_reg); \
} \
static inline void dwc_write_##_reg(_container_type *container, uint32_t data) { \
	DWC_WRITE_REG32(&container->regs->_reg, data); \
}

#endif

/** @endcond */


/** @name Memory Allocation
 *
 * These function provide access to memory allocation.  There are only 2 DMA
 * functions and 3 Regular memory functions that need to be implemented.  None
 * of the memory debugging routines need to be implemented.  The allocation
 * routines all ZERO the contents of the memory.
 *
 * Defining DEBUG_MEMORY turns on memory debugging and statistic gathering.
 * This checks for memory leaks, keeping track of alloc/free pairs.  It also
 * keeps track of how much memory the driver is using at any given time. */

#define DWC_PAGE_SIZE 4096
#define DWC_PAGE_OFFSET(addr) (((uint32_t)addr) & 0xfff)
#define DWC_PAGE_ALIGNED(addr) ((((uint32_t)addr) & 0xfff) == 0)

#define DWC_INVALID_DMA_ADDR 0x0

typedef uint32_t dwc_dma_t;

/** @todo these functions will be added in the future */
#if 0
/**
 * Creates a DMA pool from which you can allocate DMA buffers.  Buffers
 * allocated from this pool will be guaranteed to meet the size, alignment, and
 * boundary requirements specified.
 *
 * @param[in] size Specifies the size of the buffers that will be allocated from
 * this pool.
 * @param[in] align Specifies the byte alignment requirements of the buffers
 * allocated from this pool.  Must be a power of 2.
 * @param[in] boundary Specifies the N-byte boundary that buffers allocated from
 * this pool must not cross.
 *
 * @returns A pointer to an internal opaque structure which is not to be
 * accessed outside of these library functions.  Use this handle to specify
 * which pools to allocate/free DMA buffers from and also to destroy the pool,
 * when you are done with it.
 */
extern dwc_pool_t *DWC_DMA_POOL_CREATE(uint32_t size, uint32_t align, uint32_t boundary);
/**
 * Destroy a DMA pool.  All buffers allocated from that pool must be freed first.
 */
extern void DWC_DMA_POOL_DESTROY(dwc_pool_t *pool);
/**
 * Allocate a buffer from the specified DMA pool and zeros its contents.
 */
extern void *DWC_DMA_POOL_ALLOC(dwc_pool_t *pool, uint64_t *dma_addr);
/**
 * Free a previously allocated buffer from the DMA pool.
 */
extern void DWC_DMA_POOL_FREE(dwc_pool_t *pool, void *vaddr, void *daddr);
#endif


/** Allocates a DMA capable buffer and zeroes its contents. */
extern void *__DWC_DMA_ALLOC(uint32_t size, dwc_dma_t *dma_addr);

/** Frees a previously allocated buffer. */
extern void __DWC_DMA_FREE(uint32_t size, void *virt_addr, dwc_dma_t dma_addr);

/** Allocates a block of memory and zeroes its contents. */
extern void *__DWC_ALLOC(uint32_t size);

extern void *__DWC_ALLOC_ATOMIC(uint32_t size);

/** Frees a previously allocated buffer. */
extern void __DWC_FREE(void *addr);

#undef DEBUG_MEMORY
#ifndef DEBUG_MEMORY

#define DWC_ALLOC(_size_) __DWC_ALLOC(_size_)
#define DWC_ALLOC_ATOMIC(_size_) __DWC_ALLOC_ATOMIC(_size_)
#define DWC_FREE(_addr_) __DWC_FREE(_addr_)
#define DWC_DMA_ALLOC(_size_,_dma_) __DWC_DMA_ALLOC(_size_,_dma_)
#define DWC_DMA_FREE(_size_,_virt_,_dma_) __DWC_DMA_FREE(_size_,_virt_,_dma_)

#else

extern void *dwc_alloc_debug(uint32_t size, char const *func, int line);
extern void *dwc_alloc_atomic_debug(uint32_t size, char const *func, int line);
extern void dwc_free_debug(void *addr, char const *func, int line);
extern void *dwc_dma_alloc_debug(uint32_t size, dwc_dma_t *dma_addr, char const *func, int line);
extern void dwc_dma_free_debug(uint32_t size, void *virt_addr, dwc_dma_t dma_addr, char const *func, int line);

extern void dwc_memory_debug_start(void);
extern void dwc_memory_debug_stop(void);
extern void dwc_memory_debug_report(void);

#define DWC_ALLOC(_size_) (dwc_alloc_debug(_size_, __func__, __LINE__))
#define DWC_ALLOC_ATOMIC(_size_) (dwc_alloc_atomic_debug(_size_, __func__, __LINE__))
#define DWC_FREE(_addr_) (dwc_free_debug(_addr_, __func__, __LINE__))
#define DWC_DMA_ALLOC(_size_,_dma_) dwc_dma_alloc_debug(_size_, _dma_, __func__, __LINE__)
#define DWC_DMA_FREE(_size_,_virt_,_dma_) dwc_dma_free_debug(_size_, _virt_, _dma_, __func__, __LINE__)

#endif /* DEBUG_MEMORY */

#define dwc_alloc DWC_ALLOC
#define dwc_alloc_atomic DWC_ALLOC_ATOMIC
#define dwc_free DWC_FREE
#define dwc_dma_alloc DWC_DMA_ALLOC
#define dwc_dma_free DWC_DMA_FREE


/** @name Memory and String Processing */

/** memset() clone */
extern void *DWC_MEMSET(void *dest, uint8_t byte, uint32_t size);
#define dwc_memset DWC_MEMSET
/** memcpy() clone */
extern void *DWC_MEMCPY(void *dest, void const *src, uint32_t size);
#define dwc_memcpy DWC_MEMCPY
/** memmove() clone */
extern void *DWC_MEMMOVE(void *dest, void *src, uint32_t size);
#define dwc_memmove DWC_MEMMOVE
/** memcmp() clone */
extern int DWC_MEMCMP(void *m1, void *m2, uint32_t size);
#define dwc_memcmp DWC_MEMCMP
/** strcmp() clone */
extern int DWC_STRCMP(void *s1, void *s2);
#define dwc_strcmp DWC_STRCMP
/** strncmp() clone */
extern int DWC_STRNCMP(void *s1, void *s2, uint32_t size);
#define dwc_strncmp DWC_STRNCMP
/** strlen() clone, for NULL terminated ASCII strings */
extern int DWC_STRLEN(char const *str);
#define dwc_strlen DWC_STRLEN
/** strcpy() clone, for NULL terminated ASCII strings */
extern char *DWC_STRCPY(char *to, const char *from);
#define dwc_strcpy DWC_STRCPY

/** strdup() clone.  If you wish to use memory allocation debugging, this
 * implementation of strdup should use the DWC_* memory routines instead of
 * calling a predefined strdup.  Otherwise the memory allocated by this routine
 * will not be seen by the debugging routines. */
extern char *DWC_STRDUP(char const *str);
#define dwc_strdup DWC_STRDUP

/** NOT an atoi() clone.  Read the description carefully.  Returns an integer
 * converted from the string str in base 10 unless the string begins with a "0x"
 * in which case it is base 16.  String must be a NULL terminated sequence of
 * ASCII characters and may optionally begin with whitespace, a + or -, and a
 * "0x" prefix if base 16.  The remaining characters must be valid digits for
 * the number and end with a NULL character.  If any invalid characters are
 * encountered or it returns with a negative error code and the results of the
 * conversion are undefined.  On sucess it returns 0.  Overflow conditions are
 * undefined.  An example implementation using atoi() can be referenced from the
 * Linux implementation. */
extern int DWC_ATOI(char *str, int32_t *value);
#define dwc_atoi DWC_ATOI
/** Same as above but for unsigned. */
extern int DWC_ATOUI(char *str, uint32_t *value);
#define dwc_atoui DWC_ATOUI
/** This routine returns a UTF16LE unicode encoded string from a UTF8 string. */
extern int DWC_UTF8_TO_UTF16LE(uint8_t const *utf8string, uint16_t *utf16string, unsigned len);
#define dwc_utf8_to_utf16le DWC_UTF8_TO_UTF16LE

/** @name Spinlocks
 *
 * These locks are used when the work between the lock/unlock is atomic and
 * short.  Interrupts are also disabled during the lock/unlock and thus they are
 * suitable to lock between interrupt/non-interrupt context.  They also lock
 * between processes if you have multiple CPUs or Preemption.  If you don't have
 * multiple CPUS or Preemption, then the you can simply implement the
 * DWC_SPINLOCK and DWC_SPINUNLOCK to disable and enable interrupts.  Because
 * the work between the lock/unlock is atomic, the process context will never
 * change, and so you never have to lock between processes.  */

struct dwc_spinlock;
typedef struct dwc_spinlock dwc_spinlock_t;

/** Returns an initialized lock variable.  This function should allocate and
 * initialize the OS-specific data structure used for locking.  This data
 * structure is to be used for the DWC_LOCK and DWC_UNLOCK functions and should
 * be freed by the DWC_FREE_LOCK when it is no longer used. */
extern dwc_spinlock_t *DWC_SPINLOCK_ALLOC(void);
#define dwc_spinlock_alloc DWC_SPINLOCK_ALLOC

/** Frees an initialized lock variable. */
void DWC_SPINLOCK_FREE(dwc_spinlock_t *lock);
#define dwc_spinlock_free DWC_SPINLOCK_FREE

extern void DWC_SPINLOCK_IRQSAVE(dwc_spinlock_t *lock, uint64_t *flags);
#define dwc_spinlock_irqsave DWC_SPINLOCK_IRQSAVE

extern void DWC_SPINUNLOCK_IRQRESTORE(dwc_spinlock_t *lock, uint64_t flags);
#define dwc_spinunlock_irqrestore DWC_SPINUNLOCK_IRQRESTORE

extern void DWC_SPINLOCK(dwc_spinlock_t *lock);
#define dwc_spinlock DWC_SPINLOCK

extern void DWC_SPINUNLOCK(dwc_spinlock_t *lock);
#define dwc_spinunlock DWC_SPINUNLOCK

/** @name Time */

/** Microsecond delay.
 *
 * @param usecs  Microseconds to delay.
 */
extern void DWC_UDELAY(uint32_t usecs);
#define dwc_udelay DWC_UDELAY

/** Millisecond delay.
 *
 * @param msecs  Milliseconds to delay.
 */
extern void DWC_MDELAY(uint32_t msecs);
#define dwc_mdelay DWC_MDELAY

#endif // _DWC_OS_H_




/** @mainpage DWC Portability and Common Library
 *
 * This is the documentation for the DWC Portability and Common Library.
 *
 * @section intro Introduction
 *
 * The DWC Portability library consists of wrapper calls and data structures to
 * all low-level functions which are typically provided by the OS.  The WUDEV
 * driver uses only these functions.  In order to port the WUDEV driver, only
 * the functions in this library need to be re-implemented, with the same
 * behavior as documented here.
 *
 * The Common library consists of higher level functions, which rely only on
 * calling the functions from the DWC Portability library.  These common
 * routines are shared across modules.  Some of the common libraries need to be
 * used directly by the driver programmer when porting WUDEV.  Such as the
 * parameter and notification libraries.
 *
 * @section low Portability Library OS Wrapper Functions
 *
 * Any function starting with DWC and in all CAPS is a low-level OS-wrapper that
 * needs to be implemented when porting, for example DWC_MUTEX_ALLOC().  All of
 * these functions are included in the dwc_os.h file.
 *
 * There are many functions here covering a wide array of OS services.  Please
 * see dwc_os.h for details, and implementation notes for each function.
 *
 * @section common Common Library Functions
 *
 * Any function starting with dwc and in all lowercase is a common library
 * routine.  These functions have a portable implementation and do not need to
 * be reimplemented when porting.  The common routines can be used by any
 * driver, and some must be used by the end user to control the drivers.  For
 * example, you must use the Parameter common library in order to set the
 * parameters in the WUDEV module.
 *
 * The common libraries consist of the following:
 *
 * - Connection Contexts - Used internally and can be used by end-user.  See dwc_cc.h
 * - Parameters - Used internally and can be used by end-user.  See dwc_params.h
 * - Notifications - Used internally and can be used by end-user.  See dwc_notifier.h
 * - Lists - Used internally and can be used by end-user.  See dwc_list.h
 * - Memory Debugging - Used internally and can be used by end-user.  See dwc_os.h
 * - Modpow - Used internally only.  See dwc_modpow.h
 * - DH - Used internally only.  See dwc_dh.h
 * - Crypto - Used internally only.  See dwc_crypto.h
 *
 *
 * @section prereq Prerequistes For dwc_os.h
 * @subsection types Data Types
 *
 * The dwc_os.h file assumes that several low-level data types are pre defined for the
 * compilation environment.  These data types are:
 *
 * - uint8_t - unsigned 8-bit data type
 * - int8_t - signed 8-bit data type
 * - uint16_t - unsigned 16-bit data type
 * - int16_t - signed 16-bit data type
 * - uint32_t - unsigned 32-bit data type
 * - int32_t - signed 32-bit data type
 * - uint64_t - unsigned 64-bit data type
 * - int64_t - signed 64-bit data type
 *
 * Ensure that these are defined before using dwc_os.h.  The easiest way to do
 * that is to modify the top of the file to include the appropriate header.
 * This is already done for the Linux environment.  If the DWC_LINUX macro is
 * defined, the correct header will be added.  A standard header <stdint.h> is
 * also used for environments where standard C headers are available.
 *
 * @subsection stdarg Variable Arguments
 *
 * Variable arguments are provided by a standard C header <stdarg.h>.  it is
 * available in Both the Linux and ANSI C enviornment.  An equivalent must be
 * provided in your enviornment in order to use dwc_os.h with the debug and
 * tracing message functionality.
 *
 * @subsection thread Threading
 *
 * WUDEV Core must be run on an operating system that provides for multiple
 * threads/processes.  Threading can be implemented in many ways, even in
 * embedded systems without an operating system.  At the bare minimum, the
 * system should be able to start any number of processes at any time to handle
 * special work.  It need not be a pre-emptive system.  Process context can
 * change upon a call to a blocking function.  The hardware interrupt context
 * that calls the module's ISR() function must be differentiable from process
 * context, even if your processes are impemented via a hardware interrupt.
 * Further locking mechanism between process must exist (or be implemented), and
 * process context must have a way to disable interrupts for a period of time to
 * lock them out.  If all of this exists, the functions in dwc_os.h related to
 * threading should be able to be implemented with the defined behavior.
 *
 */ 