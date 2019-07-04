#pragma once

#include <base_module.hpp>
#include <microphone_controller.hpp>

namespace r2d2::microphone {

    /**
     * Class module_c provides the process function
     * for receiving data requests
     * and sending the data of the microphone module.
     */
    class module_c : public base_module_c {
    private:
        microphone_controller_c &mic;
	const int buffer_length = 63; //max buffer length

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

		// take a sample
		mic.sample();

		// build frame
		frame_microphone_s microphone_state;
		microphone_state.length = buffer_length; // max buffer length

		uint16_t *microphone_ptr = mic.read_buffer(); // get pointer to buffer
		for (int i=0; i<buffer_length; ++i){
			microphone_state.microphone_data[i] = *microphone_ptr;
			microphone_ptr++;
		}

                /*
                 * Send it off!
                 */
                comm.send(microphone_state);
            }
        }
    };

} // namespace r2d2::microphone
