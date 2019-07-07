#include <hwlib.hpp>

#include <comm.hpp>
#include <module.hpp>
#include <microphone_controller.hpp>


int main(void) {

    using namespace r2d2;

    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(10);

    comm_c comm;
    auto mic = hwlib::target::pin_adc(hwlib::target::ad_pins::a0);
    auto microphone_controller = microphone::microphone_controller_c(mic);

    microphone::module_c module(comm, microphone_controller);

    for(;;) {
//        microphone_controller.print();
        module.process();
        hwlib::wait_ms(100);
    }

    return 0;
}
