#include "../headers/microphone_controller.hpp"

uint16_t r2d2::microphone::microphone_controller_c::read_mic() {
    if (!muted){
        return r2d2::microphone::microphone_controller_c::mic.read(); // return adc pin (microphone) value
    }
    else{
        return 0; // don't return an audible value
    }
}

void r2d2::microphone::microphone_controller_c::sample(){
    for (int i=0; i < 63; ++i){
        sample_buffer[i] = microphone_controller_c::read_mic(); // fill sample buffer
    }
}

uint16_t* r2d2::microphone::microphone_controller_c::read_buffer(){
    return sample_buffer; // return pointer to buffer
}

void r2d2::microphone::microphone_controller_c::mute() {
    if (!muted){ // if the mic is not muted
        muted = true; // mute the microphone
    }
    return;
    
}

void r2d2::microphone::microphone_controller_c::unmute(){
    if (muted){ // if the mic is muted
        muted = false; // unmute the microphone;
    }
    return;
}

void r2d2::microphone::microphone_controller_c::print() {
    hwlib::cout << "[Mic level]: " << read_mic() << '\n';
}

