#include <Adafruit_DotStar.h>
#include <SPI.h> 

// Here's how to control the LEDs from any two pins:
#define NUMPIXELS  89
#define DATAPIN    2
#define CLOCKPIN   3
#define ELAPSED    30000 // time, in milliseconds, to leave LEDs on
#define NEEDED     100 // LDR value to be equal to, or lower than

Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN);

int sensorPin = A0;             // select the input pin for Photoresistor
int inputPin1 = 4;               // choose the input pin (for PIR sensor 1)
int pirState = LOW;             // we start, assuming no motion detected
int val1 = 0;                    // variable for reading the pin status of PIR sensor 1
int systemState = 0;            // State of the system: 0 = no movement detected; 1 = movement detected
int lightValue = 0;             // Store value from photoresistor (0-1023)
unsigned long startTime = 0;    // Used to determine when state changed from 0 to 1

bool timeHasPassed(){
  return (millis() - startTime) >= ELAPSED;
}


void setup() {
  pinMode(inputPin1, INPUT);     // declare sensor as input
  pinMode(sensorPin, INPUT);     // declare Photoresistor as input
  
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP

  Serial.begin(9600);
}

void loop(){
  lightValue = analogRead(sensorPin);
  Serial.print("Light:  ");
  Serial.println(lightValue);
  // Determine if the area is dark enough to continue or not
  if(lightValue <= NEEDED){
    val1 = digitalRead(inputPin1);  // read input value of PIR sensor
    if (val1 == HIGH) {            // check if the input is HIGH
      // turn lights on
      strip.fill(0xFF0000); // 'On' pixel one at a time
      strip.show();
      // Just wait the elapsed amount of required time
      delay(ELAPSED);
    }
  }
  // Just for CYA sake, turn the LED strip off no matter what
  strip.clear();
  strip.show();
  // just a slight rest 
  delay(500);
}
