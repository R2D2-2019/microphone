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
    GND.write(0);
    STATUS.write(1);

    while (true) {
      STATUS.write(MIC_IN.read());
      hwlib::wait_ms(10);
    }
}