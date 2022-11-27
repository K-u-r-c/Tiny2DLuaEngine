#ifndef C13C08BD_E8A1_4F14_AD91_8AF5BC747E28
#define C13C08BD_E8A1_4F14_AD91_8AF5BC747E28

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

struct ProjectileEmitterComponent {
    glm::vec2 projectileVelocity;
    double repeatFrequency;
    int projectileDuration;
    int hitPercentDamage;
    bool isFriendly;
    int lastEmissionTime;
    static int projectileNum;
    bool isRepeat;

    ProjectileEmitterComponent(glm::vec2 projectileVelocity = glm::vec2(0), double repeatFrequency = 0.0, int projectileDuration = 10000,
                               int hitPercentDamage = 10, bool isFriendly = false, bool isRepeat = true)
        : projectileVelocity(projectileVelocity),
          repeatFrequency(repeatFrequency),
          projectileDuration(projectileDuration),
          hitPercentDamage(hitPercentDamage),
          isFriendly(isFriendly),
          isRepeat(isRepeat) {
        this->lastEmissionTime = SDL_GetTicks();
    }
};

#endif /* C13C08BD_E8A1_4F14_AD91_8AF5BC747E28 */
