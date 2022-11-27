#ifndef AA8DF865_8098_4BF5_BB7E_EDF05A845276
#define AA8DF865_8098_4BF5_BB7E_EDF05A845276

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"

class MovementSystem : public System {
   public:
    MovementSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<RigidbodyComponent>();
    }

    void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
        eventBus->SubscribeToEvent<CollisionEvent>(this, &MovementSystem::onCollision);
    }

    void onCollision(CollisionEvent& event) {
        Entity a = event.a;
        Entity b = event.b;

        if (a.BelongsToGroup("enemies") && b.BelongsToGroup("obstacles")) {
            OnEnemyHitsObstacle(a, b);
        }

        if (b.BelongsToGroup("enemies") && a.BelongsToGroup("obstacles")) {
            OnEnemyHitsObstacle(b, a);
        }
    }

    void OnEnemyHitsObstacle(Entity enemy, Entity obstacle) {
        if (enemy.HasComponent<RigidbodyComponent>() && enemy.HasComponent<SpriteComponent>()) {
            auto& rigidbody = enemy.GetComponent<RigidbodyComponent>();
            auto& sprite = enemy.GetComponent<SpriteComponent>();

            if (rigidbody.velocity.x != 0) {
                rigidbody.velocity.x *= -1;
                sprite.flip = (sprite.flip == SDL_FLIP_NONE) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
            }

            if (rigidbody.velocity.y != 0) {
                rigidbody.velocity.y *= -1;
                sprite.flip = (sprite.flip == SDL_FLIP_NONE) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
            }
        }
    }

    void Update(double deltaTime) {
        for (auto entity : GetSystemEntities()) {
            auto& transform = entity.GetComponent<TransformComponent>();
            const auto rigidbody = entity.GetComponent<RigidbodyComponent>();

            transform.position.x += rigidbody.velocity.x * deltaTime;
            transform.position.y += rigidbody.velocity.y * deltaTime;

            if (entity.HasTag("player")) {
                int paddingLeft = 10;
                int paddingTop = 10;
                int paddingRight = 50;
                int paddingBottom = 50;

                transform.position.x = transform.position.x < paddingLeft ? paddingLeft : transform.position.x;
                transform.position.x =
                    transform.position.x > Game::mapWidth - paddingRight ? Game::mapWidth - paddingRight : transform.position.x;
                transform.position.y = transform.position.y < paddingTop ? paddingTop : transform.position.y;
                transform.position.y =
                    transform.position.y > Game::mapHeight - paddingBottom ? Game::mapHeight - paddingBottom : transform.position.y;
            }

            bool isEntityOutsideMap = (                   //
                transform.position.x < 0 ||               //
                transform.position.x > Game::mapWidth ||  //
                transform.position.y < 0 ||               //
                transform.position.y > Game::mapHeight    //
            );

            if (isEntityOutsideMap && !entity.HasTag("player")) {
                entity.Kill();
            }
        }
    }
};

#endif /* AA8DF865_8098_4BF5_BB7E_EDF05A845276 */
