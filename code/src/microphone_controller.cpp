#include <microphone_controller.hpp>

namespace r2d2::microphone {

  uint16_t microphone_controller_c::read_mic() {
    if (!muted) {
      return mic.read(); // return adc pin (microphone) value
    } else {
      return 0; // don't return an audible value
    }
  }

  void r2d2::microphone::microphone_controller_c::sample() {
    for (int i = 0; i < get_buffer_size(); ++i) {
      sample_buffer[i] = read_mic(); // fill sample buffer
    }
  }

  const std::array<uint16_t, microphone_controller_c::buffer_size> &
  microphone_controller_c::read_buffer() {
    return sample_buffer; // return reference to buffer
  }

  void microphone_controller_c::mute() {
    muted = true; // mute the microphone
  }

  void microphone_controller_c::unmute() {
    muted = false; // unmute the microphone;
  }

  void microphone_controller_c::print() {
    hwlib::cout << "[Mic level]: " << read_mic() << '\n';
  }
}

