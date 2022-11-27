#ifndef FD8FC11E_689E_405E_9CAB_1ED666DE71C4
#define FD8FC11E_689E_405E_9CAB_1ED666DE71C4

#include <glm/glm.hpp>

struct KeyboardControlledComponent {
    glm::vec2 upVelocity;
    glm::vec2 rightVelocity;
    glm::vec2 downVelocity;
    glm::vec2 leftVelocity;

    KeyboardControlledComponent(glm::vec2 upVelocity = glm::vec2(0), glm::vec2 rightVelocity = glm::vec2(0),
                                glm::vec2 downVelocity = glm::vec2(0), glm::vec2 leftVelocity = glm::vec2(0))
        : upVelocity(upVelocity), rightVelocity(rightVelocity), downVelocity(downVelocity), leftVelocity(leftVelocity) {}
};

#endif /* FD8FC11E_689E_405E_9CAB_1ED666DE71C4 */
