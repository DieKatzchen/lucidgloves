//only compiles if BLESerial is set because it won't compile for a non-compatible board
#if COMMUNICATION == COMM_BLESERIAL
#include <NimBLEDevice.h>
#define   CONFIG_BT_NIMBLE_PINNED_TO_CORE   1 //Pins NimBLE to core 1
static NimBLEServer* pServer;
class BLESerialCommunication : public ICommunication {
  private:
    bool m_isOpen;

  public:
    BLESerialCommunication() {
      m_isOpen = false;
    }

    class ServerCallbacks: public NimBLEServerCallbacks {
      void onConnect(NimBLEServer* pServer) {
          #ifdef NEOPIXEL
          neopixelWrite(DEBUG_LED,0,RGB_BRIGHTNESS,0); // Green
          #endif
      };
      void onDisconnect(NimBLEServer* pServer) {
          #ifdef NEOPIXEL
          neopixelWrite(DEBUG_LED,0,0,RGB_BRIGHTNESS); // Blue
          #endif
      };
    };

    bool isOpen(){
      return m_isOpen;
    }

    void start(){
      NimBLEDevice::init(BTSERIAL_DEVICE_NAME);

      pServer = NimBLEDevice::createServer();
      pServer->setCallbacks(new ServerCallbacks());
      NimBLEService *pService = pServer->createService("6E400001-B5A3-F393-E0A9-E50E24DCCA9E"); //Main service
      NimBLECharacteristic *rxCharacteristic = pService->createCharacteristic("6E400002-B5A3-F393-E0A9-E50E24DCCA9E",NIMBLE_PROPERTY::WRITE);
      NimBLECharacteristic *txCharacteristic = pService->createCharacteristic("6E400003-B5A3-F393-E0A9-E50E24DCCA9E",NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
      pService->start();

      NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising(); // create advertising instance
      pAdvertising->addServiceUUID(pService->getUUID()); // tell advertising the UUID of our service
      pAdvertising->start(); // start advertising
      
      #if BT_ECHO
      Serial.begin(SERIAL_BAUD_RATE);
      Serial.println("The device started, now you can pair it with bluetooth!");
      #endif
      #ifdef NEOPIXEL
      neopixelWrite(DEBUG_LED,0,0,RGB_BRIGHTNESS); // Blue
      #endif
      m_isOpen = true;
    }

    void output(const std::vector< uint8_t > &vec){
      if(pServer->getConnectedCount()) {
        NimBLEService* pSvc = pServer->getServiceByUUID("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
        if(pSvc) {
          NimBLECharacteristic* qChr = pSvc->getCharacteristic("6E400003-B5A3-F393-E0A9-E50E24DCCA9E");
          if(qChr) {    
            qChr->setValue(vec);
            qChr->notify();
          }
        }
      }
      //else
      //vTaskDelay(1); //keep watchdog fed
      #if BT_ECHO
      Serial.write(data);
      Serial.write('\n');
      #endif
    }

    bool readData(const std::vector< uint8_t > *vec){
      /*byte size = m_SerialBT.readBytesUntil('\n', input, 100);
      input[size] = NULL;*/
      if(pServer->getConnectedCount()) {
        NimBLEService* pSvc = pServer->getServiceByUUID("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
        if(pSvc) {
          NimBLECharacteristic* qChr = pSvc->getCharacteristic("6E400002-B5A3-F393-E0A9-E50E24DCCA9E");
          if(qChr) {
            //String message = qChr->getValue();
            strcpy(input, qChr->getValue< uint8_t >());
          }
        }
      }
      return input != NULL && sizeof(input) > 0;
    }
};
#endif
