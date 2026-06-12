#include <cstddef>

#include "Common/Platform.hpp"
#include "Common/types.hpp"
#include "xrCore/String/string_funcs_inline.hpp"
#include "xrCore/xrDebug_macros.h"

#include "clsid.hpp"

void CLSID2TEXT(CLASS_ID id, pstr text)
{
    text[8] = 0;
    for (int i = 7; i >= 0; i--)
    {
        text[i] = char(id & 0xff);
        id >>= 8;
    }
}

CLASS_ID TEXT2CLSID(pcstr text)
{
    VERIFY3(xr_strlen(text) <= 8, "Beer from creator CLASS_ID:", text);
    char buf[9];
    buf[8] = 0;
    strncpy_s(buf, sizeof(buf), text, 8);
    size_t need = 8 - xr_strlen(buf);
    while (need)
    {
        buf[8 - need] = ' ';
        need--;
    }
    return xray::make_clsid(buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
}
