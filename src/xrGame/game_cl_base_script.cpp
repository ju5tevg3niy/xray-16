#include <vector>
#include "pch_script.h"
#include "game_cl_base.h"

void SZoneMapEntityData::script_register(lua_State* luaState)
{
    using namespace luabind;

    module(luaState)
    [
        class_<SZoneMapEntityData>("SZoneMapEntityData")
            .def(constructor<>())
            .def_readwrite("pos", &SZoneMapEntityData::pos)
            .def_readwrite("color", &SZoneMapEntityData::color),

        class_<std::vector<SZoneMapEntityData>>("ZoneMapEntities")
            .def("push_back", (void (std::vector<SZoneMapEntityData>::*)(const SZoneMapEntityData&))
                (&std::vector<SZoneMapEntityData>::push_back))
    ];
}

void RPoint::script_register(lua_State* luaState)
{
    using namespace luabind;

    module(luaState)
    [
        class_<RPoint>("RPoint")
            .def(constructor<>())
            .def_readwrite("P", &RPoint::P)
            .def_readwrite("A", &RPoint::A)
    ];
}
