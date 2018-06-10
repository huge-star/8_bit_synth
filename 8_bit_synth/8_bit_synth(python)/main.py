import pyaudio
import numpy as np
import pygame, sys
from pygame.locals import *

def generate(freq, exp = "t", fs = 44100, time = 1):
    point = round(time * fs)
    value = [0] * (point)
    if freq == -1:
        return (np.array(value)).astype(np.int8)
    # exp = input("Please enter a expression >>> ")
    for i in range(point):
        exp_sub = exp.replace('t', str(i))
        value[i] = round((eval(exp_sub) * 2.55 * 2 ** (freq / 12)) % 256)
    return np.array(value).astype(np.int8)



def play(value, fs = 44100, time = 1):
    p = pyaudio.PyAudio()

    # generate samples, note conversion to float32 array
    samples = (value).astype(np.int8)

    # for paFloat32 sample values must be in range [-1.0, 1.0]
    stream = p.open(format=pyaudio.paInt8,channels=1,rate=fs,output=True)

    # play. May repeat with different volume values (if done interactively)
    stream.write(samples)
    stream.stop_stream()
    stream.close()
    p.terminate()

preset = []
f = open("preset.txt", "a+")



# while flag:
#     sel = input("What would you like to do?\n1. exp\n2. save\n3. load\n4. quit")
#     if sel == 1:
exp = input("Please enter a expression >>> ")
data = [generate(-1)] * 14
for i in range(14):
    data[i] = generate(i, exp)

pygame.init()
DISPLAYSURF = pygame.display.set_mode((400, 300))
pygame.display.set_caption('8-bit synth')
while True:
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()
        if event.type == KEYDOWN:
            if event.key == pygame.K_a:
                value = data[0]
            if event.key == pygame.K_w:
                value = data[1]
            if event.key == pygame.K_s:
                value = data[2]
            if event.key == pygame.K_e:
                value = data[3]
            if event.key == pygame.K_d:
                value = data[4]
            if event.key == pygame.K_f:
                value = data[5]
            if event.key == pygame.K_t:
                value = data[6]
            if event.key == pygame.K_g:
                value = data[7]
            if event.key == pygame.K_y:
                value = data[8]
            if event.key == pygame.K_h:
                value = data[9]
            if event.key == pygame.K_u:
                value = data[10]
            if event.key == pygame.K_j:
                value = data[11]
            if event.key == pygame.K_k:
                value = data[12]
            if event.key == pygame.K_o:
                value = data[13]
        else:
            value = generate(-1)
        # if event.type == KEYUP:
        #     if event.key == pygame.K_a:
        #         term(stream, p)
    play(value)
    pygame.display.update()
    # if sel == 2:
    #     name = input("\nPlease enter of the name of the expression:")
    #
    #     preset.append("%d. %s %s" & (index, name, exp))
