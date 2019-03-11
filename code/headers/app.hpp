#pragma once
#include <hwlib.hpp>

namespace r2d2 {
    class app_c {
    public:
        app_c(hwlib::target::pins sensor_pin, hwlib::target::pins status_pin);

        /**\brief entry point of application
         *  does not return
         */
        void main();

        /**\brief
         *  writes internal buffer to hwlib::cout
         */
        void publish();

        /* \brief
         *  busy while true loop
         */
        void idle();

    private:
        hwlib::target::pin_in sensor;
        hwlib::target::pin_out status;
    };
} // namespace r2d2
