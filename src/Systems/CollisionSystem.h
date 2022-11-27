#ifndef A354F250_325A_430E_B435_8CB8F20038CD
#define A354F250_325A_430E_B435_8CB8F20038CD

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"
#include "../Logger/Logger.h"
#include <SDL2/SDL.h>

class RenderColliderSystem : public System {
   public:
    RenderColliderSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<BoxColliderComponent>();
    }

    void Update(SDL_Renderer* renderer, SDL_Rect& camera) {
        for (auto entity : GetSystemEntities()) {
            const auto transform = entity.GetComponent<TransformComponent>();
            const auto collider = entity.GetComponent<BoxColliderComponent>();

            SDL_Rect colliderRect = {
                static_cast<int>(transform.position.x + collider.offset.x) - camera.x,  //
                static_cast<int>(transform.position.y + collider.offset.y) - camera.y,  //
                static_cast<int>(collider.width),                                       //
                static_cast<int>(collider.height),                                      //
            };

            SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
            SDL_RenderDrawRect(renderer, &colliderRect);
        }
    }
};

class CollisionSystem : public System {
   public:
    CollisionSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<BoxColliderComponent>();
    }

    void Update(std::unique_ptr<EventBus>& eventBus) {
        auto entities = GetSystemEntities();

        // Loops all the enteties that the system is interested in
        for (auto a = entities.begin(); a != entities.end(); a++) {
            auto aTransform = (*a).GetComponent<TransformComponent>();
            auto aCollider = (*a).GetComponent<BoxColliderComponent>();

            // Loops all the enteties that still need to be checked "to the right of i"
            for (auto b = a; b != entities.end(); b++) {
                if ((*a) == (*b)) continue;  // ? If they are the same entity bypass the check

                auto bTransform = (*b).GetComponent<TransformComponent>();
                auto bCollider = (*b).GetComponent<BoxColliderComponent>();

                bool collisionOccured =
                    CheckAABBCollision(aTransform.position.x + aCollider.offset.x, aTransform.position.y + aCollider.offset.y,
                                       aCollider.width, aCollider.height, bTransform.position.x + bCollider.offset.x,
                                       bTransform.position.y + bCollider.offset.y, bCollider.width, bCollider.height);

                if (collisionOccured) {
                    // Logger::Debug("Entity " + std::to_string((*a).GetId()) + " is colliding with entity " +
                    // std::to_string((*b).GetId()));

                    eventBus->EmitEvent<CollisionEvent>((*a), (*b));
                }
            }
        }
    }

    bool CheckAABBCollision(double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH) {
        return (             //
            aX < bX + bW &&  //
            aX + aW > bX &&  //
            aY < bY + bH &&  //
            aY + aH > bY     //
        );
    }
};

#endif /* A354F250_325A_430E_B435_8CB8F20038CD */
