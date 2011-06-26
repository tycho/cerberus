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

#include "Scripting/scripting_lua.h"

LuaScripting::LuaScripting()
 : Scripting(".lua")
{
    m_luaState = lua_open();

    luaL_openlibs(m_luaState);
}

LuaScripting::~LuaScripting()
{
    lua_close(m_luaState);
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
