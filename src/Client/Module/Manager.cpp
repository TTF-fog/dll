﻿#pragma once

#include "Manager.hpp"
#include "../Events/EventHandler.hpp"
#include "Modules/Input/GUIKeyListener.hpp"
#include "Modules/Misc/Uninject/Uninject.hpp"
#include "Modules/ClickGUI/ClickGUI.hpp"
#include "Modules/Module.hpp"
#include "Modules/FPS/FPSCounter.hpp"
#include "Modules/CPS/CPSCounter.hpp"
#include "Modules/Zoom/Zoom.hpp"
#include "Modules/Time/Time.hpp"
#include "Modules/Memory/Memory.hpp"
#include "Modules/Sprint/Sprint.hpp"
#include "Modules/Fullbright/Fullbright.hpp"
#include "Modules/Deepfry/Deepfry.hpp"
#include "Modules/ForceCoords/ForceCoords.hpp"


namespace ModuleManager {
    std::vector<Module*> modules;
}

void ModuleManager::initialize()
{
    modules.push_back(new Deepfry());
    modules.push_back(new ClickGUI());
    modules.push_back(new Zoom());
    modules.push_back(new FPSCounter());
    modules.push_back(new CPSCounter());

    modules.push_back(new Time());
    modules.push_back(new MEM());
    modules.push_back(new Sprint());
    modules.push_back(new Fullbright());
    modules.push_back(new ForceCoords());

    EventHandler::registerListener(new GUIKeyListener("E"));
    EventHandler::registerListener(new UninjectListener("Uninject"));
}

void ModuleManager::terminate()
{
    for (Module* module : modules) {
        module->onDisable();
    }

    modules.clear();
}

Module* ModuleManager::getModule(std::string name)
{
    for (Module* mod : modules) {
        if (mod->name == name) {
            return mod;

        }
    }

    return nullptr;
}
