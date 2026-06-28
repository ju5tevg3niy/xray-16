#include "Common/types.hpp"
#include "xrCore/Math/matrix.hpp"
#pragma once

#include <vector>
#include <list>

#include "CameraDefs.h"
#include "xrCore/PostProcess/PPInfo.hpp"

using EffectorCamVec = std::list<CEffectorCam*>;
using EffectorPPVec = std::vector<CEffectorPP*>;

#define effCustomEffectorStartID 10000

struct SCamEffectorInfo;
class CCameraManager
{
protected:
    SCamEffectorInfo m_cam_info;

    EffectorCamVec m_EffectorsCam;
    EffectorCamVec m_EffectorsCam_added_deffered;
    EffectorPPVec m_EffectorsPP;

    bool m_bAutoApply;
    SPPInfo pp_affected;
    void UpdateDeffered();

    virtual void UpdateCamEffectors();
    virtual void UpdatePPEffectors();
    virtual bool ProcessCameraEffector(CEffectorCam* eff);
    void OnEffectorReleased(SBaseEffector* e);

public:
#ifdef DEBUG
    u32 dbg_upd_frame;
#endif

    void Dump();
    u32 Count() { return m_EffectorsCam.size() + m_EffectorsCam_added_deffered.size(); }
    CEffectorCam* AddCamEffector(CEffectorCam* ef);
    CEffectorCam* GetCamEffector(ECamEffectorType type);
    void RemoveCamEffector(ECamEffectorType type);

    ECamEffectorType RequestCamEffectorId();
    EEffectorPPType RequestPPEffectorId();
    CEffectorPP* GetPPEffector(EEffectorPPType type);
    CEffectorPP* AddPPEffector(CEffectorPP* ef);
    void RemovePPEffector(EEffectorPPType type);

    IC Fvector Position() const { return m_cam_info.p; }
    IC Fvector Direction() const { return m_cam_info.d; }
    IC Fvector Up() const { return m_cam_info.n; }
    IC Fvector Right() const { return m_cam_info.r; }
    IC float Fov() const { return m_cam_info.fFov; }
    IC float Aspect() const { return m_cam_info.fAspect; }
    IC void camera_Matrix(Fmatrix& M) { M.set(m_cam_info.r, m_cam_info.n, m_cam_info.d, m_cam_info.p); }
    void Update(const Fvector& P, const Fvector& D, const Fvector& N, float fFOV_Dest, float fASPECT_Dest,
        float fFAR_Dest, u32 flags);
    void UpdateFromCamera(const CCameraBase* C);

    void ApplyDevice();
    static void ResetPP();

    CCameraManager(bool bApplyOnUpdate);
    virtual ~CCameraManager();
};
extern SPPInfo pp_identity;
extern SPPInfo pp_zero;

extern float psCamInert;
extern float psCamSlideInert;
