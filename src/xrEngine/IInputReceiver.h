#include "Common/types.hpp"
// IInputReceiver.h: interface for the IInputReceiver class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "xrCore/Math/flags.hpp"

// despite being unused in this file, it's almost always used in IR_* functions
// so it's logically correct to include it
#include "xr_level_controller.h"

class IInputReceiver
{
public:
    virtual ~IInputReceiver() = default;

    [[nodiscard]]
    bool IR_GetKeyState(int dik) const;

    virtual void IR_Capture();
    virtual void IR_Release();

    virtual void IR_OnActivate();
    virtual void IR_OnDeactivate();

    virtual void IR_OnMousePress(int /*btn*/) {}
    virtual void IR_OnMouseRelease(int /*btn*/) {}
    virtual void IR_OnMouseHold(int /*btn*/) {}
    virtual void IR_OnMouseWheel(float /*x*/, float /*y*/) {}
    virtual void IR_OnMouseMove(int /*x*/, int /*y*/) {}

    virtual void IR_OnKeyboardPress(int /*dik*/) {}
    virtual void IR_OnKeyboardRelease(int /*dik*/) {}
    virtual void IR_OnKeyboardHold(int /*dik*/) {}
    virtual void IR_OnTextInput(pcstr /*text*/) {}

    virtual void IR_OnControllerPress(int /*dik*/, const ControllerAxisState& /*state*/) {}
    virtual void IR_OnControllerRelease(int /*dik*/, const ControllerAxisState& /*state*/) {}
    virtual void IR_OnControllerHold(int /*dik*/, const ControllerAxisState& /*state*/) {}

    virtual void IR_OnControllerAttitudeChange(Fvector /*change*/) {}
};

extern float psMouseSens;
extern float psMouseSensScale;
extern Flags32 psMouseInvert;

extern float psControllerStickSensX;
extern float psControllerStickSensY;
extern float psControllerStickSensScale;
extern float psControllerStickInnerDeadZone;
extern float psControllerStickOuterDeadZone;
extern float psControllerStickAngularDeadZone;
extern float psControllerSensorSens;
extern float psControllerSensorDeadZone;
extern float psControllerCursorAutohideTime;
extern Flags32 psControllerFlags;

enum EControllerFlags
{
    ControllerInvertX,
    ControllerInvertY,
    ControllerEnableSensors,
};
