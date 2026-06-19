#pragma once

#include <vector>

#include "pure_relcase.h"

// fwd. decl.
class IGameObject;
template <class T> struct _vector3;
using Fvector = _vector3<float>;

namespace Feel
{
class Touch : private pure_relcase
{
    friend class pure_relcase;

public:
    struct DenyTouch
    {
        IGameObject* O;
        /*DWORD*/ unsigned long Expire;
    };

protected:
    std::vector<DenyTouch> feel_touch_disable;

public:
    std::vector<IGameObject*> feel_touch;
    std::vector<IGameObject*> q_nearest;

public:
    void feel_touch_relcase(IGameObject* O);

public:
    Touch();
    virtual ~Touch();

    virtual bool feel_touch_contact(IGameObject* O);
    virtual void feel_touch_update(Fvector& P, float R);
    virtual void feel_touch_deny(IGameObject* O, u32 T);
    virtual void feel_touch_new(IGameObject* O){};
    virtual void feel_touch_delete(IGameObject* O){};
};
};
