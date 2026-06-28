#include "Common/types.hpp"
#pragma once

#define DU_BOX_NUMVERTEX 8
#define DU_BOX_NUMFACES 12
#define DU_BOX_NUMLINES 12
#define DU_BOX_NUMVERTEX2 36

namespace xray::render::RENDER_NAMESPACE
{
extern Fvector du_box_vertices[];
extern u16 du_box_faces[];
extern u16 du_box_lines[];

extern Fvector du_box_vertices2[];
} // namespace xray::render::RENDER_NAMESPACE
