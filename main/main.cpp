#include "main.h"
#include "../CleanUp/CleanUp.h"

using namespace std;
using namespace dpp;

const std::string BOT_TOKEN = "";

int main() {
    cluster bot(BOT_TOKEN);
    bot.on_log(utility::cout_logger());
    bot.on_slashcommand([](const slashcommand_t& event) {
        switch(main::stoa(event.command.get_command_name())) {
            case 543: { //Color
                event.reply(CleanUp::getMessage(
                    main::getOption(event, "background_color"),
                    get<string>(event.get_parameter("color")),
                    get<string>(event.get_parameter("message"))
                ));
                break;
            }
            case 648: { //Modify
                const vector<string>& mods = {
                    main::getOption(event, "modifier_one"),
                    main::getOption(event, "modifier_two"),
                    main::getOption(event, "modifier_three"),
                    main::getOption(event, "modifier_four")
                };
                event.reply(CleanUp::modify(
                    get<string>(event.get_parameter("message")), mods
                ));
                break;
            }
            case 617: { //Header
                event.reply(CleanUp::header(
                    get<string>(event.get_parameter("message")),
                    get<string>(event.get_parameter("header_size"))
                ));
                break;
            }
            default: {
                event.reply("INVALID COMMAND (Reach out to me @dontneg if you see this error)");
            }
        }
    });
    bot.on_ready([&bot](const ready_t& event) {
        const vector<string> colors = {"gray","red","green","orange","blue","pink","cyan","white"};
        const vector<string> bgColors = {"dark blue","orange", "even darker gray","dark gray","gray","purple","light gray","white"};
        const vector<string> mods = {"bold","italic","strikethrough","underline"};
        const vector<string> headerType = {"large", "medium", "small"};
        //Color Options
        command_option colorOption = command_option(co_string, "color", "Color you want the text to be.", true);
        command_option backgroundColorOption = command_option(co_string, "background_color", "Color you want the text to be.", false);

        //Modifier Options
        command_option modifierOptionOne = command_option(co_string, "modifier_one", "First modifier you want applied.", true);
        command_option modifierOptionTwo = command_option(co_string, "modifier_two", "Second modifier you want applied.", false);
        command_option modifierOptionThree = command_option(co_string, "modifier_three", "Third modifier you want applied.", false);
        command_option modifierOptionFour = command_option(co_string, "modifier_four", "Fourth modifier you want applied.", false);

        //Header Option
        command_option headerOption = command_option(co_string, "header_size", "Size you want the header to be.", true);

        for(const string& color: colors) {
            CleanUp::addChoice(colorOption, color);
        }
        for(const string& color: bgColors) {
            CleanUp::addChoice(backgroundColorOption, color);
        }
        for(const string& mod: mods) {
            CleanUp::addChoice(modifierOptionOne, mod);
            CleanUp::addChoice(modifierOptionTwo, mod);
            CleanUp::addChoice(modifierOptionThree, mod);
            CleanUp::addChoice(modifierOptionFour, mod);
        }
        for(const string& size: headerType) {
            CleanUp::addChoice(headerOption, size);
        }
        if (run_once<struct register_bot_commands>()) {
            //Color Command
            bot.global_command_create(slashcommand("color", "Generate text with a specific color", bot.me.id)
                .add_option(*new command_option(co_string, "message", "message you want colorized", true))
                .add_option(colorOption)
                .add_option(backgroundColorOption));
            //Modify Command
            bot.global_command_create(slashcommand("modify", "Generate text with a specific modifier.", bot.me.id)
                .add_option(*new command_option(co_string, "message", "message you want modified.", true))
                .add_option(modifierOptionOne)
                .add_option(modifierOptionTwo)
                .add_option(modifierOptionThree)
                .add_option(modifierOptionFour));
            //Header Command
            bot.global_command_create(slashcommand("header", "Generate a header with your text and a specific size", bot.me.id)
                .add_option(*new command_option(co_string, "message", "message you want turned into a header", true))
                .add_option(headerOption));
        }
    });
    bot.start(st_wait);
}

int main::stoa(const string& str) {
    int asciival = 0;
    for(const auto character: str) {
        asciival += static_cast<int>(character);
    }
    return asciival;
}

string main::getOption(const slashcommand_t& event, const string& optionName) {
    return holds_alternative<string>(event.get_parameter(optionName)) ? get<string>(event.get_parameter(optionName)) : "";
}