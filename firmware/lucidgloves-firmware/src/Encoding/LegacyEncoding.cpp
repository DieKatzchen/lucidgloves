#include "LegacyEncoding.h"
#include <Arduino.h>
void LegacyEncoding::encode(OutboundData data, char* stringToEncode){
  sprintf(stringToEncode, "%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d\n", 
  (int)data.fingers[0], (int)data.fingers[1], (int)data.fingers[2], (int)data.fingers[3], (int)data.fingers[4],
  data.joyX, data.joyY, data.joyClick,
  data.triggerButton, data.aButton, data.bButton, data.grab, data.pinch
  );
}

DecodedData LegacyEncoding::decodeData(char* stringToDecode) {
    DecodedData decodedData = {};

    byte index = 0;
    char* ptr = strtok(stringToDecode, "&");
    while(ptr != NULL && index < NUM_FINGERS)
    {
        decodedData.servoValues[index] = atoi(ptr);
        decodedData.fields.servoValuesReceived[index] = true;
        index++;
        ptr = strtok(NULL, "&");
    }

    return decodedData;
}
