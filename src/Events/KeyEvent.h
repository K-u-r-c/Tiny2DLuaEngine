#ifndef AB1397CA_2072_4E6E_A592_880BC3963D28
#define AB1397CA_2072_4E6E_A592_880BC3963D28

#include "../EventBus/Event.h"
#include <SDL2/SDL.h>

class KeyEvent : public Event {
   public:
    const Uint8* currentKeyStates;
    KeyEvent(const Uint8* currentKeyStates) : currentKeyStates(currentKeyStates) {}
};

#endif /* AB1397CA_2072_4E6E_A592_880BC3963D28 */
