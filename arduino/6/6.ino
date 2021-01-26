#include <Arduino_LSM9DS1.h> //Include the library for 9-axis IMU
#include <Arduino_LPS22HB.h> //Include library to read Pressure 
#include <Arduino_HTS221.h> //Include library to read Temperature and Humidity 
#include <Arduino_APDS9960.h> //Include library for colour, proximity and gesture recognition
#include <ArduinoBLE.h>

const char TEM_CHARACTERISTIC_UUID[] = "024dd1c2-ff3c-48e4-afd2-afea7d441f50";
const char HUM_CHARACTERISTIC_UUID[] = "e53fa8e6-6776-47ee-b179-38a422ec7218";
const char DEVICE_UUID[] = "67fcdd00-518d-4816-ae01-282b6f81aaee";
const char DEVICE_NAME[] = "6";
const char DELAY_UUID[] = "cc3d2a45-db3d-47df-87ba-3ba9c5261b03";
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
