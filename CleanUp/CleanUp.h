#pragma once
#include <string>
#include <vector>
#include "dpp/dpp.h"

class CleanUp {
public:
    static std::string getMessage(const std::string& bgColor, const std::string& color, const std::string& text);
    static int backgroundColor(const std::string& bgColor);
    static int mainColor(const std::string& color);
    static std::string mainModifier(const std::string& msg, const std::string& modifier);
    static std::string modify(const std::string& msg, const std::vector<std::string>& modifiers);
    static std::string header(const std::string& msg, const std::string& size);
    static void addChoice(dpp::command_option& commandOption, const std::string& choice);
};