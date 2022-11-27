#ifndef C780DC6A_7023_4F4C_B219_493B0CE620ED
#define C780DC6A_7023_4F4C_B219_493B0CE620ED

#include <SDL2/SDL.h>
#include <memory>
#include <sol/sol.hpp>
#include "../ECS/ECS.h"
#include "../AssetManager/AssetManager.h"
#include "../EventBus/EventBus.h"

// const int FPS = 60;
// const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game {
   private:
    bool isRunning;
    bool isDebug;
    int millisecsPreviousFrame = 0;
    std::string gamePath;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect camera;

    sol::state lua;
    std::unique_ptr<Registry> registry;
    std::unique_ptr<AssetManager> assetManager;
    std::unique_ptr<EventBus> eventBus;

   public:
    Game(std::string gamePath);
    ~Game();

    void Initialize();
    void Run();
    void Setup();
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();

    static int windowWidth;
    static int windowHeight;
    static int mapWidth;
    static int mapHeight;
};

#endif /* C780DC6A_7023_4F4C_B219_493B0CE620ED */
