#pragma once
#include <dpp/dpp.h>
#include <string>



class main{
public:
    static std::string getOption(const dpp::slashcommand_t& event, const std::string& optionName);
    static int stoa(const std::string& str);
};