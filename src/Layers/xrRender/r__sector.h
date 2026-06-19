// Portal.h: interface for the CPortal class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include <utility>
#include <vector>

#include "Common/Platform.hpp"
#include "Common/types.hpp"
#include "xrCDB/ISpatial.h"
#include "xrCDB/xrCDB.h"
#include "xrCore/FixedVector.h"
#include "xrCore/Math/fbox2.hpp"
#include "xrCore/Math/math_funcs_inline.hpp"
#include "xrCore/Math/matrix.hpp"
#include "xrCore/Math/plane.hpp"
#include "xrCore/Math/sphere.hpp"
#include "xrCore/Math/vector3.hpp"
#include "xrEngine/pure.h"

namespace xray::render::RENDER_NAMESPACE
{
class CPortal;
class CSector;

struct _scissor : public Fbox2
{
    float depth;
};

// Connector
class CPortal : public IRender_Portal
#ifdef DEBUG
                ,
                public pureRender
#endif
{
public:
    using Poly = svector<Fvector, 6>;
    struct level_portal_data_t
    {
        u16 sector_front;
        u16 sector_back;
        Poly vertices;
    };

private:
    Poly poly;
    CSector *pFace, *pBack;

public:
    Fplane P;
    Fsphere S;
    u32 marker;
    BOOL bDualRender;

    void setup(const level_portal_data_t& data, const std::vector<CSector*>& portals);

    Poly& getPoly() { return poly; }
    CSector* Back() { return pBack; }
    CSector* Front() { return pFace; }
    CSector* getSector(CSector* pFrom) { return pFrom == pFace ? pBack : pFace; }
    CSector* getSectorFacing(const Fvector& V)
    {
        if (P.classify(V) > 0)
            return pFace;
        else
            return pBack;
    }
    CSector* getSectorBack(const Fvector& V)
    {
        if (P.classify(V) > 0)
            return pBack;
        else
            return pFace;
    }
    float distance(const Fvector& V) { return _abs(P.classify(V)); }
    CPortal();
    virtual ~CPortal();

#ifdef DEBUG
    virtual void OnRender();
#endif
};

class dxRender_Visual;

// Main 'Sector' class
class CSector : public IRender_Sector
{
public:
    struct level_sector_data_t
    {
        std::vector<u32> portals_id;
        u32 root_id;
    };

protected:
    dxRender_Visual* m_root; // whole geometry of that sector

public:
    std::vector<CPortal*> m_portals;
    std::vector<CFrustum> r_frustums;
    std::vector<_scissor> r_scissors;
    _scissor r_scissor_merged;
    u32 r_marker;

public:
    // Main interface
    dxRender_Visual* root() { return m_root; }
    void setup(const level_sector_data_t& data, const std::vector<CPortal*>& portals);

    CSector() { m_root = nullptr; }
    virtual ~CSector() = default;
};

class CPortalTraverser
{
public:
    enum
    {
        VQ_HOM = (1 << 0),
        VQ_SSA = (1 << 1),
        VQ_SCISSOR = (1 << 2),
        VQ_FADE = (1 << 3), // requires SSA to work
    };

public:
    u32 i_marker; // input
    u32 i_options; // input:	culling options
    Fvector i_vBase; // input:	"view" point
    Fmatrix i_mXFORM; // input:	4x4 xform
    Fmatrix i_mXFORM_01; //
    CSector* i_start; // input:	starting point
    std::vector<CSector*> r_sectors; // result
    std::vector<std::pair<CPortal*, float>> f_portals; //

public:
    CPortalTraverser();
    void traverse(IRender_Sector* start, CFrustum& F, Fvector& vBase, Fmatrix& mXFORM, u32 options);
    void traverse_sector(CSector *sector, CFrustum& F, _scissor& R);
    void fade_portal(CPortal* _p, float ssa);
    void fade_render();
#ifdef DEBUG
    void dbg_draw();
#endif
};
} // namespace xray::render::RENDER_NAMESPACE
