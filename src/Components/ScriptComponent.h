#ifndef D48C3F7F_76D0_4EB7_9870_28610E60E811
#define D48C3F7F_76D0_4EB7_9870_28610E60E811

#include <sol/sol.hpp>

struct ScriptComponent {
    sol::function func;

    ScriptComponent(sol::function func = sol::lua_nil) : func(func) {}
};

#endif /* D48C3F7F_76D0_4EB7_9870_28610E60E811 */
