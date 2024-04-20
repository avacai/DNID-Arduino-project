import serial
import pygame

# Initialize serial connection
ser = serial.Serial('/dev/cu.usbmodem21201', 9600)  # Change to match Arduino's port

# Initialize Pygame mixer
pygame.mixer.init()

# Function to play music
def play_music():
    pygame.mixer.music.load("battlemusic.mp3")  # Replace with your music file path
    pygame.mixer.music.play()

def stop_music():
    pygame.mixer.music.stop()
# Main loop
while True:
    # Read from serial port
    data = ser.readline().decode().strip()
    print(data);

    # Check if the received data indicates to play music
    if data == "play_music":
        play_music()
