#ifndef E7B9E941_D5B5_47A2_B627_8D6C62E2E087
#define E7B9E941_D5B5_47A2_B627_8D6C62E2E087

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../AssetManager/AssetManager.h"
#include <SDL2/SDL.h>

class RenderSystem : public System {
   public:
    RenderSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<SpriteComponent>();
    }

    void Update(SDL_Renderer* renderer, std::unique_ptr<AssetManager>& assetManager, const SDL_Rect& camera) {
        struct RenderableEntity {
            TransformComponent transformComponent;
            SpriteComponent spriteComponent;
        };

        std::vector<RenderableEntity> renderableEntities;
        for (auto entity : GetSystemEntities()) {
            RenderableEntity renderableEntity;
            renderableEntity.spriteComponent = entity.GetComponent<SpriteComponent>();
            renderableEntity.transformComponent = entity.GetComponent<TransformComponent>();

            bool isEntityOutsideCameraView = (  //
                renderableEntity.transformComponent.position.x +
                        (renderableEntity.transformComponent.scale.x * renderableEntity.spriteComponent.width) <
                    camera.x ||                                                          //
                renderableEntity.transformComponent.position.x > camera.x + camera.w ||  //
                renderableEntity.transformComponent.position.y +
                        (renderableEntity.transformComponent.scale.y * renderableEntity.spriteComponent.height) <
                    camera.y ||                                                       //
                renderableEntity.transformComponent.position.y > camera.y + camera.h  //
            );

            if (isEntityOutsideCameraView && !renderableEntity.spriteComponent.isFixed) continue;

            renderableEntities.emplace_back(renderableEntity);
        }

        std::sort(renderableEntities.begin(), renderableEntities.end(), [](const RenderableEntity& a, const RenderableEntity& b) {
            return a.spriteComponent.zIndex < b.spriteComponent.zIndex;  //
        });

        for (auto entity : renderableEntities) {
            const auto transform = entity.transformComponent;
            const auto sprite = entity.spriteComponent;

            SDL_Rect srcRect = sprite.srcRect;

            SDL_Rect dstRect = {
                static_cast<int>(transform.position.x - (sprite.isFixed ? 0 : camera.x)),  //
                static_cast<int>(transform.position.y - (sprite.isFixed ? 0 : camera.y)),  //
                static_cast<int>(sprite.width * transform.scale.x),                        //
                static_cast<int>(sprite.height * transform.scale.y)                        //
            };

            SDL_RenderCopyEx(                              //
                renderer,                                  //
                assetManager->GetTexture(sprite.assetId),  //
                &srcRect,                                  //
                &dstRect,                                  //
                transform.rotation,                        //
                NULL,                                      //
                sprite.flip                                //
            );
        }
    }
};

#endif /* E7B9E941_D5B5_47A2_B627_8D6C62E2E087 */