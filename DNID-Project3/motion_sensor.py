from gpiozero import MotionSensor
from gpiozero import Motor
from time import sleep

# Initialize motion sensor
pir = MotionSensor(4)  # Assuming motion sensor is connected to GPIO pin 4

# Initialize 360 motor
motor = Motor(forward=17, backward=18)  # Assuming 360 motor is connected to GPIO pins 17 and 18

try:
    while True:
        pir.wait_for_motion()  # Wait for motion to be detected
        print("Motion detected!")
        motor.forward()  # Activate the motor in one direction (adjust as needed)
        sleep(5)  # Motor activation duration (adjust as needed)
        motor.stop()  # Stop the motor
except KeyboardInterrupt:
    # Clean up GPIO resources on keyboard interrupt
    pir.close()
    motor.close()
