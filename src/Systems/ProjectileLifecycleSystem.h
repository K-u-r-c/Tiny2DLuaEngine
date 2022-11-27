#ifndef C7FE794B_D7C5_4041_9EC1_997414E58019
#define C7FE794B_D7C5_4041_9EC1_997414E58019

#include "../ECS/ECS.h"
#include "../Components/ProjectileComponent.h"
#include <SDL2/SDL.h>

class ProjectileLifecycleSystem : public System {
   public:
    ProjectileLifecycleSystem() { RequireComponent<ProjectileComponent>(); }

    void Update() {
        for (auto entity : GetSystemEntities()) {
            auto projectile = entity.GetComponent<ProjectileComponent>();

            if (SDL_GetTicks() - projectile.startTime > projectile.duration) {
                entity.Kill();
            }
        }
    }
};

#endif /* C7FE794B_D7C5_4041_9EC1_997414E58019 */
