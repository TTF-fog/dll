#pragma once
#include <windows.h>
#include "src/Client/Client.hpp"
#include "src/Client/Events/EventHandler.hpp"
#include "src/Client/GUI/D2D.hpp"
#include <kiero.h>

DWORD WINAPI init(HMODULE real)
{

    Client::initialize();
    Logger::info("Initializing Client");

    while (true) {
        if (Client::disable) {
            break;
        } else {
            Sleep(50);
        }
    }

    Logger::info("Uninitializing Client");

    EventHandler::unregisterAll();


        D2D::context->Release();
        D2D::context = nullptr;
        Logger::debug("Freed context.");

    ModuleManager::terminate();
    HookManager::terminate();

    kiero::shutdown();

    Logger::debug("Shut down Kiero.");


    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();

    Logger::debug("Freeing Library.");

    FreeLibraryAndExitThread(real, 1);
}

BOOL APIENTRY DllMain(HMODULE instance, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)init, instance, 0, nullptr);
        break;
    }

    return TRUE;
}