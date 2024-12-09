#pragma once
#include "../Util/DataStructs.h"

//Interface for communication
class ICommunication {

  public:
    virtual bool isOpen() = 0;

    virtual void start() = 0;

    virtual void output(char* data) = 0;
	
	virtual void output(OutboundData* data) = 0;

	virtual bool readData(char* input) = 0;
	
	virtual bool readData(DecodedData* input) = 0;
};
