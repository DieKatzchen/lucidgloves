#pragma once
#include "ICommunication.h"
#include "../../Config.h"

#if COMMUNICATION == COMM_BLESERIAL
#include <NimBLEDevice.h>
#define   CONFIG_BT_NIMBLE_PINNED_TO_CORE   1 //Pins NimBLE to core 1

class BLESerialCommunication : public ICommunication {
private:
    bool m_isOpen;
    NimBLEServer* pServer;
    
public:
    BLESerialCommunication();

    bool isOpen() override;

    void start() override;

    void output(char* data) override;

    bool readData(char* input) override;
};
#endif
