// Stats.h: interface for the CStats class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "xrCore/FTimer.h"
#include "xrCore/Math/flags.hpp"
#include "xrCore/xrstring.h"
#include "xrCommon/xr_vector.h"
#include "xrCommon/xr_smart_pointers.h"
#include "xrEngine/StatGraph.h"
#include "xrEngine/pure.h"

class CGameFont;

DECLARE_MESSAGE(Stats);

class CStats : public pureRender
{
private:
    CGameFont* statsFont;
    CGameFont* fpsFont;
    xr_unique_ptr<CStatGraph> fpsGraph;
    xr_vector<shared_str> errors;

public:
    CStats();
    ~CStats();

    void Show(void);
    virtual void OnRender();
    void OnDeviceCreate(void);
    void OnDeviceDestroy(void);

private:
    void FilteredLog(const char* s);
};

enum
{
    st_sound = (1 << 0),
    st_sound_min_dist = (1 << 1),
    st_sound_max_dist = (1 << 2),
    st_sound_ai_dist = (1 << 3),
    st_sound_info_name = (1 << 4),
    st_sound_info_object = (1 << 5),
};

extern CStatTimer gTestTimer0; // debug counter
extern CStatTimer gTestTimer1; // debug counter
extern CStatTimer gTestTimer2; // debug counter
extern CStatTimer gTestTimer3; // debug counter

extern Flags32 g_stats_flags;
