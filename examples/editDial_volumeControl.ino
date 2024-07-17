// Anticlockwise - Volume down
// Clockwise - Volume Up
// Button - Pause media

//both libs available in the arduino library manager
#include <Encoder.h>
#include <HID-Project.h>

// Define the pins for the rotary encoder
#define ENCODER_CLK 8
#define ENCODER_DT 9
#define ENCODER_SW 7
Encoder myEnc(ENCODER_CLK, ENCODER_DT);

long oldPosition  = -999;
int buttonState = 0;
int lastButtonState = 0;

void setup() {
  // Initialize the encoder switch pin
  pinMode(ENCODER_SW, INPUT_PULLUP);
  // Start the consumer control emulation
  Consumer.begin();
  // Initialize the encoder position
  myEnc.write(0);
}

void loop() {
  long newPosition = myEnc.read() / 4;

  if (newPosition != oldPosition) {
    if (newPosition > oldPosition) {
      // Volume up
      Consumer.write(MEDIA_VOLUME_UP);
    } else {
      // Volume down
      Consumer.write(MEDIA_VOLUME_DOWN);
    }
    oldPosition = newPosition;
  }

  // Read the state of the encoder switch
  buttonState = digitalRead(ENCODER_SW);
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      // Pause/Play media
      Consumer.write(MEDIA_PLAY_PAUSE);
    }
    lastButtonState = buttonState;
  }
}