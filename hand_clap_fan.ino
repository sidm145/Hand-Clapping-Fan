int sensorPin = 2; // Connects to LM393 OUT
int ledPin = 4;    // Connects to LED
int motorPin = 3;  // Connects to your new 220 ohm resistor -> Transistor Base

bool fanIsOn = false; // Keeps track of the fan state

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
}

void loop() {
  // Using the LOW logic you discovered for your specific clap sensor!
  if (digitalRead(sensorPin) == LOW) {
    
    // Flip the state (ON becomes OFF, OFF becomes ON)
    fanIsOn = !fanIsOn; 
    
    if (fanIsOn == true) {
      digitalWrite(ledPin, HIGH); // Turn on LED
      
      // --- THE PRO KICKSTART ---
      // 1. Blast 100% power to overcome the heavy fan blade
      analogWrite(motorPin, 255); 
      delay(100);                 
      
      // 2. Drop down to a smooth cruising speed (~60% power). 
      // Thanks to the 220 ohm resistor, the transistor will stay ice cold!
      analogWrite(motorPin, 150); 
      
    } else {
      digitalWrite(ledPin, LOW);  // Turn off LED
      analogWrite(motorPin, 0);   // Turn off Motor completely
    }
    
    // Wait half a second so a single clap doesn't trigger it twice
    delay(500); 
  }
}
