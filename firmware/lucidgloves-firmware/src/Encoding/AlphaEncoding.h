#ifndef ALPHAENCODING_H
#define ALPHAENCODING_H

#include "IEncoding.h"
#include "Config.h"

class AlphaEncoding : public IEncoding {
public:
    void encode(OutboundData data, char* stringToEncode);
    DecodedData decodeData(char* stringToDecode);
private:
    int getArgument(char* stringToDecode, char command);
};

#endif