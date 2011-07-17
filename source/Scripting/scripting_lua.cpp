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

#include "Input/input.h"
#include "Scripting/scripting_lua.h"

LuaScripting::LuaScripting()
 : Scripting(".lua")
{
    m_luaState = lua_open();

    luaL_openlibs(m_luaState);

    tolua_color_open(m_luaState);
    tolua_entity_open(m_luaState);
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
            g_console->WriteLine("Creating a new entity called %s.", lua_tostring(m_luaState, -1));
            Entity *e = new Entity(lua_tostring(m_luaState, -1));
            lua_pop(m_luaState, 1);
            lua_getglobal(m_luaState, "attributes");
            if (lua_istable(m_luaState, -1)) {
                lua_pushnil(m_luaState);
                while(lua_next(m_luaState, -2) != 0) {
                    const char *attributeName = NULL;
                    if (!lua_isnumber(m_luaState, -2) && lua_isstring(m_luaState, -2)) {
                        attributeName = lua_tostring(m_luaState, -2);
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
                        if (!strcmp(behaviorName, "input")) {
                            InputBehavior *b = new InputBehavior(e);
                            e->AddBehavior("input", b);
                        } else if (!strcmp(behaviorName, "physics")) {
                            PhysicsBehavior *b = new PhysicsBehavior(e);
                            if (lua_istable(m_luaState, -1)) {
                                lua_pushnil(m_luaState);
                                while(lua_next(m_luaState, -2) != 0) {
                                    if (lua_isnumber(m_luaState, -2)) {
                                        g_console->WriteLine("WARN: Numerical key found in physics table, please fix.");
                                    } else if (lua_isstring(m_luaState, -2)) {
                                        const char *key = lua_tostring(m_luaState, -2);
                                        if (!strcmp(key, "collidable")) {
                                            if (lua_isboolean(m_luaState, -1)) {
                                                b->SetCollidable(lua_toboolean(m_luaState, -1));
                                            } else {
                                                g_console->WriteLine("WARN: Expected a boolean value for 'collidable.'");
                                            }
                                        } else if (!strcmp(key, "gravity")) {
                                            if (lua_isnumber(m_luaState, -1)) {
                                                b->SetGravity((float)lua_tonumber(m_luaState, -1));
                                            } else {
                                                g_console->WriteLine("WARN: Expected a numerical value for 'gravity.'");
                                            }
                                        }
                                    } else {
                                        g_console->WriteLine("WARN: Non-string key found in physics table, please fix.");
                                    }
                                    lua_pop(m_luaState, 1);
                                }
                            }
                            e->AddBehavior("physics", b);
                        } else if (!strcmp(behaviorName, "render")) {
                            RenderBehavior *b = new RenderBehavior(e);
                            e->AddBehavior("render", b);
                        } else {
                            g_console->WriteLine("WARN: '%s' is not a valid behavior.", behaviorName);
                        }
                    }
                    lua_pop(m_luaState, 1);
                }
            } else {
                g_console->WriteLine("INFO: No behaviors table found.");
            }
            /* Look for input hooks */
            if (e->HasBehavior("input")) {
                InputBehavior *b = dynamic_cast<InputBehavior *>(e->GetBehavior(Behavior::Names[INPUT]));
                if (b != NULL) {
                    /* onKeyUp */
                    lua_getglobal(m_luaState, "onKeyUp");
                    if (lua_isfunction(m_luaState, -1)) {
                        g_input->RegisterEventObserver(SDL_KEYUP, b);
                        g_console->WriteLine("Registered onKeyUp.");
                    }
                    /* onKeyDown */
                    lua_getglobal(m_luaState, "onKeyDown");
                    if (lua_isfunction(m_luaState, -1)) {
                        g_input->RegisterEventObserver(SDL_KEYDOWN, b);
                        g_console->WriteLine("Registered onKeyDown.");
                    }
                    /* onMouseDown */
                    lua_getglobal(m_luaState, "onMouseDown");
                    if (lua_isfunction(m_luaState, -1)) {
                        g_input->RegisterEventObserver(SDL_MOUSEBUTTONDOWN, b);
                        g_console->WriteLine("Registered onMouseDown.");
                    }
                    /* onMouseUp */
                    lua_getglobal(m_luaState, "onMouseUp");
                    if (lua_isfunction(m_luaState, -1)) {
                        g_input->RegisterEventObserver(SDL_MOUSEBUTTONUP, b);
                        g_console->WriteLine("Registered onMouseUp.");
                    }
                    /* onMouseOver */
                    lua_getglobal(m_luaState, "onMouseOver");
                    if (lua_isfunction(m_luaState, -1)) {
                        g_input->RegisterEventObserver(MOUSE_OVER, b);
                        g_console->WriteLine("Registered onMouseOver.");
                    }
                    /* onMouseLeave */
                    lua_getglobal(m_luaState, "onMouseLeave");
                    if (lua_isfunction(m_luaState, -1)) {
                        g_input->RegisterEventObserver(MOUSE_LEAVE, b);
                        g_console->WriteLine("Registered onMouseLeave.");
                    }
                }
            }
            return e;
        }
        g_console->WriteLine("ERROR: Missing field: 'name'");
    }
    g_console->WriteLine("FAIL: Could not parse the entity file.");
    return NULL;
}

bool LuaScripting::RunScript(const char *_scriptPath)
{
    char file[1024];
    strcpy(file, m_scriptDir);
    strcat(file, _scriptPath);
    strcat(file, m_extension);

    int s = luaL_dofile(m_luaState, file);
    if (s != 0) {
        g_console->WriteLine("\nError occurred while trying to run Lua script.");
        g_console->WriteLine("  File: %s", file);
        g_console->WriteLine("  Error: %s\n", lua_tostring(m_luaState, -1));
        return false;
    }

    return true;
}

void LuaScripting::SendInput(Entity *_entity, const char *_hook, int _value)
{
    tolua_pushusertype(m_luaState, (void*)_entity, "Entity");
    lua_setglobal(m_luaState, "entity");
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
}

lua_State *LuaScripting::GetState()
{
    return m_luaState;
}


/**
 * Make a function call to lua
 * Example: CallFunction("aLuaFunction", "%d, %s", 4, "aString");
 */
/*
int LuaScripting::CallFunction(const char *_functionName, const char *_functionArgFormat, ...)
{
    lua_getglobal(m_luaState, _functionName);
    if (!lua_isfunction(m_luaState, -1)) {
        lua_pop(m_luaState, 1);
        return -1;
    }
    if (_functionArgFormat != NULL && *_functionArgFormat != '\0') {
        int argc = 0;
        size_t len = strlen(_functionArgFormat);
        for (int i = 0; i < len; i++) {
            if (_functionArgFormat[i] == '%') argc++;
        }
        if (argc > 0) {
            char *pch = strtok(_functionArgFormat, "%, ");
            va_list ap;
            va_start(ap, argc);
            while (pch != NULL) {
                if (pch[0] != NULL && pch[0] != '\0') {
                    switch (pch[0]) {
                    case 'n':
                        break;
                    case 's':
                        break;
                    case 'b':
                        break;
                    case 't':
                        break;
                    }
                }
                pch = strtok(NULL, "%, ");
            }
            va_end(ap);
        }
    }
}

int LuaScripting::CallFunction(const char *_functionName)
{
    return CallFunction(_functionName, NULL);
}

const char *LuaScripting::CallStringFunction(const char *_functionName)

*/
