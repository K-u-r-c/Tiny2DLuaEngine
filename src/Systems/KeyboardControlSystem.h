#ifndef B48F3FE5_914A_43DA_A151_254A84C89359
#define B48F3FE5_914A_43DA_A151_254A84C89359

#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/KeyEvent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/KeyboardControlledComponent.h"

class KeyboardControlSystem : public System {
   public:
    KeyboardControlSystem() {
        RequireComponent<SpriteComponent>();
        RequireComponent<RigidbodyComponent>();
        RequireComponent<KeyboardControlledComponent>();
    }

    void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
        eventBus->SubscribeToEvent<KeyEvent>(this, &KeyboardControlSystem::onKeyPressed);
    }

    void onKeyPressed(KeyEvent& event) {
        for (auto entity : GetSystemEntities()) {
            auto& sprite = entity.GetComponent<SpriteComponent>();
            auto& rigidbody = entity.GetComponent<RigidbodyComponent>();
            const auto keyboardcontrol = entity.GetComponent<KeyboardControlledComponent>();

            if (event.currentKeyStates[SDL_SCANCODE_UP]) {
                rigidbody.velocity = keyboardcontrol.upVelocity;
                sprite.srcRect.y = sprite.height * 0;
            }

            if (event.currentKeyStates[SDL_SCANCODE_RIGHT]) {
                rigidbody.velocity = keyboardcontrol.rightVelocity;
                sprite.srcRect.y = sprite.height * 1;
            }

            if (event.currentKeyStates[SDL_SCANCODE_DOWN]) {
                rigidbody.velocity = keyboardcontrol.downVelocity;
                sprite.srcRect.y = sprite.height * 2;
            }

            if (event.currentKeyStates[SDL_SCANCODE_LEFT]) {
                rigidbody.velocity = keyboardcontrol.leftVelocity;
                sprite.srcRect.y = sprite.height * 3;
            }

            if (!event.currentKeyStates[SDL_SCANCODE_LEFT] && !event.currentKeyStates[SDL_SCANCODE_RIGHT]) {
                rigidbody.velocity = glm::vec2(0.0, rigidbody.velocity.y);
            }

            if (!event.currentKeyStates[SDL_SCANCODE_DOWN] && !event.currentKeyStates[SDL_SCANCODE_UP]) {
                rigidbody.velocity = glm::vec2(rigidbody.velocity.x, 0.0);
            }
        }
    }

    void Update() {}
};

#endif /* B48F3FE5_914A_43DA_A151_254A84C89359 */
