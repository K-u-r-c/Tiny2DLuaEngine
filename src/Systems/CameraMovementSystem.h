#ifndef C1C8FD34_338B_427E_AB47_35A28B01CF8B
#define C1C8FD34_338B_427E_AB47_35A28B01CF8B

#include "../ECS/ECS.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Game/Game.h"
#include <SDL2/SDL.h>

class CameraMovementSystem : public System {
   public:
    CameraMovementSystem() {
        RequireComponent<CameraFollowComponent>();
        RequireComponent<TransformComponent>();
        RequireComponent<SpriteComponent>();
    }

    void Update(SDL_Rect& camera) {
        for (auto entity : GetSystemEntities()) {
            auto transform = entity.GetComponent<TransformComponent>();
            auto sprite = entity.GetComponent<SpriteComponent>();

            if (transform.position.x + (camera.w / 2) < Game::mapWidth) {
                camera.x = transform.position.x - (Game::windowWidth / 2) + (sprite.width / 2);
            }

            if (transform.position.y + (camera.h / 2) < Game::mapHeight) {
                camera.y = transform.position.y - (Game::windowHeight / 2) + (sprite.height / 2);
            }

            camera.x = camera.x < 0 ? 0 : camera.x;
            camera.y = camera.y < 0 ? 0 : camera.y;

            camera.x = camera.x > camera.w ? camera.w : camera.x;
            camera.y = camera.y > camera.h ? camera.h : camera.y;
        }
    }
};

#endif /* C1C8FD34_338B_427E_AB47_35A28B01CF8B */
