#pragma once

#include <base_module.hpp>
#include <microphone_controller.hpp>

namespace r2d2::microphone {

    /**
     * Class module_c provides the process function
     * for receiving data requests
     * and sending the data of the steering_wheel_controller_c.
     */
    class module_c : public base_module_c {
    private:
        microphone_controller_c &mic;

    public:
        /**
         * Instantiate the module class
         *
         * @param comm - The internal communication bus instance.
         * @param microphone - The steering wheel controller that represents
         * the steering wheel/manual control.
         */
        module_c(base_comm_c &comm, microphone_controller_c &mic)
            : base_module_c(comm), mic(mic) {

            comm.listen_for_frames({frame_type::MICROPHONE});
        }

        /**
         * This function lets the module process data
         */
        void process() override {

            while (comm.has_data()) {

                auto frame = comm.get_data();

                /*
                 * Only process frame if it is a request
                 */
                if (!frame.request) {
                    continue;
                }
                // frame_manual_control_s movement_state;

                // movement_state.brake = microphone.get_button(2);
                // movement_state.rotation = microphone.get_slider(0);
                // movement_state.speed = microphone.get_slider(1);

                /*
                 * Send it off!
                 */
                comm.send(1);
            }

            /*
             * Send it off!
             */
            comm.send(mic.read_mic());
        }
    };

} // namespace r2d2::microphone
