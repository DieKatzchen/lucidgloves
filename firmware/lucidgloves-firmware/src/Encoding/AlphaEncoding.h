#ifndef ALPHAENCODING_H
#define ALPHAENCODING_H

#include "IEncoding.h"
#include "Config.h"

class AlphaEncoding : public IEncoding {
public:
    void encode(OutboundData data, char* stringToEncode);
	void encode(OutboundData data, OutboundStruct* dataToEncode)
    ReceivedStruct decodeData(char* stringToDecode);
	ReceivedStruct decodeData(ReceivedStruct* dataToDecode)
private:
    int getArgument(char* stringToDecode, char command);
};

#endif