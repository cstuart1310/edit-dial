// This is frankenstein code, half written by me (Callum Stuart), and half found on stack overflow
// This program will only work with a board compatible with keyboard and mouse inputs (I use an arduino micro (not to be confused with the nano or mini) )

// WIRING
// GND - GND
// + - VCC
//CLK - PIN 8
//DT - PIN 9
// SW - PIN 7

 #include <Keyboard.h> //Includes Keyboard library needed for keyboard/mouse inputs
 #define outputA 8
 #define outputB 9
const int button = 7;
 int counter = 0; 
 int aState;
 int aLastState;  
 int buttonState = 0;   
 void setup() { 
  // Sets pinmodes
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   pinMode(button, INPUT);   
   Serial.begin (9600);
   // Reads the starting state of the outputA
   aLastState = digitalRead(outputA);   
 } 
 void loop() { 

  //Dial
   aState = digitalRead(outputA); // Reads the state of the outputA
   // If the previous and the current state of the outputA are different, the dial has turned
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
       counter ++;
       Keyboard.write(KEY_LEFT_ARROW); // What the dial does when turned left
       delay(1); 
       Serial.print("Left"); // For testing
     } else {
       counter --;
       Keyboard.write(KEY_RIGHT_ARROW); // What the dial does when turned right
       delay(1);
       Serial.print("Right"); // For testing
     }
     Serial.print("Position: ");
     Serial.println(counter);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
 //Button
 
 buttonState = digitalRead(button);
  if (buttonState != HIGH) { // What the button does when pressed
   Serial.println("space");
   Keyboard.press(0x80); // Hex code for CTRL, .press means it is held down until .release
   delay(10);
   Keyboard.press('k');  // Holds K
   delay(10);
   Keyboard.releaseAll(); // Releases all keys
   delay(100);
 
 } else {
Serial.println("not");
}
 }
