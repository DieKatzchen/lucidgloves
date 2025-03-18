#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
#include "../../AdvancedConfig.h"

const char* const SPECIAL_COMMANDS[] = {
    "SaveInter",
    "SaveTravel",
    "ClearData"
    // Add more commands as needed
};

//NUM_SPECIAL_COMMANDS can be defined this way because all char* are pointers of the same size
const int NUM_SPECIAL_COMMANDS = sizeof(SPECIAL_COMMANDS) / sizeof(SPECIAL_COMMANDS[0]);

//6 bytes
struct ReceivedFields {
    bool servoValuesReceived[NUM_FINGERS];
    bool specialCommandReceived;
};

//16 bytes + command (10 bytes?)
struct ReceivedStruct {
    ReceivedFields fields;
    int servoValues[NUM_FINGERS];
    const char* command;
};


// "\\.\pipe\vrapplication\input\glove\v2\<left/right>"
//120 bytes
struct OutboundStruct {
  float flexion[5][4];
  float splay[5];
  float joyX;
  float joyY;
  bool joyButton;
  bool trgButton;
  bool aButton;
  bool bButton;
  bool grab;
  bool pinch;
  bool menu;
  bool calibrate;

  float trgValue;
};

//32 bytes + splay
struct OutboundData {
	float fingers[NUM_FINGERS];
    int joyX;
    int joyY;
    bool joyClick;
    bool triggerButton;
    bool aButton;
    bool bButton;
    bool grab;
    bool pinch;
    bool calib;
    bool menu;

    //20 bytes
    #if USING_SPLAY
	  float splay[NUM_FINGERS];
    #endif
};

#endif