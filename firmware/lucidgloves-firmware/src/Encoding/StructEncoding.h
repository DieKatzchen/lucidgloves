#ifndef STRUCTENCODING_H
#define STRUCTENCODING_H

#include "IEncoding.h"
#include "Config.h"

class StructEncoding : public IEncoding {
public:
    void encode(OutboundData data, InputData* dataToEncode);
    DecodedData decodeData(DecodedData* dataToDecode);
};

#endif