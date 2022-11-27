#ifndef C89CFD6E_4BB5_4387_A363_CFDAF776F192
#define C89CFD6E_4BB5_4387_A363_CFDAF776F192

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/HealthComponent.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"

#include "../Logger/Logger.h"

class DamageSystem : public System {
   public:
    DamageSystem() { RequireComponent<BoxColliderComponent>(); }

    void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
        eventBus->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::onCollision);
    }

    void onCollision(CollisionEvent& event) {
        Entity a = event.a;
        Entity b = event.b;

        // Projectile hit player
        if (a.BelongsToGroup("projectiles") && b.HasTag("player")) {
            OnProjectileHitsPlayer(a, b);
        }

        if (b.BelongsToGroup("projectiles") && a.HasTag("player")) {
            OnProjectileHitsPlayer(b, a);
        }

        if (a.BelongsToGroup("projectiles") && b.BelongsToGroup("enemies")) {
            OnProjectileHitsEnemy(a, b);
        }

        if (b.BelongsToGroup("projectiles") && a.BelongsToGroup("enemies")) {
            OnProjectileHitsEnemy(b, a);
        }
    }

    void OnProjectileHitsPlayer(Entity projectile, Entity player) {
        const auto projectileComponent = projectile.GetComponent<ProjectileComponent>();

        if (!projectileComponent.isFriendly) {
            auto& health = player.GetComponent<HealthComponent>();

            health.healthPercentage -= projectileComponent.hitPercentDamage;
            Logger::Warning("Player has been hit for: " + std::to_string(projectileComponent.hitPercentDamage) + " damage");

            if (health.healthPercentage <= 0) {
                player.Kill();
                Logger::Error("Player has been killed !");
            }

            projectile.Kill();
        }
    }

    void OnProjectileHitsEnemy(Entity projectile, Entity enemy) {
        const auto projectileComponent = projectile.GetComponent<ProjectileComponent>();

        if (projectileComponent.isFriendly) {
            auto& health = enemy.GetComponent<HealthComponent>();

            health.healthPercentage -= projectileComponent.hitPercentDamage;
            Logger::Debug("Enemy has been hit for: " + std::to_string(projectileComponent.hitPercentDamage) + " damage");

            if (health.healthPercentage <= 0) {
                enemy.Kill();
            }
            projectile.Kill();
        }
    }

    void Update() {}
};

#endif /* C89CFD6E_4BB5_4387_A363_CFDAF776F192 */
