#pragma once

#include <base_module.hpp>
#include <microphone_controller.hpp>
#include <algorithm>

namespace r2d2::microphone {

    /**
     * Class module_c provides the process function
     * for receiving data requests
     * and sending the data of the microphone module.
     */
    class module_c : public base_module_c {
    private:
        microphone_controller_c &mic;

    public:
        /**
         * Instantiate the module class
         *
         * @param comm - The internal communication bus instance.
         * @param microphone - The microphone controller that represents
         * the microphone.
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
		microphone_state.length = mic.get_buffer_size(); // max buffer length

		int c_index = 0; // we need to copy to a c style array in the frame
		for (auto &sample : mic.read_buffer()){
			microphone_state.microphone_data[c_index] = sample; // copy values to frame
			++c_index; // increase c style iterator
		}
                /*
                 * Send it off!
                 */
                comm.send(microphone_state);
            }
        }
    };

} // namespace r2d2::microphone
