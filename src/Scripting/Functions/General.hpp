#pragma once
#include <lua.hpp>
#include "../../Client/GUI/Engine/Engine.hpp"
#include "../../Utils/Utils.cpp"
namespace General {
    int lua_Notify(lua_State* L) {
        const char* message = luaL_checkstring(L, 1);
        FlarialGUI::Notify(message);
        return 0;
    }

    int lua_getRoamingPath(lua_State* L) {
        std::string path = Utils::getRoamingPath() + "\\Flarial";
        lua_pushstring(L, path.c_str());
        return 1;
    }
    std::string keyCodeToInt(int* keyCode){
        std::string key = Utils::getKeyAsString(){
            
        }
    }

    void registerGeneral(lua_State* L){
        lua_register(L, "Notify", lua_Notify);
        lua_register(L, "getRoamingPath", lua_getRoamingPath);
    }
}
