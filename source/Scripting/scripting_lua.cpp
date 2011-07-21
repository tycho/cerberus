/*
 * Copyright (c) 2011 Eddie Ringle <eddie@eringle.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "universal_include.h"

#include "Entity/behaviors.h"
#include "Entity/entity.h"

#include "Input/input.h"
#include "Scripting/scripting_lua.h"

int push_table_instance(lua_State* L, int lo) {

	if (lua_istable(L, lo)) {

		lua_pushstring(L, ".c_instance");
		lua_gettable(L, lo);
		if (lua_isuserdata(L, -1)) {

			lua_replace(L, lo);
			return 1;
		} else {

			lua_pop(L, 1);
			return 0;
		};
	} else {
		return 0;
	};

	return 0;
}

/* the equivalent of lua_is* for usertype */
static int lua_isusertype (lua_State* L, int lo, const char* type)
{
	if (!lua_isuserdata(L,lo)) {
		if (!push_table_instance(L, lo)) {
			return 0;
		};
	};
	{
		/* check if it is of the same type */
		int r;
		const char *tn;
		if (lua_getmetatable(L,lo))        /* if metatable? */
		{
		 lua_rawget(L,LUA_REGISTRYINDEX);  /* get registry[mt] */
		 tn = lua_tostring(L,-1);
		 r = tn && (strcmp(tn,type) == 0);
		 lua_pop(L, 1);
			if (r)
			 return 1;
			else
			{
				/* check if it is a specialized class */
				lua_pushstring(L,"tolua_super");
				lua_rawget(L,LUA_REGISTRYINDEX); /* get super */
				lua_getmetatable(L,lo);
				lua_rawget(L,-2);                /* get super[mt] */
				if (lua_istable(L,-1))
				{
					int b;
					lua_pushstring(L,type);
					lua_rawget(L,-2);                /* get super[mt][type] */
					b = lua_toboolean(L,-1);
					lua_pop(L,3);
					if (b)
					 return 1;
				}
			}
		}
 }
	return 0;
}

static int entity_SetProperty(lua_State *L)
{
    int n = lua_gettop(L);
    if (n != 3) {
        return luaL_error(L, "Entity::SetProperty(name, value) requires 2 parameters.");
    }
    Entity *entity = (Entity *)tolua_tousertype(L, 1, 0);
    const char *propName = tolua_tostring(L, 2, 0);
    switch (lua_type(L, 3)) {
    case LUA_TSTRING:
        entity->SetProperty(propName, TYPE_STRING, (void*)lua_tostring(L, 3));
        break;
    case LUA_TNUMBER: {
        float f = lua_tonumber(L, 3);
        entity->SetProperty(propName, TYPE_NUMBER, (void*)&f);
        break;
    }
    case LUA_TBOOLEAN: {
        bool b = lua_toboolean(L, 3);
        entity->SetProperty(propName, TYPE_BOOLEAN, (void*)&b);
        break;
    }
    case LUA_TUSERDATA: {
        if (lua_isusertype(L, 3, "Rect")) {
            entity->SetProperty(propName, TYPE_RECT, tolua_tousertype(L, 3, 0));
        } else if (lua_isusertype(L, 3, "Vector")) {
            entity->SetProperty(propName, TYPE_VECTOR, tolua_tousertype(L, 3, 0));
        } else {
            return luaL_error(L, "The type of the value passed must be one of: String, Number, Boolean, Rect, Vector");
        }
        break;
    }
    default:
        return luaL_error(L, "The type of the value passed must be one of: String, Number, Boolean, Rect, Vector");
    }
    return 0;
}

static int entity_GetProperty(lua_State *L)
{
    int n = lua_gettop(L);
    if (n != 2) {
        return luaL_error(L, "Entity::GetProperty(name) requires 1 parameter.");
    }
    Entity *entity = (Entity *)tolua_tousertype(L, 1, 0);
    const char *propName = tolua_tostring(L, 2, 0);
    const char *str;
    float f;
    bool b;
    Rect *r;
    Vector *v;
    if (entity->GetProperty(propName, str)) {
        lua_pushstring(L, str);
        return 1;
    } else if (entity->GetProperty(propName, f)) {
        lua_pushnumber(L, f);
        return 1;
    } else if (entity->GetProperty(propName, b)) {
        lua_pushboolean(L, b);
        return 1;
    } else if (entity->GetProperty(propName, r)) {
        tolua_pushusertype(L, (void*)r, "Rect");
        return 1;
    } else if (entity->GetProperty(propName, v)) {
        tolua_pushusertype(L, (void*)v, "Vector");
        return 1;
    } else {
        lua_pushnil(L);
        return 1;
    }
}

LuaScripting::LuaScripting()
 : Scripting(".lua")
{
    m_luaState = lua_open();

    luaL_openlibs(m_luaState);

    tolua_color_open(m_luaState);
    tolua_rect_open(m_luaState);
    tolua_vector_open(m_luaState);
    tolua_entity_open(m_luaState);

    lua_getglobal(m_luaState, "Entity");
    if (lua_istable(m_luaState, -1)) {
        if (lua_getmetatable(m_luaState, -1)) {
            lua_pushcfunction(m_luaState, entity_SetProperty);
            lua_setfield(m_luaState, -2, "SetProperty");
            lua_pushcfunction(m_luaState, entity_GetProperty);
            lua_setfield(m_luaState, -3, "GetProperty");
        }
    }
}

LuaScripting::~LuaScripting()
{
    lua_close(m_luaState);
}

Entity *LuaScripting::LoadEntity(const char *_entityFile)
{
    if (RunScript(_entityFile)) {
        lua_getglobal(m_luaState, "name");
        if (lua_isstring(m_luaState, -1)) {
            Entity *e = new Entity(0, lua_tostring(m_luaState, -1));
            Vector position;
            position.x = position.y = 100;
            position.z = 0;
            e->SetProperty("position", TYPE_VECTOR, (void*)&position);
            lua_pop(m_luaState, 1);
            lua_getglobal(m_luaState, "properties");
            if (lua_istable(m_luaState, -1)) {
                lua_pushnil(m_luaState);
                while(lua_next(m_luaState, -2) != 0) {
                    const char *propertyName = NULL;
                    if (!lua_isnumber(m_luaState, -2) && lua_isstring(m_luaState, -2)) {
                        propertyName = lua_tostring(m_luaState, -2);
                        int type = lua_type(m_luaState, -1);
                        if (propertyName != NULL) {
                            switch (type) {
                            case LUA_TSTRING:
                                e->SetProperty(propertyName, TYPE_STRING, (void*)lua_tostring(m_luaState, -1));
                                break;
                            case LUA_TNUMBER: {
                                float f = lua_tonumber(m_luaState, -1);
                                e->SetProperty(propertyName, TYPE_NUMBER, (void*)&f);
                                break;
                            }
                            case LUA_TBOOLEAN: {
                                bool b = lua_toboolean(m_luaState, -1);
                                e->SetProperty(propertyName, TYPE_BOOLEAN, (void*)&b);
                                break;
                            }
                            case LUA_TUSERDATA:
                                if (lua_isusertype(m_luaState, -1, "Rect")) {
                                    e->SetProperty(propertyName, TYPE_RECT, tolua_tousertype(m_luaState, -1, 0));
                                    break;
                                } else if (lua_isusertype(m_luaState, -1, "Vector")) {
                                    e->SetProperty(propertyName, TYPE_VECTOR, tolua_tousertype(m_luaState, -1, 0));
                                    break;
                                } else {
                                    g_console->WriteLine("WARN: Unknown property type detected, please fix.");
                                }
                                break;
                            default:
                                g_console->WriteLine("WARN: Property values must one of the following types: String, Number, Boolean, Rect, Vector");
                                break;
                            }
                        }
                    }
                    lua_pop(m_luaState, 1);
                }
            }
            lua_getglobal(m_luaState, "behaviors");
            if (lua_istable(m_luaState, -1)) { // -1 is the table
                // Loop through behaviors table
                lua_pushnil(m_luaState); // -1 is the first key
                while(lua_next(m_luaState, -2) != 0) { // -2: behaviors table
                    const char *behaviorName = NULL;
                    if (!lua_isnumber(m_luaState, -1) && lua_isstring(m_luaState, -1)) {
                        behaviorName = lua_tostring(m_luaState, -1);
                    } else if (!lua_isnumber(m_luaState, -2) && lua_isstring(m_luaState, -2)) {
                        behaviorName = lua_tostring(m_luaState, -2);
                    } else {
                        g_console->WriteLine("WARN: Non-string entry found in behaviors table, please fix.");
                    }
                    if (behaviorName != NULL) {
                        behaviorFunc f = get_behavior(behaviorName);
                        if (f == NULL) {
                            g_console->WriteLine("WARN: '%s' is not a registered behavior.", behaviorName);
                        } else {
                            e->AddBehavior(behaviorName, f);
                        }
                    }
                    lua_pop(m_luaState, 1);
                }
            }
            /* Look for input hooks */
            /* onKeyUp */
            lua_getglobal(m_luaState, "onKeyUp");
            if (lua_isfunction(m_luaState, -1)) {
                g_input->RegisterEventObserver(SDL_KEYUP, e);
            }
            /* onKeyDown */
            lua_getglobal(m_luaState, "onKeyDown");
            if (lua_isfunction(m_luaState, -1)) {
                g_input->RegisterEventObserver(SDL_KEYDOWN, e);
            }
            /* onMouseDown */
            lua_getglobal(m_luaState, "onMouseDown");
            if (lua_isfunction(m_luaState, -1)) {
                g_input->RegisterEventObserver(SDL_MOUSEBUTTONDOWN, e);
            }
            /* onMouseUp */
            lua_getglobal(m_luaState, "onMouseUp");
            if (lua_isfunction(m_luaState, -1)) {
                g_input->RegisterEventObserver(SDL_MOUSEBUTTONUP, e);
            }
            /* onMouseOver */
            lua_getglobal(m_luaState, "onMouseOver");
            if (lua_isfunction(m_luaState, -1)) {
                g_input->RegisterEventObserver(MOUSE_OVER, e);
            }
            /* onMouseLeave */
            lua_getglobal(m_luaState, "onMouseLeave");
            if (lua_isfunction(m_luaState, -1)) {
                g_input->RegisterEventObserver(MOUSE_LEAVE, e);
            }
            ResetEntityFileGlobals();
            return e;
        }
        ResetEntityFileGlobals();
        g_console->WriteLine("ERROR: Missing field: 'name'");
    }
    g_console->WriteLine("FAIL: Could not parse the entity file.");
    return NULL;
}

void LuaScripting::ResetEntityFileGlobals()
{
    /* name */
    lua_pushnil(m_luaState);
    lua_setglobal(m_luaState, "name");
    /* properties */
    lua_pushnil(m_luaState);
    lua_setglobal(m_luaState, "properties");
    /* behaviors */
    lua_pushnil(m_luaState);
    lua_setglobal(m_luaState, "behaviors");
    /* onKeyDown */
    lua_pushnil(m_luaState);
    lua_setglobal(m_luaState, "onKeyDown");
    /* onKeyUp */
    lua_pushnil(m_luaState);
    lua_setglobal(m_luaState, "onKeyUp");
    /* onMouseDown */
    lua_pushnil(m_luaState);
    lua_setglobal(m_luaState, "onMouseDown");
    /* onMouseUp */
    lua_pushnil(m_luaState);
    lua_setglobal(m_luaState, "onMouseUp");
    /* onMouseOver */
    lua_pushnil(m_luaState);
    lua_setglobal(m_luaState, "onMouseOver");
    /* onMouseLeave */
    lua_pushnil(m_luaState);
    lua_setglobal(m_luaState, "onMouseLeave");
}

bool LuaScripting::RunScript(const char *_scriptPath)
{
    char file[1024];
    strcpy(file, m_scriptDir);
    strcat(file, _scriptPath);
    strcat(file, m_extension);

    int lerr = luaL_loadfile(m_luaState, file);
    switch (lerr)
    {
    case 0: {
        int s = luaL_dofile(m_luaState, file);
        if (s != 0) {
            g_console->WriteLine("\nError occurred while trying to run Lua script.");
            g_console->WriteLine("  File: %s", file);
            g_console->WriteLine("  Error: %s\n", lua_tostring(m_luaState, -1));
            return false;
        } else {
            return true;
        }
    }
    case LUA_ERRSYNTAX:
        g_console->WriteLine("Lua script failed because of a syntax error.");
        return false;
    case LUA_ERRMEM:
        g_console->WriteLine("Lua script failed because of a memory error.");
        return false;
    }
    return false;
}

void LuaScripting::ExecuteHook(Entity *_entity, const char *_hook, int _value)
{
    tolua_pushusertype(m_luaState, (void*)_entity, "Entity");
    lua_setglobal(m_luaState, "entity");
    lua_pop(m_luaState, 1);
    if (RunScript(_entity->GetName())) {
        lua_getglobal(m_luaState, _hook);
        if (lua_isfunction(m_luaState, -1)) {
            lua_pushnumber(m_luaState, _value);
            if (!strcmp(_hook, "onMouseOver") || !strcmp(_hook, "onMouseLeave")) {
                lua_call(m_luaState, 0, 0);
            } else {
                lua_call(m_luaState, 1, 0);
            }
        }
    }
    ResetEntityFileGlobals();
}

lua_State *LuaScripting::GetState()
{
    return m_luaState;
}
