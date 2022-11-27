#ifndef A1D6873D_BF9A_4276_A179_54E9C4C3D09B
#define A1D6873D_BF9A_4276_A179_54E9C4C3D09B

#include <memory>
#include <SDL2/SDL.h>
#include <sol/sol.hpp>
#include "../ECS/ECS.h"
#include "../AssetManager/AssetManager.h"

class LevelLoader {
   public:
    LevelLoader();
    ~LevelLoader();

    void LoadLevel(sol::state& lua, const std::unique_ptr<Registry>& registry, const std::unique_ptr<AssetManager>& assetManager,
                   SDL_Renderer* renderer, std::string gamePath, int levelNumber);
};

#endif /* A1D6873D_BF9A_4276_A179_54E9C4C3D09B */
