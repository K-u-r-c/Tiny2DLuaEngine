#ifndef A15F927A_0D31_454D_937F_E1333B374CF9
#define A15F927A_0D31_454D_937F_E1333B374CF9

#include <glm/glm.hpp>

struct BoxColliderComponent {
    int width;
    int height;
    glm::vec2 offset;

    BoxColliderComponent(int width = 0, int height = 0, glm::vec2 offset = glm::vec2(0.0)) : width(width), height(height), offset(offset) {}
};

#endif /* A15F927A_0D31_454D_937F_E1333B374CF9 */
