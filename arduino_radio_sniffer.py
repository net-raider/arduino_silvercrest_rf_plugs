import serial
from matplotlib import pyplot as plt
from scipy.signal import correlate
import numpy as np


def timings2signal(timings, n_samples_per_tick=8, n_skip=1):
    signal = []
    bit = 1
    for t in timings[n_skip:]:
        bit = 1 - bit
        signal.extend([bit for i in range(t)])
    signal = np.array(signal, dtype=float)
    return signal


def signal2command(signal):
    timings = []
    timing = 0
    prev = signal[0]
    for curr in signal[1:]:
        if curr == prev:
            timing += 1
        else:
            timings.append(timing)
            timing = 0
        prev = curr
    return b"".join([v.to_bytes(4, "little") for v in timings])

def sniff_signal():
    buff = []
    LISTEN_CMD = bytes("l".encode("utf-8"))
    arduino = serial.Serial(port="/dev/ttyACM0", baudrate=9600)
    arduino.write(LISTEN_CMD)
    while True:
        msg = int.from_bytes(arduino.read(4), "little")
        if msg < 256 and chr(msg) == "z":
            break
        buff.append(msg)
    return timings2signal(buff)


signal = sniff_signal()
plt.plot(signal)
plt.show()
