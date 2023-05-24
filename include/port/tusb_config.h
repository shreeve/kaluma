/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

// #include "pico/stdio_usb.h" // TODO: this pulls in stdio stuff

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// Board Specific Configuration
//--------------------------------------------------------------------+

// change to 1 if using pico-pio-usb as host controller for raspberry rp2040
#define CFG_TUH_RPI_PIO_USB   1

//--------------------------------------------------------------------
// COMMON CONFIGURATION
//--------------------------------------------------------------------

// defined by compiler flags for flexibility
#ifndef CFG_TUSB_MCU
#error CFG_TUSB_MCU must be defined
#endif

#ifndef CFG_TUSB_OS
#define CFG_TUSB_OS           OPT_OS_PICO
#endif

#ifndef CFG_TUSB_DEBUG
#define CFG_TUSB_DEBUG        1
#endif

// Enable Device and Host stack
#define CFG_TUD_ENABLED       1
#define CFG_TUH_ENABLED       1

/* USB DMA on some MCUs can only access a specific SRAM region with restriction on alignment.
 * Tinyusb use follows macros to declare transferring memory so that they can be put
 * into those specific section.
 * e.g
 * - CFG_TUSB_MEM SECTION : __attribute__ (( section(".usb_ram") ))
 * - CFG_TUSB_MEM_ALIGN   : __attribute__ ((aligned(4)))
 */
#ifndef CFG_TUH_MEM_SECTION
#define CFG_TUH_MEM_SECTION
#endif

#ifndef CFG_TUH_MEM_ALIGN
#define CFG_TUH_MEM_ALIGN        __attribute__ ((aligned(4)))
#endif

// TODO: I added this from the original... is it ok?
#define CFG_TUSB_RHPORT0_MODE   (OPT_MODE_DEVICE)

//--------------------------------------------------------------------
// DEVICE CONFIGURATION
//--------------------------------------------------------------------
#define CFG_TUD_CDC              (1)

// CDC FIFO size of TX and RX
#define CFG_TUD_CDC_RX_BUFSIZE   (256) // TODO: these were originally 512, go back?
#define CFG_TUD_CDC_TX_BUFSIZE   (256) // TODO: these were originally 512, go back?
#define CFG_TUD_VENDOR           (0)

// CDC Endpoint transfer buffer size, more is faster
#define CFG_TUD_CDC_EP_BUFSIZE   64

//--------------------------------------------------------------------
// HOST CONFIGURATION
//--------------------------------------------------------------------

// Size of buffer to hold descriptors and other data used for enumeration
#define CFG_TUH_ENUMERATION_BUFSIZE 256

#define CFG_TUH_HUB                 0 // number of supported hubs
#define CFG_TUH_CDC                 1 // CDC ACM
#define CFG_TUH_CDC_FTDI            1 // FTDI UART
#define CFG_TUH_HID                 0
#define CFG_TUH_MSC                 0
#define CFG_TUH_VENDOR              0

// max device support (excluding hub device): 1 hub typically has 4 ports
#define CFG_TUH_DEVICE_MAX          (3*CFG_TUH_HUB + 1)

//------------- CDC -------------//

#define CFG_TUH_CDC_TX_BUFSIZE     512
#define CFG_TUH_CDC_RX_BUFSIZE     512

// Set Line Control state on enumeration/mounted:
// DTR ( bit 0), RTS (bit 1)
#define CFG_TUH_CDC_LINE_CONTROL_ON_ENUM    0x03

// Set Line Coding on enumeration/mounted, value for cdc_line_coding_t
// bit rate = 115200, 1 stop bit, no parity, 8 bit data width
#define CFG_TUH_CDC_LINE_CODING_ON_ENUM   { 9600, CDC_LINE_CONDING_STOP_BITS_1, CDC_LINE_CODING_PARITY_NONE, 8 }

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_CONFIG_H_ */
