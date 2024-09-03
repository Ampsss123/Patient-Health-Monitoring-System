#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM maths.
#include <PulseSensorPlayground.h>  
#include <LiquidCrystal.h> 
#define LM35 A1
int Contrast=75;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  
  
//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor
void setup() 
{  
  Serial.begin(9600);          
  analogWrite(6,Contrast);
  lcd.begin(16, 2);
  pulseSensor.analogInput(PulseWire);  
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);  
  // Double-check the "pulseSensor" object was created and "began" seeing a signal.
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset. 
  }
}

void loop() 
{
  
 int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now.
if (pulseSensor.sawStartOfBeat()) 
{            // Constantly test to see if "a beat happened".
 Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: ");                        // Print phrase "BPM: "
 Serial.println(myBPM);                        // Print the value inside of myBPM.
}

  delay(20);

  lcd.setCursor(0, 0);
     lcd.print("Pulse: ");
     
    lcd.setCursor(3, 0);
    lcd.print(myBPM);

    float lmvalue = analogRead(LM35);
  float tempr = (lmvalue*500)/1023;
  //Serial.println(tempr);
  delay(2000);
   lcd.setCursor(0, 1);
    lcd.print("Temp");
   lcd.setCursor(0,6);
    lcd.print(tempr);
  
}