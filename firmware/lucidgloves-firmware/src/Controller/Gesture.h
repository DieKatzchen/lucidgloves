#ifndef GESTURE_H
#define GESTURE_H
#include "../../AdvancedConfig.h"

class Gesture {
public:
    bool grabGesture(int *flexion);
    bool pinchGesture(int *flexion);
    bool triggerGesture(int *flexion);
};

#endif