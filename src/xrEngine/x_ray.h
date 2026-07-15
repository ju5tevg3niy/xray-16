#pragma once
#include <SDL_surface.h>
#include <SDL_video.h>
#include <array>
#include <atomic>
#include <mutex>
#include <thread>
#include "Common/types.hpp"
#include "xrEngine/Engine.h"
#include "xrEngine/EngineAPI.h"

struct SDL_Window;
struct SDL_Surface;

namespace discord
{
class Core;
}

// definition
class CApplication final
{
    SDL_Window* m_window{};
    std::thread m_splash_thread;
    std::atomic_bool m_should_exit;

    SDL_Surface* m_surface;

private:
    std::mutex m_discord_lock;
    discord::Core* m_discord_core{};

private:
    GameModule* m_game_module{};

private:
    void SplashProc();

    void ShowSplash(bool topmost);
    void HideSplash();

    void InitializeDiscord();
    void UpdateDiscordStatus();

public:
    CApplication(pcstr commandLine, GameModule* game, const std::array<RendererModule*, 2>& modules);
    ~CApplication();

    int Run();
};
