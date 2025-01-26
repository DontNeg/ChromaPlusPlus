#include "main.h"
#include "../CleanUp/CleanUp.h"
#include "../negenv.h"

using namespace std;
using namespace dpp;

int main() {
    cluster bot(NegEnv::getEnv("TOKEN", "token.env"));
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
                event.reply(headerTypes.at(get<string>(event.get_parameter("header_size"))) + " " + get<string>(event.get_parameter("message")));
                break;
            }
            default: {
                event.reply("INVALID COMMAND (Reach out to me @dontneg if you see this error)");
            }
        }
    });
    bot.on_ready([&bot](const ready_t& event) {
        //Color Options
        auto colorOption = command_option(co_string, "color", "Color you want the text to be.", true);
        auto backgroundColorOption = command_option(co_string, "background_color", "Color you want the text to be.", false);

        //Modifier Options
        auto modifierOptionOne = command_option(co_string, "modifier_one", "First modifier you want applied.", true);
        auto modifierOptionTwo = command_option(co_string, "modifier_two", "Second modifier you want applied.", false);
        auto modifierOptionThree = command_option(co_string, "modifier_three", "Third modifier you want applied.", false);
        auto modifierOptionFour = command_option(co_string, "modifier_four", "Fourth modifier you want applied.", false);
        //Header Option
        auto headerOption = command_option(co_string, "header_size", "Size you want the header to be.", true);

        for(auto &color: colorOptions | views::keys) {
            CleanUp::addChoice(colorOption, color);
        }
        for(auto &color: bgColors | views::keys) {
            CleanUp::addChoice(backgroundColorOption, color);
        }
        for(const auto &mod: modifierOptions | views::keys) {
            CleanUp::addChoice(modifierOptionOne, mod);
            CleanUp::addChoice(modifierOptionTwo, mod);
            CleanUp::addChoice(modifierOptionThree, mod);
            CleanUp::addChoice(modifierOptionFour, mod);
        }
        for(auto &size: headerTypes | views::keys) {
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