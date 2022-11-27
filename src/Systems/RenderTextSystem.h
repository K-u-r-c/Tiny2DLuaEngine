#ifndef DE9C1EF3_666C_40B8_BB28_A7C7AFD8C2F0
#define DE9C1EF3_666C_40B8_BB28_A7C7AFD8C2F0

#include "../ECS/ECS.h"
#include "../Components/TextLabelComponent.h"
#include "../AssetManager/AssetManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class RenderTextSystem : public System {
   public:
    RenderTextSystem() { RequireComponent<TextLabelComponent>(); }

    void Update(SDL_Renderer* renderer, std::unique_ptr<AssetManager>& assetManager, const SDL_Rect& camera) {
        for (auto entity : GetSystemEntities()) {
            const auto textLabel = entity.GetComponent<TextLabelComponent>();

            SDL_Surface* surface =
                TTF_RenderText_Blended(assetManager->GetFont(textLabel.assetId), textLabel.text.c_str(), textLabel.color);

            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            int labelWidth = 0;
            int labelHeight = 0;

            SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);

            SDL_Rect dstRect = {
                static_cast<int>(textLabel.position.x - (textLabel.isFixed ? 0 : camera.x)),  //
                static_cast<int>(textLabel.position.y - (textLabel.isFixed ? 0 : camera.y)),  //
                labelWidth,                                                                   //
                labelHeight                                                                   //
            };

            SDL_RenderCopy(renderer, texture, NULL, &dstRect);
            SDL_DestroyTexture(texture);
        }
    }
};

#endif /* DE9C1EF3_666C_40B8_BB28_A7C7AFD8C2F0 */
