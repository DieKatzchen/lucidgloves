#ifndef ICOMMUNICATION_H
#define ICOMMUNICATION_H
#include "../Util/DataStructs.h"

//Interface for communication
class ICommunication {

  public:
    virtual bool isOpen() = 0;

    virtual void start() = 0;

	virtual void output(OutboundStruct data) = 0;

	virtual bool readData(ReceivedStruct* input) = 0;
	
	virtual void output(char* data) = 0;

    virtual bool readData(char* input) = 0;
};

#endif