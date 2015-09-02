# thermostat_arduino_lcd_display
Sketch for an arduino (tested on and works on an uno) that is a thermostat with display to power on/off a refrigeration unit lacking integrated temperature controls. Uses an arduino, a lcd display, a relay board, two potentiometers (one for changing the set temperature and one for dimming the display), and a BMP180 temperature/pressure module for sensor feedback.

Instructions:
Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!),
Connect GND to Ground,
Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5,
Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4,
EOC is not used, it signifies an end of conversion,
XCLR is a reset pin, also not used here,
Connect LCD to digital pins 12,11,5,4,3,2 (follow image in images folder),
Connect relay to 5v, pin digital 13, and ground,
Connect refrigeration unit positive line to normally open on the relay and its power to common,
Connect potentiometer to 5v, gnd, and analog pin 3
