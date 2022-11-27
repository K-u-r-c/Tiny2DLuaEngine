#include "Logger.h"

static std::string CurrentDateTimeToString() {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string output(30, '\0');
    std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now));

    return output;
}

std::vector<std::string> Logger::messages;

Logger::Logger() {
    ClearLog();
    AutoScroll = true;
}

Logger::~Logger() { ClearLog(); }

// Helper functions
char* Logger::Strdup(const char* s) {
    size_t len = strlen(s) + 1;
    void* buf = malloc(len);
    IM_ASSERT(buf);
    return (char*)memcpy(buf, (const void*)s, len);
}
// End helper functions

void Logger::ClearLog() {
    for (int i = 0; i < Items.Size; i++) free(Items[i]);
    Items.clear();
    messages.clear();
}

void Logger::AddLog(const char* fmt, ...) {
    // FIXME-OPT
    char buf[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
    buf[IM_ARRAYSIZE(buf) - 1] = 0;
    va_end(args);
    Items.push_back(Strdup(buf));
}

void Logger::Draw(const char* title) {
    if (ImGui::Begin(title, NULL)) {
        if (ImGui::Button("Clear")) {
            ClearLog();
        }

        ImGui::SameLine();
        bool copy_to_clipboard = ImGui::Button("Copy");

        ImGui::SameLine();
        if (ImGui::BeginPopup("Options")) {
            ImGui::Checkbox("Auto-scroll", &AutoScroll);
            ImGui::EndPopup();
        }

        ImGui::SameLine();
        if (ImGui::Button("Options")) ImGui::OpenPopup("Options");
        ImGui::SameLine();
        Filter.Draw("Filter", 180);
        ImGui::Separator();

        ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
        if (ImGui::BeginPopupContextWindow()) {
            if (ImGui::Selectable("Clear")) ClearLog();
            ImGui::EndPopup();
        }

        if (copy_to_clipboard) ImGui::LogToClipboard();
        for (int i = 0; i < Items.Size; i++) {
            const char* item = Items[i];
            if (!Filter.PassFilter(item)) continue;

            // Normally you would store more information in your item than just a string.
            // (e.g. make Items[] an array of structure, store color/type etc.)
            ImVec4 color;
            if (strstr(item, "[ERROR]")) {
                color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f);
            } else if (strstr(item, "[WARNING]")) {
                color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
            } else {
                color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            }
            ImGui::PushStyleColor(ImGuiCol_Text, color);
            ImGui::TextUnformatted(item);
            ImGui::PopStyleColor();
        }
        if (copy_to_clipboard) ImGui::LogFinish();

        if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) ImGui::SetScrollHereY(1.0f);

        ImGui::EndChild();

        ImGui::End();
    } else {
        ImGui::End();
        return;
    }
}

void Logger::Debug(const std::string& message) {
    std::string date = CurrentDateTimeToString();
    date.erase(std::find(date.begin(), date.end(), '\0'), date.end());
    std::string msg = "[DEBUG] " + date + ": " + message;
    messages.push_back(msg);
}

void Logger::Warning(const std::string& message) {
    std::string date = CurrentDateTimeToString();
    date.erase(std::find(date.begin(), date.end(), '\0'), date.end());
    std::string msg = "[WARNING] " + date + ": " + message;
    messages.push_back(msg);
}

void Logger::Error(const std::string& message) {
    std::string date = CurrentDateTimeToString();
    date.erase(std::find(date.begin(), date.end(), '\0'), date.end());
    std::string msg = "[ERROR] " + date + ": " + message;
    messages.push_back(msg);
}

void Logger::ShowLogger() {
    static Logger logger;

    for (auto msg : logger.messages) {
        logger.AddLog("%s", msg.c_str());
    }
    logger.messages.clear();

    logger.Draw("Logger");
}