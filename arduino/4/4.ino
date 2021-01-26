#include <Arduino_LSM9DS1.h> //Include the library for 9-axis IMU
#include <Arduino_LPS22HB.h> //Include library to read Pressure 
#include <Arduino_HTS221.h> //Include library to read Temperature and Humidity 
#include <Arduino_APDS9960.h> //Include library for colour, proximity and gesture recognition
#include <ArduinoBLE.h>

const char TEM_CHARACTERISTIC_UUID[] = "ff929363-3695-429c-9010-6eff43cfa4b7";
const char HUM_CHARACTERISTIC_UUID[] = "f5ac381b-b56f-4288-a042-5900f556d5c4";
const char DEVICE_UUID[] = "227c7c6c-13ae-4132-80b5-05556df0198e";
const char DEVICE_NAME[] = "4";
const char DELAY_UUID[] = "9396186d-2574-4bc8-ae58-4c3da3ee84eb";
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
