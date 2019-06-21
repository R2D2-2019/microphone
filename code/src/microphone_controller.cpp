#include <microphone_controller.hpp>

namespace r2d2::microphone{

    int_fast16_t r2d2::microphone::microphone_controller_c::read_mic() {
        if (!mute){
            return microphone_controller_c::mic.read(); // return adc pin (microphone) value
        }
        else{
            return 0; // don't return an audible value
        }
    }

    void r2d2::microphone::microphone_controller_c::mute() {
        if (!mute){ // if the mic is not muted
            mute = true; // mute the microphone
        }
        return;
    
    }   

    void r2d2::microphone::microphone_controller_c::unmute(){
        if (mute){ // if the mic is muted
            mute = false; // unmute the microphone;
        }
        return;
    }

    void r2d2::microphone::microphone_controller_c::print() {
        hwlib::cout << "[Mic level]: " << read_mic() << '\n';
    }

}
