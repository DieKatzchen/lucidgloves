#ifndef GESTURE_H
#define GESTURE_H
#include "../../AdvancedConfig.h"

class Gesture {
public:
    bool grabGesture(float *flexion);
    bool pinchGesture(float *flexion);
    bool triggerGesture(float *flexion);
};

#endif