#ifndef D2AF2515_4926_4681_B9B3_4848203717F8
#define D2AF2515_4926_4681_B9B3_4848203717F8

#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include <imgui/imgui_impl_sdl.h>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>

struct Logger {
    ImVector<char*> Items;
    ImGuiTextFilter Filter;
    static std::vector<std::string> messages;
    bool AutoScroll;

    Logger();
    ~Logger();

    // Helper functions
    static char* Strdup(const char* s);
    // End helper functions

    void ClearLog();
    void AddLog(const char* fmt, ...) IM_FMTARGS(2);
    void Draw(const char* title);
    static void Debug(const std::string& message);
    static void Warning(const std::string& message);
    static void Error(const std::string& message);
    static void ShowLogger();
};

#endif /* D2AF2515_4926_4681_B9B3_4848203717F8 */
