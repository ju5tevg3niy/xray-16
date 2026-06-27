#include <vector>
#pragma once

namespace xray::render::RENDER_NAMESPACE
{
class light;
class light_Package
{
public:
    std::vector<light*> v_point;
    std::vector<light*> v_spot;
    std::vector<light*> v_shadowed;

public:
    void clear();
    void sort();
};
} // namespace xray::render::RENDER_NAMESPACE
