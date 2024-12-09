#pragma once
#include "../Util/DataStructs.h"



// Interface for encoding
class IEncoding {
public:
    virtual void encode(InputData data, char* stringToEncode) = 0;
	
	virtual void encode(OutboundData data, InputData dataToEncode) = 0;

    virtual DecodedData decodeData(char* stringToDecode) = 0;
	
	virtual DecodedData decodeData(DecodedData* dataToDecode) = 0;
};
