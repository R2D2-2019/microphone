#include "hwlib.hpp"
#include <hwlib-arduino-due.hpp>

int main(void) {
  // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    //Testing to read input data using pin_in as well as using the adc
    auto pin_mic = hwlib::target::pin_in(hwlib::target::pins::a3);
    //Constructor to define the pin as a adc input
    auto adc = hwlib::target::pin_adc( hwlib::target::ad_pins::a1 ); //Object creation


    hwlib::wait_ms(1000);
    for (;;){
        hwlib::cout << "this works via arduino";
        hwlib::cout << pin_mic.read();
        unsigned int mic_value = adc.get(); //Convert and read	
        hwlib::wait_ms(1000);
    }
}