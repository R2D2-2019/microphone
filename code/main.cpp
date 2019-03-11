#include <hwlib.hpp>
#include <app.hpp>

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);

    auto app = r2d2::app_c(hwlib::target::pins::d2, hwlib::target::pins::d13);
    app.main();
}
