import pyaudio
import wave

form_1 = pyaudio.paInt16 # 16-bit resolution
chans = 1 # 1 channel
sample_rate = 44100 # Sampling rate in khz
chunk = 4096 # 2^12 samples for buffer
record_secs = 10 # amount of seconds to record
dev_index = 3 # device index found by p.get_device_info_by_index(ii), follow the guide on the microphone wiki to see which index to use.
wav_output_filename = 'mictest.wav' # the filename of .wav file

audio = pyaudio.PyAudio() # create pyaudio instantiation

for i in range(audio.get_device_count()): # this loop is used to see if you've got the correct device index
  dev = audio.get_device_info_by_index(i)
  print((i,dev['name'],dev['maxInputChannels']))

# create pyaudio stream
stream = audio.open(format = form_1,rate = sample_rate,channels = chans, \
                    input_device_index = dev_index,input = True, \
                    frames_per_buffer=chunk)
print("recording")
frames = []

# loop through stream and append audio chunks to frame array
for ii in range(0,int((sample_rate/chunk)*record_secs)):
    data = stream.read(chunk)
    frames.append(data)

print("finished recording")

# stop the stream, close it, and terminate the pyaudio instantiation
stream.stop_stream()
stream.close()
audio.terminate()

# save the audio frames as .wav file
wavefile = wave.open(wav_output_filename,'wb')
wavefile.setnchannels(chans)
wavefile.setsampwidth(audio.get_sample_size(form_1))
wavefile.setframerate(sample_rate)
wavefile.writeframes(b''.join(frames))
wavefile.close()