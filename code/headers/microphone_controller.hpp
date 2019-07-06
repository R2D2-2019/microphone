#pragma once

#include "hwlib.hpp"
#include <array>

namespace r2d2::microphone {

    /**
     * Class microphone_controller_c provides functions
     * for collecting audio data from the KY-038 module.
     *
     * Uses a template to determine the buffer size at
     * compile time.
     */

    class microphone_controller_c {
    private:
        hwlib::adc &mic;
	static constexpr int buffer_size = 63; // size of internal communication buffer, this size must not be changed!!
	std::array<uint16_t, buffer_size> sample_buffer; // array storing our samples
        bool muted = false; // microphone is not muted by default

    public:
        /**
         * Instantiate the microphone controller class
         *
         * @param mic The adc input that reads the microphone
         */
        microphone_controller_c(hwlib::adc &new_mic):
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
	const std::array<uint16_t, buffer_size> & read_buffer();
	
	/**
	 * This function returns the buffer size
	 */
	constexpr int get_buffer_size() const{
		return buffer_size;
	}

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
