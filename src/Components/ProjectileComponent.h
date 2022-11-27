#ifndef D60BE558_F6E0_4102_AECF_E8292A30FFDD
#define D60BE558_F6E0_4102_AECF_E8292A30FFDD

#include <SDL2/SDL.h>

struct ProjectileComponent {
    bool isFriendly;
    int hitPercentDamage;
    int duration;
    int startTime;

    ProjectileComponent(bool isFriendly = false, int hitPercentDamage = 0, int duration = 0)
        : isFriendly(isFriendly), hitPercentDamage(hitPercentDamage), duration(duration) {
        this->startTime = SDL_GetTicks();
    }
};

#endif /* D60BE558_F6E0_4102_AECF_E8292A30FFDD */
