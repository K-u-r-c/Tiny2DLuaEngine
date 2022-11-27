#ifndef DBAB4E7C_F93C_4CBA_A3A7_59B1FB91A911
#define DBAB4E7C_F93C_4CBA_A3A7_59B1FB91A911

#include <glm/glm.hpp>

struct RigidbodyComponent {
    glm::vec2 velocity;

    RigidbodyComponent(glm::vec2 velocity = glm::vec2(0.0, 0.0)) : velocity(velocity) {}
};

#endif /* DBAB4E7C_F93C_4CBA_A3A7_59B1FB91A911 */
