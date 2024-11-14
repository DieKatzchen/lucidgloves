#pragma once

#include "IEncoding.h"
#include "Config.h"

class StructEncoding : public IEncoding {
public:
    void encode(OutboundData data, InputData dataToEncode) override;
    DecodedData decodeData(DecodedData* dataToDecode) override;
private:
    float mapf(int value, int fromLow, int fromHigh);
};
