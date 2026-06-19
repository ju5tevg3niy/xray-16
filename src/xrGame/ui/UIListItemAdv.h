#pragma once

#include "UIListItem.h"

class CUIListItemAdv : public CUIListItem
{
public:
    virtual ~CUIListItemAdv();

    void AddField(LPCSTR val, float width);
    void AddWindow(CUIWindow* pWnd);
    virtual void SetTextColor(u32 color);

protected:
    float GetNextLeftPos();
    typedef std::vector<CUIStatic*>::iterator my_it;
    std::vector<CUIStatic*> m_fields;
};
