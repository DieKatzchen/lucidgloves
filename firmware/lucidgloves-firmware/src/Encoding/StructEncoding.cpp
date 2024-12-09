#include "StructEncoding.h"
#include "../Util/Mapping.h"
#include <Arduino.h>
void StructEncoding::encode(InputData data, OutboundData dataToEncode){
  float trigger = (data.fingers[1] > ANALOG_MAX/2) ? (data.fingers[1] - ANALOG_MAX/2) * 2:0;
  #if USING_SPLAY
  for (int i=0;i<NUM_FINGERS,i++)
    dataToEncode.splay = mapf(data.splay,0,ANALOG_MAX,0,1);
  #endif
  for (int i=0;i<NUM_FINGERS;i++)
	for(int j=0;j<4;j++)
      dataToEncode.flexion[i][j] = mapf(data.fingers[i],0,ANALOG_MAX,0,1);
  dataToEncode.joyX = mapf(data.joyX,0,ANALOG_MAX,0,1);
  dataToEncode.joyY = mapf(data.joyY,0,ANALOG_MAX,0,1);
  dataToEncode.trgValue = trigger;
  dataToEncode.joyButton = data.joyClick;
  dataToEncode.trgButton = data.triggerButton;
  dataToEncode.aButton = data.aButton;
  dataToEncode.bButton = data.bButton;
  dataToEncode.grab = data.grab;
  dataToEncode.pinch = data.pinch;
  dataToEncode.menu = data.menu;
  dataToEncode.calibrate = data.calib;
}
DecodedData StructEncoding::decodeData(DecodedData* dataToDecode) {
    return *dataToDecode;
}