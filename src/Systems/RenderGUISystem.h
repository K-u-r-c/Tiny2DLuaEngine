#ifndef A2831CC1_8B28_4498_89FD_057D7C34A044
#define A2831CC1_8B28_4498_89FD_057D7C34A044

#include "../ECS/ECS.h"

#include <memory>

#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include <imgui/imgui_impl_sdl.h>
#include "../Logger/Logger.h"

#include "../Components/TransformComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/HealthComponent.h"

class RenderGUISystem : public System {
   public:
    RenderGUISystem() = default;

    void Update(const std::unique_ptr<Registry>& registry, const SDL_Rect& camera) {
        ImGui::NewFrame();

        /* ImGuiWindowFlags setupFlags = ImGuiWindowFlags_AlwaysAutoResize;
        if (ImGui::Begin("Spawn enemies", NULL, setupFlags)) {
            static int posX = 0;
            static int posY = 0;
            static int scaleX = 1;
            static int scaleY = 1;
            static int velX = 0;
            static int velY = 0;
            static float rotation = 0.0;
            static float projAngle = 0.0;
            static float projSpeed = 100.0;
            static int projRepeat = 10;
            static int projDuration = 10;
            static char* sprites[] = {(char*)"tank-image", (char*)"truck-image"};
            static int selectedSpriteIndex = 0;
            static int health = 100;

            // Section to input enemy sprite texture id
            if (ImGui::CollapsingHeader("Sprite", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::Combo("Texture id", &selectedSpriteIndex, sprites, IM_ARRAYSIZE(sprites));
            }

            ImGui::Spacing();
            if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::InputInt("Position X", &posX);
                ImGui::InputInt("Position Y", &posY);
                ImGui::SliderInt("Scale X", &scaleX, 1, 10);
                ImGui::SliderInt("Scale Y", &scaleY, 1, 10);
                ImGui::SliderAngle("Rotation", &rotation, 0, 360);
            }
            ImGui::Spacing();

            if (ImGui::CollapsingHeader("Rigidbody", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::InputInt("Velocity X", &velX);
                ImGui::InputInt("Velocity Y", &velY);
            }
            ImGui::Spacing();

            if (ImGui::CollapsingHeader("Projectile emitter", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::SliderAngle("Angle", &projAngle, 0, 360);
                ImGui::SliderFloat("Speed", &projSpeed, 10, 500);
                ImGui::InputInt("Repeat time", &projRepeat);
                ImGui::InputInt("Duration", &projDuration);
            }
            ImGui::Spacing();

            if (ImGui::CollapsingHeader("Health", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::SliderInt("Health %", &health, 0, 100);
            }

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            if (ImGui::Button("Spawn")) {
                Entity enemy = registry->CreateEntity();
                enemy.Group("enemies");
                enemy.AddComponent<TransformComponent>(glm::vec2(posX, posY), glm::vec2(scaleX, scaleY), glm::degrees(rotation));
                enemy.AddComponent<RigidbodyComponent>(glm::vec2(velX, velY));
                enemy.AddComponent<SpriteComponent>(sprites[selectedSpriteIndex], 32, 32, 2);
                enemy.AddComponent<BoxColliderComponent>(25, 20, glm::vec2(5, 5));
                double projVelX = cos(projAngle) * projSpeed;
                double projVelY = sin(projAngle) * projSpeed;
                enemy.AddComponent<ProjectileEmitterComponent>(glm::vec2(projVelX, projVelY), projRepeat * 1000, projDuration * 1000, 10,
                                                               false);
                enemy.AddComponent<HealthComponent>(health);
            }
        }
        ImGui::End(); */

        // Display a small overlay window to display the map position using the mouse
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoNav;
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always, ImVec2(0, 0));
        ImGui::SetNextWindowBgAlpha(0.9f);
        if (ImGui::Begin("Map coordinates", NULL, windowFlags)) {
            ImGui::Text("Map coordinates (x=%.1f, y=%.1f)", ImGui::GetIO().MousePos.x + camera.x, ImGui::GetIO().MousePos.y + camera.y);
        }
        ImGui::End();

        Logger::ShowLogger();

        // ImGui::ShowDemoWindow();

        ImGui::Render();
        ImGuiSDL::Render(ImGui::GetDrawData());
    }
};

#endif /* A2831CC1_8B28_4498_89FD_057D7C34A044 */
