/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2023 Ha Thach (thach@tinyusb.org)
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
 */

#include "tusb.h"
#include "usb.h"
#include "pio_usb.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"

#define PIN_5V_EN       18
#define PIN_USB_HOST_DP 16

void km_usbd_init(void) {
  tud_init(0);
}

void core1_main() {
#ifdef PIN_5V_EN
  gpio_init(PIN_5V_EN);
  gpio_set_dir(PIN_5V_EN, GPIO_OUT);
  gpio_put(PIN_5V_EN, 1);
#endif

  // rp2040 use pico-pio-usb for host tuh_configure() can be used to passed pio configuration to the host stack
  // Note: tuh_configure() must be called before tuh_init()
  pio_usb_configuration_t pio_cfg = PIO_USB_DEFAULT_CONFIG;
  pio_cfg.pin_dp = PIN_USB_HOST_DP;
  tuh_configure(1, TUH_CFGID_RPI_PIO_USB_CONFIGURATION, &pio_cfg);

  tuh_init(1);

  while (1) {
    tuh_task();

    uint8_t const idx = 0;
    if (tuh_cdc_connected(idx)) {
      tuh_cdc_write_flush(idx);
    }
  }
}

void km_usbh_init(void) {
  // Set the system clock to a multiple of 120mhz for bitbanging USB with pico-usb
  set_sys_clock_khz(120000, true);

  multicore_launch_core1(core1_main);
}
