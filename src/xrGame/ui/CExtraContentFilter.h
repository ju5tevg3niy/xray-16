#include "xrCore/xrstring.h"
#include <vector>
#pragma once

class CExtraContentFilter
{
    struct PackData
    {
        shared_str sPackName;
        bool bEnabled;
        std::vector<shared_str> aContent;
    };

    std::vector<PackData*> aDataPacks;

    bool CheckPackKey(LPCSTR KeyName);

public:
    CExtraContentFilter();
    virtual ~CExtraContentFilter();

    bool IsDataEnabled(LPCSTR pData);
};
