/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 5; //In seconds
BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      if (advertisedDevice.haveManufacturerData()) {
        String mfgdata = advertisedDevice.getManufacturerData().c_str();
        if (mfgdata.length() >= 8) {
          Serial.printf("SWGE Advertised DEVICE: %s \n", advertisedDevice.toString().c_str());
          if (mfgdata[0] = 0x01 && mfgdata[1] == 0x83) {
            if (mfgdata[2] == 0x0a && mfgdata[3] == 0x04) {
              // Location Beacon
              Serial.print("Location Beacon found: ");
              if (mfgdata[4] == 0x01 && mfgdata[5] == 0x02 && mfgdata[6] == 0xa6 && mfgdata[7] == 0x01) {
                // Marketplace, Outdoor Areas
                Serial.println("Marketplace, Outdoor Areas");
              }
              else if
              (mfgdata[4] == 0x02 && mfgdata[5] == 0x02 && mfgdata[6] == 0xa6 && mfgdata[7] == 0x01) {
                // Behind Droid Depot
                Serial.println("Behind Droid Depot");
              }
              else if
              (mfgdata[4] == 0x03 && mfgdata[5] == 0x02 && mfgdata[6] == 0xa6 && mfgdata[7] == 0x01) {
                // Resistance
                Serial.println("Resistance");
              }
              else if
              (mfgdata[4] == 0x04 && mfgdata[5] == 0x02 && mfgdata[6] == 0xa6 && mfgdata[7] == 0x01) {
                // Unknown
                Serial.println("Unknown and never seen");
              }
              else if
              (mfgdata[4] == 0x05 && mfgdata[5] == 0x02 && mfgdata[6] == 0xa6 && mfgdata[7] == 0x01) {
                // Droid Depot
                Serial.println("Droid Depot");
              }
              else if
              (mfgdata[4] == 0x06 && mfgdata[5] == 0x02 && mfgdata[6] == 0xa6 && mfgdata[7] == 0x01) {
                // Dok-Ondar's
                Serial.println("Dok-Ondar's");
              }
              else if
              (mfgdata[4] == 0x07 && mfgdata[5] == 0x02 && mfgdata[6] == 0xa6 && mfgdata[7] == 0x01) {
                // First Order
                Serial.println("First Order");
              }
              else if
              (mfgdata[4] == 0x03 && mfgdata[5] == 0x18 && mfgdata[6] == 0xba && mfgdata[7] == 0x01) {
                // Droid Depot (DL)
                Serial.println("Droid Depot (DL)");
              }
              else if
              (mfgdata[4] == 0x06 && mfgdata[5] == 0x18 && mfgdata[6] == 0xba && mfgdata[7] == 0x01) {
                // Marketplace (WDW)
                Serial.println("Marketplace (WDW)");
              }
              else if
              (mfgdata[4] == 0x05 && mfgdata[5] == 0xff && mfgdata[6] == 0xa6 && mfgdata[7] == 0x01) {
                // Oga's 1
                Serial.println("Oga's 1");
              }
              else if
              (mfgdata[4] == 0x07 && mfgdata[5] == 0xff && mfgdata[6] == 0xa6 && mfgdata[7] == 0x01) {
                // Oga's 2
                Serial.println("Oga's 2");
              }
              else
              {
                Serial.println("Unrecgonized beacon!");
              }
            } 
            else if (mfgdata[2] == 0x03 && mfgdata[3] == 0x04) {
              // Droid Beacon
              Serial.print("Droid Beacon found: ");
              Serial.println("");
            }
          }
        }
      }
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
}

void loop() {
  // put your main code here, to run repeatedly:
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());
  Serial.println("Scan done!");
  pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
  delay(2000);
}
