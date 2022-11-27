#ifndef FCB91C4A_37AD_47D0_B53A_20A62587B91D
#define FCB91C4A_37AD_47D0_B53A_20A62587B91D

#include <glm/glm.hpp>

struct TransformComponent {
    glm::vec2 position;
    glm::vec2 scale;
    double rotation;

    TransformComponent(glm::vec2 position = glm::vec2(0.0, 0.0), glm::vec2 scale = glm::vec2(1.0, 1.0), double rotation = 0.0)
        : position(position), scale(scale), rotation(rotation) {}
};

#endif /* FCB91C4A_37AD_47D0_B53A_20A62587B91D */
