#pragma once

#include <hwlib.hpp>

namespace r2d2::microphone {

    /**
     * Class microphone_controller_c provides functions
     * for collecting audio data from the KY-038 module.
     */
    class microphone_controller_c {
    private:
        hwlib::target::pin_adc &mic;
	uint16_t sample_buffer[63]; // max internal CAN bus buffer size
        bool muted = false; // microphone is not muted by default

    public:
        /**
         * Instantiate the microphone controller class
         *
         * @param mic The adc input that reads the microphone
         */
        microphone_controller_c(hwlib::target::pin_adc &new_mic):
	    mic(new_mic)
	{}

        /**
         * This function reads the analog data from the
	 * microphone pin
         *
         * @return returns the microphone value
	 * 
         */
        uint16_t read_mic();

	/**
	 * This function returns a pointer to the sample buffer
	 *
	 * @return pointer to sample buffer 
	 */
	uint16_t *read_buffer();

        /**
	 * This function takes a block of 63
	 * samples and collects it in it's internal buffer
	 * 
	 * @internal calls read_mic() to fill sample_buffer
	 */
	void sample();

        /**
         * This function blocks the read_mic() function
         * 
         * @internal sets mute value to true
         */
        void mute();
	
	/**
	 * This function unblocks the read_mic() function
	 *
	 * @ internal sets mute value to false
	 */
	void unmute();


        /**
         * This function is for testing/reading
         * the incoming data of the microphone.
         */
        void print();
    };
} // namespace r2d2::microphone
