//GUN OXIMETER.
// Adding libraries
#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal.h>
int Contrast=145;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  
int temp;

#include<NewPing.h>
const int trigPin = 9;
const int echoPin = 10;

float duration, distance;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
MAX30105 particleSensor;

#define MAX_BRIGHTNESS 255
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
//Arduino Uno doesn't have enough SRAM to store 100 samples of IR led data and red led data in 32-bit format
//To solve this problem, 16-bit MSB of the sampled data will be truncated. Samples become 16-bit data.
uint16_t irBuffer[50]; //infrared LED sensor data
uint16_t redBuffer[50];  //red LED sensor data
#else
uint32_t irBuffer[50]; //infrared LED sensor data
uint32_t redBuffer[50];  //red LED sensor data
#endif

int32_t bufferLength; //data length
int32_t spo2; //SPO2 value
int8_t validSPO2; //indicator to show if the SPO2 calculation is valid
int32_t heartRate; //heart rate value
int8_t validHeartRate; //indicator to show if the heart rate calculation is valid

byte pulseLED = 11; //Must be on PWM pin
byte readLED = 13; //Blinks with each data read

void setup() {
  //LCD Set UP
  analogWrite(6,Contrast);
  lcd.begin(20, 4);
  
  //Presence Sensor Setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  
//  //HR and SPO2 Sensor Setup
  Serial.begin(9600); // initialize serial communication at 115200 bits per second:
  pinMode(pulseLED, OUTPUT);
  pinMode(readLED, OUTPUT);

if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println(F("MAX30105 was not found. Please check wiring/power."));
    while (1);
  }
  Serial.read();

  byte ledBrightness = 60; //Options: 0=Off to 255=50mA
  byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  byte sampleRate = 100; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 411; //Options: 69, 118, 215, 411
  int adcRange = 4096; //Options: 2048, 4096, 8192, 16384

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); 
  //Configure sensor with these settings
  mlx.begin();
  }

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1000);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  
   
   lcd.clear();
   lcd.setCursor(0, 0);
   
   lcd.print(distance);
   lcd.print(",");

   // Temperature

   temp= mlx.readObjectTempC();

  //LCD
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print("temperatre= ");
    lcd.print(mlx.readObjectTempC());
    lcd.print("C");
    delay(1000);

    //SPO2

    long irValue = particleSensor.getIR();
    bufferLength = 50; //buffer length of 100 stores 4 seconds of samples running at 25sps

  //read the first 50 samples, and determine the signal range
  for (byte i = 0 ; i < bufferLength ; i++)
  {
    while (particleSensor.available() == false) //do we have new data?
      particleSensor.check(); //Check the sensor for new data

    redBuffer[i] = particleSensor.getRed();
    irBuffer[i] = particleSensor.getIR();
    particleSensor.nextSample();
  }
   maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);

  //Continuously taking samples from MAX30102.  Heart rate and SpO2 are calculated every 1 second
  while (1)
  {
    //dumping the first 25 sets of samples in the memory and shift the last 75 sets of samples to the top
    for (byte i = 15; i < 50; i++)
    {
      redBuffer[i - 15] = redBuffer[i];
      irBuffer[i - 15] = irBuffer[i];
    }

    //take 25 sets of samples before calculating the heart rate.
    for (byte i = 25; i < 50; i++)
    {
      while (particleSensor.available() == false) //do we have new data?
        particleSensor.check(); //Check the sensor for new data

      digitalWrite(readLED, !digitalRead(readLED)); //Blink onboard LED with every data read

      redBuffer[i] = particleSensor.getRed();
      irBuffer[i] = particleSensor.getIR();
      particleSensor.nextSample();

     if (validSPO2){
      Serial.print(distance);
      Serial.print(",");
      Serial.print(temp);
      Serial.print(",");
      Serial.print(spo2, DEC);
      Serial.println(",");
      
      }
      delay(1000);
    //LCD
      lcd.setCursor(0, 3);
      lcd.print("spo2= ");
      lcd.print(spo2);
      lcd.print("%");
   }
    maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
}
  }
}
