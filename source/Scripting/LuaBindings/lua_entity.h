#ifndef __lua_entity_h
#define __lua_entity_h

#include "Scripting/LuaBindings/luna.h"
#include "Entity/entity.h"

class LuaEntity {
    public:
        static const char className[];
        static Luna<LuaEntity>::RegType methods[];

        LuaEntity(lua_State *L);
        ~LuaEntity();

        int GetX(lua_State *L);
        int GetY(lua_State *L);
        int GetZ(lua_State *L);

        int SetX(lua_State *L);
        int SetY(lua_State *L);
        int SetZ(lua_State *L);
    private:
        Entity *entity;
}

#endif
