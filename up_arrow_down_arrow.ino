// WIRING
// GND - GND
// + - VCC
//CLK - PIN 8
//DT - PIN 9


 #include <Keyboard.h> //Includes Keyboard library needed for keyboard/mouse inputs
 #include <Mouse.h>
 #define outputA 8
 #define outputB 9
const int button = 7;
 int counter = 0; 
 int aState;
 int aLastState;  
 int buttonState = 0;   
 void setup() { 
   Mouse.begin();
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   pinMode(button, INPUT);   
   Serial.begin (9600);
   // Reads the initial state of the outputA
   aLastState = digitalRead(outputA);   
 } 
 void loop() { 

  //Dial
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
       counter ++;
       Keyboard.write(KEY_UP_ARROW); 
       delay(1);
       Serial.print("LEft");
     } else {
       counter --;
       Keyboard.write(KEY_DOWN_ARROW); 
       delay(1);
       Serial.print("Right");
     }
     Serial.print("Position: ");
     Serial.println(counter);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
  //Button
 
 buttonState = digitalRead(button);
  if (buttonState != HIGH) {
   Serial.println("space");
   Mouse.click();
   delay(500);
 
 }
 }
