#include "BTSerialCommunication.h"

#if COMMUNICATION == COMM_BTSERIAL

BTSerialCommunication::BTSerialCommunication() {
    m_isOpen = false;
}

bool BTSerialCommunication::isOpen() {
    return m_isOpen;
}

union incoming {
   DecodedData inData;
   byte in[11];
};

union outgoing {
   OutboundData outData;
   byte out[11];
};

void BTSerialCommunication::start() {
    m_SerialBT.begin(BTSERIAL_DEVICE_NAME);
    #if BT_ECHO
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println("The device started, now you can pair it with bluetooth!");
    #endif
    m_isOpen = true;
}

void BTSerialCommunication::output(OutboundStruct* data) {

    #if BT_ECHO
    Serial.print(data);
    Serial.flush();
    #endif
}

bool BTSerialCommunication::readData(ReceivedStruct* input) {

    return input != NULL && sizeof(input) > 0;
}

void BTSerialCommunication::output(char* data) {
    m_SerialBT.print(data);
    #if BT_ECHO
    Serial.print(data);
    Serial.flush();
    #endif
}

bool BTSerialCommunication::readData(char* input) {
    /*byte size = m_SerialBT.readBytesUntil('\n', input, 100);
    input[size] = NULL;*/
    String message = m_SerialBT.readStringUntil('\n');
    strcpy(input, message.c_str());
    return input != NULL && strlen(input) > 0;
}
#endif
