#include "hwlib.hpp"

int main(void) {
  // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    auto pin_mic = hwlib::target::pin_in_out(hwlib::target::pins::a3);

    hwlib::wait_ms(1000);
    for (;;){
        hwlib::cout << "this works via arduino";
        hwlib::cout << pin_mic.read();
        hwlib::wait_ms(1000);
    }
}