#pragma once
#include <fstream>
#include <string>

class NegEnv{
public:
    static std::string getEnv(const std::string& varName, const std::string& fileName);
};

inline std::string NegEnv::getEnv(const std::string& varName, const std::string& fileName) {
    std::ifstream envFile(fileName);
    std::string line;
    while(std::getline(envFile, line)){
        const auto index = line.find(varName);
        if(index != std::string::npos) {
            return line.substr(index+varName.length()+1);
        }
    }
    throw std::exception("ENV VARIABLE NOT FOUND.");
}