import serial as pyserial
import time
import random
import sys
import click

sys.path.append(".")
from arduino_radio_commands import commands


@click.command()
@click.argument(
    "serial",
    type=click.Path(exists=True),
)
@click.option(
    "--device",
    "-d",
    default="MASTER",
    help="Device to control.",
    type=click.Choice(["A", "B", "C", "D", "MASTER"], case_sensitive=False),
)
@click.option(
    "--mode",
    "-m",
    default="OFF",
    help="Command to send to device.",
    type=click.Choice(["ON", "OFF"], case_sensitive=False),
)
def arduino_cmd(serial, device, mode):
    """
    Control SilverCrest RF 433MHz plugs with Arduino.

    SERIAL is the device to which Arduino is listening.
    """
    arduino = pyserial.Serial(port=serial, baudrate=9600)
    arduino.write(commands["{}_{}".format(device, mode)])
    time.sleep(1)


if __name__ == "__main__":
    arduino_cmd()
