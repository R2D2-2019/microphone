#include "hwlib.hpp"

int main(void) {
  // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);

    // pin allocation
    auto VCC =    hwlib::target::pin_out(hwlib::target::pins::d2);
    auto GND =    hwlib::target::pin_out(hwlib::target::pins::d3);
    auto MIC_IN = hwlib::target::pin_in (hwlib::target::pins::d4);
    auto STATUS = hwlib::target::pin_out(hwlib::target::pins::d13);

    // pin initialization
    GND.set(0);
    STATUS.set(1);

    while (true) {
      STATUS.set(MIC_IN.get());
      hwlib::wait_ms(10);
    }
}