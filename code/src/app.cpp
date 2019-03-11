#include <app.hpp>
#include <array>

// sampling duration in seconds
constexpr unsigned int sampling_duration = 4;
// frequency in hertz
constexpr unsigned int frequency = 4'000;
// storage size
constexpr unsigned int sample_size = frequency * sampling_duration;
// sampeling period in microseconds
constexpr unsigned int period = 1'000'000 / frequency;

std::array<bool, sample_size> sample_buffer;
unsigned int index = 0;

r2d2::app_c::app_c(hwlib::target::pins sensor_pin,
                   hwlib::target::pins status_pin)
    : sensor(sensor_pin), status(status_pin) {
}

void r2d2::app_c::main() {
    while (true) {
        if (index == sample_size) {
            r2d2::app_c::publish();
            r2d2::app_c::idle();
        }
        sample_buffer[index++] = sensor.read();
        status.write(sensor.read());
        hwlib::wait_us(period);
    }
}

void r2d2::app_c::publish() {
    for (const auto &b : sample_buffer) {
        hwlib::cout << b;
    }
    hwlib::cout << "\n";
}

void r2d2::app_c::idle() {
    while (true)
        continue;
}
