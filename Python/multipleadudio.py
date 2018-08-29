import pygame as pg
import time

pg.mixer.init()
pg.init()

AUDIO_FOLDER = "/home/pi/Documents/Projects/GPSAudio/SoundMessages/wav_correct/"

sounds = []

# Append sound files to the list.
# The sound files were obtained using web cam microphone
# and internal Windows recording app. Then, https://online-audio-converter.com
# website had been used to batch convert all the *.wma into *.wav files with
# default settings.
print("Appending ... " + AUDIO_FOLDER + "warning.wav")
sounds.append(pg.mixer.Sound(AUDIO_FOLDER + "warning.wav"))
for i in range(1,21):
    print("Appending ... " + AUDIO_FOLDER + str(i) + ".wav")
    sounds.append(pg.mixer.Sound(AUDIO_FOLDER + str(i) + ".wav"))

##for sound in sounds:
##    sound.play()
