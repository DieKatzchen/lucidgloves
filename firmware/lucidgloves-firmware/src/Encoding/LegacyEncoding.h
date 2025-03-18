#ifndef LEGACYENCODING_H
#define LEGACYENCODING_H

#include "IEncoding.h"
#include "Config.h"

class LegacyEncoding : public IEncoding {
public:
    void encode(OutboundData data, char* stringToEncode);
    DecodedData decodeData(char* stringToDecode);
};

#endif