#include "CleanUp.h"
#include "../Main/main.h"

using namespace std;

string CleanUp::getMessage(const string& bgColor, const string& color, const string& text) {
    return string("```ansi\n\u001b[") + to_string(bgColors.at(bgColor)) + ";" + to_string(colorOptions.at(color)) + "m" + text + "\n```";
}

string CleanUp::modify(const string& msg, const vector<string>& modifiers) {
    set<string> mods = {};
    string message = msg;
    for(const string& modifier: modifiers) {
        if (!mods.contains(modifier)) {
            string modText = modifierOptions.at(modifier);
            message = modText.append(message).append(modText);
        }
        mods.insert(modifier);
    }
    return message;
}

void CleanUp::addChoice(dpp::command_option& commandOption, const string& choice) {
    commandOption = commandOption.add_choice(dpp::command_option_choice(choice, choice));
}