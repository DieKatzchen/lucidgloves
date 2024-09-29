#include <vector>

#if ENCODING == ENCODE_PIPE
#define CLEAR_DATA 0
#define SAVE_INTER 1
#define SAVE_TRAVEL 2

struct HandData {
  const std::array<std::array<float, 4>, 5> flexion;
  const std::array<float, 5> splay;
  const float joyX;
  const float joyY;
  const bool joyButton;
  const bool trgButton;
  const bool aButton;
  const bool bButton;
  const bool grab;
  const bool pinch;
  const bool menu;
  const bool calibrate;
};

const int hand_union_size = sizeof(HandData);

union HandPacket{
  HandData structure;
  byte byteArray[hand_union_size];
};

HandPacket* encode(float* flexion, int joyX, int joyY, bool joyClick, bool triggerButton, bool aButton, bool bButton, bool grab, bool pinch, bool calib, bool menu);

struct HapticData{
  const std::array<int, 5> hapticLimits;
  int Z;
};

const int haptic_union_size = sizeof(HapticData);

union HapticPacket{
  HapticData structure;
  byte byteArray[haptic_union_size];
};

void decodeData(std::vector< uint8_t >* vec int* hapticLimits);
#endif

#if ENCODING == ENCODE_LEGACY
//legacy encoding
char* encode(int* flexion, int joyX, int joyY, bool joyClick, bool triggerButton, bool aButton, bool bButton, bool grab, bool pinch, bool calib, bool menu){
  static char stringToEncode[75];
  
  sprintf(stringToEncode, "%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d\n", 
  flexion[0], flexion[1], flexion[2], flexion[3], flexion[4],
  joyX, joyY, joyClick,
  triggerButton, aButton, bButton, grab, pinch
  );
  return stringToEncode;
}
//legacy decoding
void decodeData(char* stringToDecode, int* hapticLimits){
    byte index = 0;
    char* ptr = strtok(stringToDecode, "&");  // takes a list of delimiters
    while(ptr != NULL)
    {
        hapticLimits[index] = atoi(ptr);
        index++;
        ptr = strtok(NULL, "&");  // takes a list of delimiters
    }
}
#endif

#if ENCODING == ENCODE_ALPHA
//alphabetic encoding
char* encode(int* flexion, int joyX, int joyY, bool joyClick, bool triggerButton, bool aButton, bool bButton, bool grab, bool pinch, bool calib, bool menu){
  static char stringToEncode[75];
  int trigger = (flexion[1] > ANALOG_MAX/2) ? (flexion[1] - ANALOG_MAX/2) * 2:0;
  #if USING_SPLAY
  sprintf(stringToEncode, "A%dB%dC%dD%dE%dF%dG%dP%d%s%s%s%s%s%s%s%s(AB)%d(BB)%d(CB)%d(DB)%d(EB)%d\n", 
  flexion[0], flexion[1], flexion[2], flexion[3], flexion[4],
  joyX, joyY, trigger, joyClick?"H":"",
  triggerButton?"I":"", aButton?"J":"", bButton?"K":"", grab?"L":"", pinch?"M":"", menu?"N":"", calib?"O":"",
  flexion[5], flexion[6], flexion[7], flexion[8], flexion[9]
  );
  #else
  sprintf(stringToEncode, "A%dB%dC%dD%dE%dF%dG%dP%d%s%s%s%s%s%s%s%s\n", 
  flexion[0], flexion[1], flexion[2], flexion[3], flexion[4],
  joyX, joyY, trigger, joyClick?"H":"",
  triggerButton?"I":"", aButton?"J":"", bButton?"K":"", grab?"L":"", pinch?"M":"", menu?"N":"", calib?"O":""
  );
  #endif
  return stringToEncode;
}

//alpha decoding
void decodeData(char* stringToDecode, int* hapticLimits){

  //Check if a Z command was received
  //Serial.println("Message recieved");
  if (strchr(stringToDecode, 'Z') != NULL) {
    //Serial.println("Found Z!");
    bool toReturn = false;
    if (strstr(stringToDecode, "ClearData") != NULL) {
        clearFlags();
        toReturn = true;
    }
    if (strstr(stringToDecode, "SaveInter") != NULL) {
        saveIntermediate();
        toReturn = true;
    }
    if (strstr(stringToDecode, "SaveTravel") != NULL) {
        saveTravel();
        toReturn = true;
    }

    if (toReturn)
      return;
  }

  hapticLimits[0] = getArgument(stringToDecode, 'A'); //thumb
  hapticLimits[1] = getArgument(stringToDecode, 'B'); //index
  hapticLimits[2] = getArgument(stringToDecode, 'C'); //middle
  hapticLimits[3] = getArgument(stringToDecode, 'D'); //ring
  hapticLimits[4] = getArgument(stringToDecode, 'E'); //pinky
}

int getArgument(char* stringToDecode, char command){
  char* start = strchr(stringToDecode, command);
  if (start == NULL)
    return -1;
  else
    return atoi(start + 1);
}

#endif

#if ENCODING == ENCODE_PIPE
std::vector< uint8_t > encode(float* flexion, int joyX, int joyY, bool joyClick, bool triggerButton, bool aButton, bool bButton, bool grab, bool pinch, bool calib, bool menu){
  static HandPacket toEncode;
  for (int f = 0; f < 5; f++){ //fingers
    for (int j=0; j < 4; j++){ //joints
      toEncode.structure.flexion[f][j] = flexion[f];
    }
  }
  for (int i = 0; i < 5; i++{
     toEncode.structure.splay[i] = flexion[i+5]
  }
  toEncode.structure.joyX = joyX;
  toEncode.structure.joyY = joyY;
  toEncode.structure.joyButton = joyClick;
  toEncode.structure.trgButton = triggerButton;
  toEncode.structure.aButton = aButton;
  toEncode.structure.bButton = bButton;
  toEncode.structure.grab = grab;
  toEncode.structure.pinch = pinch;
  toEncode.structure.menu = menu;
  toEncode.structure.calibrate = calib;

  return toEncode.byteArray;
}

void decodeData(std::vector< uint8_t >* vec, int* hapticLimits){

  HapticPacket toDecode;
  toDecode.byteArray = &vec;
  
  //Check if a Z command was received
  //Serial.println("Message recieved");
  if (toDecode.structure.Z != NULL) {
    //Serial.println("Found Z!");
    bool toReturn = false;
    if (toDecode.structure.Z == CLEAR_DATA) {
        clearFlags();
        toReturn = true;
    }
    if (toDecode.structure.Z == SAVE_INTER) {
        saveIntermediate();
        toReturn = true;
    }
    if (toDecode.structure.Z == SAVE_TRAVEL) {
        saveTravel();
        toReturn = true;
    }

    if (toReturn)
      return;
  }
  
  for (int i = 0; i < 5; i++){
    hapticLimits[i] = toDecode.structure[i];
  }
}
#endif
