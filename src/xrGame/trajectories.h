#include "Common/types.hpp"
#pragma once

#include <vector>

#include "xrCore/Math/vector3.hpp"

// fwd. decl.
namespace collide { class rq_results; }

struct trajectory_pick
{
    Fvector center;
    Fvector z_axis;
    Fvector y_axis;
    Fvector x_axis;
    Fvector sizes;
    u8 invert_x;
    u8 invert_y;
    u8 invert_z;
};

bool trajectory_intersects_geometry(float trajectory_time, Fvector const& trajectory_start,
    Fvector const& trajectory_end, Fvector const& trajectory_velocity, Fvector& collide_position,
    IGameObject* const self_object, IGameObject* const ignored_object, collide::rq_results& temp_rq_results,
    std::vector<trajectory_pick>* const out_trajectory_picks, std::vector<Fvector>* const out_collide_tris,
    Fvector const& box_size); // can be zero - ray is traced then
