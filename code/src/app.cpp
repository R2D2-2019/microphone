#include <app.hpp>
#include <array>

constexpr unsigned int size = 4000 * 4;
std::array<bool, size> buffer;
unsigned int index = 0;


r2d2::app_c::app_c(hwlib::target::pins sensor_pin,
                   hwlib::target::pins status_pin)
    : sensor(sensor_pin), status(status_pin) {
}

void r2d2::app_c::main() {
    while (true) {
        if (index == size) {
            r2d2::app_c::publish();
            r2d2::app_c::idle();
        }
        buffer[index++] = sensor.read();
        status.write(sensor.read());
        hwlib::wait_us(250);
    }
}

void r2d2::app_c::publish() {
    for (const auto &b : buffer) {
        hwlib::cout << b;
    }
    hwlib::cout << "\n";
}

void r2d2::app_c::idle() {
    while (true)
        continue;
}
