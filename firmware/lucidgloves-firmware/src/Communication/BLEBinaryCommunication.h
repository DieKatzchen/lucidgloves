#ifndef BLEBINARYCOMMUNICATION_H
#define BLEBINARYCOMMUNICATION_H
#include "ICommunication.h"
#include "../../Config.h"

#if COMMUNICATION == COMM_BLEBINARY
#include <NimBLEDevice.h>
#define   CONFIG_BT_NIMBLE_PINNED_TO_CORE   1 //Pins NimBLE to core 1

class BLEBinaryCommunication : public ICommunication {
private:
    bool m_isOpen;
    NimBLEServer* pServer;
    
public:
    BLEBinaryCommunication();

    bool isOpen() override;

    void start() override;

	void output(OutboundData* data) override;

    bool readData(DecodedData* input) override;
};
#endif

#endif