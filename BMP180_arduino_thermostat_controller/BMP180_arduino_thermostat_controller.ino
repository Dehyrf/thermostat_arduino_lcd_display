#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <LiquidCrystal.h>

/*************************************************** 
  Designed specifically to work with the Adafruit BMP085 or BMP180 Breakout 
  ----> https://www.adafruit.com/products/391
  
  -Prereqs: BMP085 library and breakout, available from adafruit; LCD Display
  
  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  By: Dehyrf, based on libraries written by Limor Fried/Ladyada for Adafruit Industries.  
 ****************************************************/

// Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
// Connect GND to Ground
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
// EOC is not used, it signifies an end of conversion
// XCLR is a reset pin, also not used here
// Connect LCD to digital pins 12,11,5,4,3,2 (follow image in images folder)
// Connect relay to 5v, pin digital 13, and ground
// Connect refrigeration unit positive line to normally open on the relay and its power to common
// Connect potentiometer to 5v, gnd, and analog pin 3


Adafruit_BMP085 bmp;
LiquidCrystal lcd(12,11,5,4,3,2);
float set_tempF = 85.0;
int count = 0;
int relay = 13;
int poten = 3;

void setup() {
  pinMode(relay, OUTPUT); 
  lcd.begin(16, 2);
  Serial.begin(9600);
  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }
}
  
void loop() {
  float tempC = bmp.readTemperature();
  float tempF = (9.0/5.0) * tempC + 32.0;
  float val = analogRead(poten);
  set_tempF = val/15 + 32;
  
  if(tempF >= set_tempF && count >= 25){
    digitalWrite(relay, LOW);
  }
  if(tempF <= set_tempF){
    digitalWrite(relay, HIGH); 
    count = 0;
  }
  else{
    count++;  
  }
   
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Temp: ");
    lcd.print ((int)set_tempF);
    lcd.print((char)223);
    lcd.print(" F");
    lcd.setCursor(0, 1);
    lcd.print("Current: ");
    lcd.print ((int)tempF);
    lcd.print((char)223);
    lcd.print(" F");
    delay(175);
    
    /*Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
    
    // Calculate altitude assuming 'standard' barometric
    // pressure of 1013.25 millibar = 101325 Pascal
    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");

    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(bmp.readSealevelPressure());
    Serial.println(" Pa");

  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(101500));
    Serial.println(" meters");
    
    Serial.println();
    delay(500);*/
}

