#ifndef DF3CF3CA_CC27_4C06_A471_D664D9D4A77E
#define DF3CF3CA_CC27_4C06_A471_D664D9D4A77E

#include <string>
#include <SDL2/SDL.h>

struct SpriteComponent {
    std::string assetId;
    int width;
    int height;
    int zIndex;
    bool isFixed;
    SDL_RendererFlip flip;
    SDL_Rect srcRect;

    SpriteComponent(std::string assetId = "", int width = 0, int height = 0, int zIndex = 0, bool isFixed = false, int srcRectX = 0,
                    int srcRectY = 0)
        : assetId(assetId), width(width), height(height), zIndex(zIndex), isFixed(isFixed) {
        this->flip = SDL_FLIP_NONE;
        this->srcRect = {srcRectX, srcRectY, width, height};
    }
};

#endif /* DF3CF3CA_CC27_4C06_A471_D664D9D4A77E */
