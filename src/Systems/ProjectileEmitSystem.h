#ifndef B0E66255_6D42_4800_8519_577C05D38B1A
#define B0E66255_6D42_4800_8519_577C05D38B1A

#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Components/TransformComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class ProjectileEmitSystem : public System {
   public:
    ProjectileEmitSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<ProjectileEmitterComponent>();
    }

    void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
        eventBus->SubscribeToEvent<KeyEvent>(this, &ProjectileEmitSystem::onSpacePressed);
    }

    void onSpacePressed(KeyEvent& event) {
        if (event.currentKeyStates[SDL_SCANCODE_SPACE]) {
            for (auto entity : GetSystemEntities()) {
                if (entity.HasTag("player")) {
                    auto& projectileEmitter = entity.GetComponent<ProjectileEmitterComponent>();
                    const auto transform = entity.GetComponent<TransformComponent>();
                    const auto sprite = entity.GetComponent<SpriteComponent>();

                    if (SDL_GetTicks() - projectileEmitter.lastEmissionTime > projectileEmitter.repeatFrequency) {
                        glm::vec2 projectilePosition = transform.position;
                        projectilePosition.x += transform.scale.x * sprite.width / 2;
                        projectilePosition.y += transform.scale.y * sprite.height / 2;

                        glm::vec2 projectileVelocity = projectileEmitter.projectileVelocity;
                        int directionX = 0;
                        int directionY = 0;
                        if (sprite.srcRect.y / 32 == 1) directionX = +1;
                        if (sprite.srcRect.y / 32 == 3) directionX = -1;
                        if (sprite.srcRect.y / 32 == 2) directionY = +1;
                        if (sprite.srcRect.y / 32 == 0) directionY = -1;

                        projectileVelocity.x = projectileEmitter.projectileVelocity.x * directionX;
                        projectileVelocity.y = projectileEmitter.projectileVelocity.y * directionY;

                        Entity projectile = entity.registry->CreateEntity();
                        projectile.Group("projectiles");
                        projectile.AddComponent<TransformComponent>(projectilePosition, glm::vec2(1.0, 1.0), 0);
                        projectile.AddComponent<RigidbodyComponent>(projectileVelocity);
                        projectile.AddComponent<SpriteComponent>("bullet-texture", 4, 4, 20);
                        projectile.AddComponent<BoxColliderComponent>(4, 4);
                        projectile.AddComponent<ProjectileComponent>(projectileEmitter.isFriendly, projectileEmitter.hitPercentDamage,
                                                                     projectileEmitter.projectileDuration);

                        projectileEmitter.lastEmissionTime = SDL_GetTicks();
                    }
                }
            }
        }
    }

    void Update(std::unique_ptr<Registry>& registry) {
        for (auto entity : GetSystemEntities()) {
            const auto transform = entity.GetComponent<TransformComponent>();
            auto& projectileEmitter = entity.GetComponent<ProjectileEmitterComponent>();

            if (!projectileEmitter.isRepeat) continue;

            if (SDL_GetTicks() - projectileEmitter.lastEmissionTime > projectileEmitter.repeatFrequency) {
                glm::vec2 projectilePosition = transform.position;
                if (entity.HasComponent<SpriteComponent>()) {
                    auto sprite = entity.GetComponent<SpriteComponent>();
                    projectilePosition.x += transform.scale.x * sprite.width / 2;
                    projectilePosition.y += transform.scale.y * sprite.height / 2;
                }

                Entity projectile = registry->CreateEntity();
                projectile.Group("projectiles");
                projectile.AddComponent<TransformComponent>(projectilePosition, glm::vec2(1.0, 1.0), 0);
                projectile.AddComponent<RigidbodyComponent>(projectileEmitter.projectileVelocity);
                projectile.AddComponent<SpriteComponent>("bullet-texture", 4, 4, 20);
                projectile.AddComponent<BoxColliderComponent>(4, 4);
                projectile.AddComponent<ProjectileComponent>(projectileEmitter.isFriendly, projectileEmitter.hitPercentDamage,
                                                             projectileEmitter.projectileDuration);

                projectileEmitter.lastEmissionTime = SDL_GetTicks();
            }
        }
    }
};

#endif /* B0E66255_6D42_4800_8519_577C05D38B1A */
