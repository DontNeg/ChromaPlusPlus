#include "CleanUp.h"
#include "../Main/main.h"

using namespace std;

string CleanUp::getMessage(const string& bgColor, const string& color, const string& text) {
    return string("```ansi\n\u001b[") + to_string(backgroundColor(bgColor)) + ";" + to_string(mainColor(color)) + "m" + text + "\n```";
}

int CleanUp::backgroundColor(const string& bgColor) {
    int bgColorReturnable;
    switch(main::stoa(bgColor)) {
        case 874: { //Dark Blue
            bgColorReturnable = 40;
            break;
        }
        case 636: { //Orange
            bgColorReturnable = 41;
            break;
        }
        case 1562: { //Even Darker Grey
            bgColorReturnable = 42;
            break;
        }
        case 885: { //Dark Grey
            bgColorReturnable = 43;
            break;
        }
        case 435: { //Grey
            bgColorReturnable = 44;
            break;
        }
        case 664: { //Purple
            bgColorReturnable = 45;
            break;
        }
        case 1003: { //Light Grey
            bgColorReturnable = 46;
            break;
        }
        case 545: { //White
            bgColorReturnable = 47;
            break;
        }
        default: {
            bgColorReturnable = 0;
            break;
        }
    }
    return bgColorReturnable;
}

int CleanUp::mainColor(const string& color) {
    int colorReturnable;
    switch(main::stoa(color)) {
        case 435: { //Grey
            colorReturnable = 30;
            break;
        }
        case 315: { //Red
            colorReturnable = 31;
            break;
        }
        case 529: { //Green
            colorReturnable = 32;
            break;
        }
        case 636: { //Orange
            colorReturnable = 33;
            break;
        }
        case 424: { //Blue
            colorReturnable = 34;
            break;
        }
        case 434: { //Pink
            colorReturnable = 35;
            break;
        }
        case 427: { //Cyan
            colorReturnable = 36;
            break;
        }
        case 545: { //White
            colorReturnable = 37;
            break;
        }
        default: {
            colorReturnable = 0;
            break;
        }
    }
    return colorReturnable;
}

string CleanUp::mainModifier(const string& msg, const string& modifier) {
    string msgReturnable;
    switch(main::stoa(modifier)){
        case 417: { //bold
            msgReturnable = "**" + msg + "**";
            break;
        }
        case  630: { //italic
            msgReturnable = "*" + msg + "*";
            break;
        }
        case 1427: { //strikethrough
            msgReturnable = "~~" + msg + "~~";
            break;
        }
        case 966: { //underline
            msgReturnable = "__" + msg + "__";
            break;
        }
        default: {
            return msg;
        }
    }
    return msgReturnable;
}

string CleanUp::modify(const string& msg, const vector<string>& modifiers) {
    set<string> mods = {};
    string message = msg;
    for(const string& modifier: modifiers) {
        if (!mods.contains(modifier)) {
            message = mainModifier(message, modifier);
        }
        mods.insert(modifier);
    }
    return message;
}

string CleanUp::header(const string& msg, const string& size) {
    string headerSize;
    switch(main::stoa(size)) {
        case 537: { //small
            headerSize = "###";
            break;
        }
        case 641: { //medium
            headerSize = "##";
            break;
        }
        case 523: { //large
            headerSize = "#";
            break;
        }
        default: {
            return msg;
        }
    }
    return headerSize + " " + msg;
}

void CleanUp::addChoice(dpp::command_option& commandOption, const string& choice) {
    commandOption = commandOption.add_choice(dpp::command_option_choice(choice, choice));
}