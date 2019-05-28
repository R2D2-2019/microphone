#include <microphone_controller.hpp>

r2d2::microphone::microphone_controller_c::microphone_controller_c(
    hwlib::target::pin_adc &mic)
    : mic(&mic) {
}

int_fast16_t r2d2::microphone::microphone_controller_c::read_mic() {
    return microphone_controller_c::mic->read();
}

void r2d2::microphone::microphone_controller_c::set_mute(bool setting) {
    mute = setting;
}

void r2d2::microphone::microphone_controller_c::print() {
    hwlib::cout << "Mic level: " << read_mic() << "\n";
}