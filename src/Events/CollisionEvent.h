#ifndef BC19FF2F_EE81_480D_84BC_5101826564A8
#define BC19FF2F_EE81_480D_84BC_5101826564A8

#include "../ECS/ECS.h"
#include "../EventBus/Event.h"

class CollisionEvent : public Event {
   public:
    Entity a;
    Entity b;
    CollisionEvent(Entity a, Entity b) : a(a), b(b) {}
};

#endif /* BC19FF2F_EE81_480D_84BC_5101826564A8 */
