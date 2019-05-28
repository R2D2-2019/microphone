#pragma once

#include <hwlib.hpp>

namespace r2d2::microphone {

    /**
     * Class steering_wheel_controller_c provides functions
     * for reading the data of the trust steering wheel.
     */
    class microphone_controller_c {
    private:
        hwlib::target::pin_adc *mic;

        bool mute = false;

    public:
        /**
         * Instantiate the microphone controller class
         *
         * @param mic The adc input that reads the microphone.
         */
        microphone_controller_c(hwlib::target::pin_adc &mic);

        /**
         * This function overrides the read() function of pin_in
         * and reads the data of a pin_in.
         *
         * @internal refreshes/reads the incoming data.
         */
        int_fast16_t read_mic();

        /**
         * This function overrides the read() function of pin_in
         * and reads the data of a pin_in.
         *
         * @internal refreshes/reads the incoming data.
         */
        void set_mute(bool setting);

        /**
         * This function is for testing/reading
         * the incoming data of the steering wheel.
         */
        void print();
    };
} // namespace r2d2::microphone
