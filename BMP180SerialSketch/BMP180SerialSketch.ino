#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

/* This driver uses the Adafruit unified sensor library (Adafruit_Sensor),
   which provides a common 'type' for sensor data and some helper functions.
   
   To use this driver you will also need to download the Adafruit_Sensor
   library and include it in your libraries folder.

   You should also assign a unique ID to this sensor for use with
   the Adafruit Sensor API so that you can identify this particular
   sensor in any data logs, etc.  To assign a unique ID, simply
   provide an appropriate value in the constructor below (12345
   is used by default in this example).
   
   Connections
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3.3V DC
   Connect GROUND to common ground
    
   History
   =======
   2013/JUN/17  - Updated altitude calculations (KTOWN)
   2013/FEB/13  - First version (KTOWN)
*/
   
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

void setup(void) 
{
  Serial.begin(9600);
  /* Initialise the sensor */
  if(!bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  pinMode(LED_BUILTIN, OUTPUT);  // imitation of the executive device
}

uint16_t tmr = 0;
int incomingByte = 0;
void loop(void) 
{
  // Send temperature every 5 seconds
  uint16_t ms = millis();
  if (ms - tmr > 5000) {
    tmr = ms;
    sensors_event_t event;
    bmp.getEvent(&event);
    if (event.pressure)
    {
      float temperature;
      bmp.getTemperature(&temperature);
      Serial.print(temperature);
    }
    else
    {
      Serial.println("Sensor error");
    }
  }
  // receive commands
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == 49) digitalWrite(LED_BUILTIN, HIGH);
    else if (incomingByte == 50) digitalWrite(LED_BUILTIN, LOW);
  }
}
