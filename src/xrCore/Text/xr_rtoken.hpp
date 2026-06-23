#pragma once
#include "Common/types.hpp"
#include "xrCore/xrstring.h"

struct xr_rtoken
{
    shared_str name;
    int id;

    xr_rtoken(pcstr _nm, int _id)
        : name(_nm), id(_id) {}

    void rename(pcstr _nm) { name = _nm; }
    bool equal(pcstr _nm) const { return (0 == xr_strcmp(name.c_str(), _nm)); }
};
