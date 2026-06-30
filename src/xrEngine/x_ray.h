#include <thread>
#include "Common/types.hpp"
#include <atomic>
#pragma once

#include <mutex>
#include <array>

#include "xrEngine/Engine.h"

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
    // Other
    CApplication(pcstr commandLine, GameModule* game, const std::array<RendererModule*, 2>& modules);
    ~CApplication();

    int Run();
};
