#include <Arduino_LSM9DS1.h> //Include the library for 9-axis IMU
#include <Arduino_LPS22HB.h> //Include library to read Pressure 
#include <Arduino_HTS221.h> //Include library to read Temperature and Humidity 
#include <Arduino_APDS9960.h> //Include library for colour, proximity and gesture recognition
#include <ArduinoBLE.h>

const char TEM_CHARACTERISTIC_UUID[] = "6bb9f26e-0c38-43da-bcad-223716de67c7";
const char HUM_CHARACTERISTIC_UUID[] = "ad1ac85f-8734-4d1f-8aa0-7e0547727924";
const char DEVICE_UUID[] = "80516a4e-3b58-433d-bbf2-96b805823398";
const char DEVICE_NAME[] = "5";
const char DELAY_UUID[] = "628d9b1d-85d5-4006-8a32-307aa06cc89b";
const int DEFAULTTIME = 2000;
int delayTime = DEFAULTTIME;




BLEService jjavaService(DEVICE_UUID);
BLEFloatCharacteristic tem(TEM_CHARACTERISTIC_UUID, BLERead | BLENotify);
BLEFloatCharacteristic hum(HUM_CHARACTERISTIC_UUID, BLERead | BLENotify);
BLEUnsignedIntCharacteristic delayt(DELAY_UUID, BLERead | BLEWrite);



void setup(){
  Serial.begin(9600); //Serial monitor to display all sensor values 

  if (!IMU.begin()) //Initialize IMU sensor 
  { Serial.println("Failed to initialize IMU!"); while (1);}

  if (!BARO.begin()) //Initialize Pressure sensor 
  { Serial.println("Failed to initialize Pressure Sensor!"); while (1);}

  if (!HTS.begin()) //Initialize Temperature and Humidity sensor 
  { Serial.println("Failed to initialize Temperature and Humidity Sensor!"); while (1);}

  if (!APDS.begin()) //Initialize Colour, Proximity and Gesture sensor 
  { Serial.println("Failed to initialize Colour, Proximity and Gesture Sensor!"); while (1);}
 

  if (!BLE.begin()) //Initialize Colour, Proximity and Gesture sensor 
  { Serial.println("Failed to initialize BLE"); while (1);}

  BLE.setLocalName(DEVICE_NAME);
  BLE.setDeviceName(DEVICE_NAME);
  BLE.setAdvertisedService(jjavaService);
  jjavaService.addCharacteristic(tem);
  jjavaService.addCharacteristic(hum);
  jjavaService.addCharacteristic(delayt);
  
  
  BLE.addService(jjavaService);

  BLE.advertise();
 }



void loop()
{
  BLEDevice central = BLE.central();

  if (central)
  {
    Serial.println(central.address());

    while (central.connected()){
      

      if(delayt.written()){
        delayTime = delayt.value();
        }
      Serial.print("time delay = ");Serial.println(delayTime);

      
      float Temperature = HTS.readTemperature();
      float Humidity = HTS.readHumidity();

      float t = roundf(Temperature*100);
      float h = roundf(Humidity*100)/10000;
      float a = t + h;

      Serial.print("Temperature = ");Serial.println(Temperature);
      Serial.print("Humidity = ");Serial.println(Humidity);

      tem.writeValue(a);
      delay (200);
      

      delay(delayTime);
      }
    }


}
