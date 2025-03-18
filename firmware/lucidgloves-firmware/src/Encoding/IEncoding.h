#ifndef IENCODING_H
#define IENCODING_H
#include "../Util/DataStructs.h"



// Interface for encoding
class IEncoding {
public:
    virtual void encode(OutboundData data, char* stringToEncode) = 0;
	
	virtual void encode(OutboundData data, OutboundStruct* dataToEncode) = 0;

    virtual ReceivedStruct decodeData(char* stringToDecode) = 0;
	
	virtual ReceivedStruct decodeData(ReceivedStruct* dataToDecode) = 0;
};

#endif