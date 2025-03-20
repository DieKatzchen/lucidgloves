#include "Gesture.h"

bool Gesture::grabGesture(float *flexion){
  return (flexion[PINKY_IND] + flexion[RING_IND] + flexion[MIDDLE_IND] + flexion[INDEX_IND]) / 4 <= ANALOG_MAX/2 ? 0:1;
}

bool Gesture::pinchGesture(float *flexion){
  return (flexion[INDEX_IND] + flexion[THUMB_IND]) / 2 <= ANALOG_MAX/2 ? 0:1;
}

bool Gesture::triggerGesture(float *flexion){
  return flexion[INDEX_IND]<=(ANALOG_MAX/2)?0:1;
}
