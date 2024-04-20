#include <Servo.h>

const int buttonPin = 2; // The pin connected to the button
int buttonState = 0;     // Current state of the butto
int debug = 0;
int lastButtonState = 0;
const int PIN_TO_SENSOR = 5;   // the pin that OUTPUT pin of sensor is connected to
int pinStateCurrent   = LOW; // current state of pin
int pinStatePrevious  = LOW; // previous state of pin

Servo myservo;  // create servo object to control a servo
Servo myservo360;
int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
unsigned long touchTime = 0; // variable to store the time when the 180 servo motor is touched
boolean touched = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600); // Initialize serial communication
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(PIN_TO_SENSOR, INPUT);
  myservo360.attach(10); // attaches the 360 servo on pin 10 to the servo object
}

void loop() {
  pinStatePrevious = pinStateCurrent; // store old state
  pinStateCurrent = digitalRead(PIN_TO_SENSOR);   // read new state

  if (pinStatePrevious == LOW && pinStateCurrent == HIGH) {   // pin state change: LOW -> HIGH
    Serial.println("Motion detected!");
    myservo360.write(90); // Set the angle of the 360-degree servo to 90 degrees (adjust as needed)
    delay(1000); 
    touched = true; 
    
  }
  else if (pinStatePrevious == HIGH && pinStateCurrent == LOW) {   // pin state change: HIGH -> LOW
    Serial.println("Motion stopped!");
    myservo360.write(0);  // Set the angle of the 360-degree servo to 0 degrees (adjust as needed
  }
  buttonState = digitalRead(buttonPin); // Read the state of the button
  //Serial.print("Enter Loop Button state set at ");
  //Serial.println(buttonState);
  if(buttonState != lastButtonState) {
  if (buttonState == LOW) {
      debug++;
      //Serial.print(debug);
      Serial.println("play_music"); // Send a signal to play music
      
    } else {
      //Serial.println("off");
    }
    delay(500); // Debounce delay
  }
  lastButtonState = buttonState;

  val = analogRead(potpin); // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180); // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);   
  // sets the servo position according to the scaled value
  // Only move the 360 servo if motion is detected
  if (pinStateCurrent == HIGH) {
    if (touched && (millis() - touchTime >= 5000)) {
      myservo360.write(90); // Turn on the 360 servo motor 5 seconds after the 180 servo motor has been touched
      touched = false; // Reset the touched flag
    }
  }
  delay(15); // waits for the servo to get there
}
