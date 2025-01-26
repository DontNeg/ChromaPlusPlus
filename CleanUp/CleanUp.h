#pragma once
#include <string>
#include <vector>
#include "dpp/dpp.h"

const static std::map<std::string, int> colorOptions = {{"gray", 30}, {"red", 31}, {"green", 32}, {"orange", 33}, {"blue", 34}, {"pink", 35}, {"cyan", 36}, {"white", 37}};
const static std::map<std::string, int> bgColors = {{"dark blue", 40}, {"orange", 41}, {"even darker gray", 42}, {"dark gray", 43}, {"gray", 44}, {"purple", 45}, {"light gray", 46}, {"white", 47}};
const static std::map<std::string, std::string> modifierOptions = {{"bold", "**"}, {"italic", "*"}, {"strikethrough", "~~"}, {"underline", "__"}};
const static std::map<std::string, std::string> headerTypes = {{"small", "###"}, {"medium", "##"}, {"large", "#"}};

class CleanUp {
public:
    static std::string getMessage(const std::string& bgColor, const std::string& color, const std::string& text);
    static std::string modify(const std::string& msg, const std::vector<std::string>& modifiers);
    static void addChoice(dpp::command_option& commandOption, const std::string& choice);
};