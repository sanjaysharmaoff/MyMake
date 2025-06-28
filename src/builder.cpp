#include "builder.h"
#include <iostream>
#include <filesystem>
#include <cstdlib>

namespace fs = std::filesystem;

Builder::Builder(const std::map<std::string, Rule>& rules) : rules(rules) {}

bool Builder::isOutOfDate(const std::string& target) {
    if (rules.count(target) && rules.at(target).command.size() && !fs::exists(target)) {
        if (target == "all" || target == "clean") return true;
    }
    if (!fs::exists(target)) return true;
    auto targetTime = fs::last_write_time(target);
    for (const auto& dep : rules.at(target).dependencies) {
        if (fs::last_write_time(dep) > targetTime) {
            return true;
        }
    }
    return false;
}

void Builder::execute(const std::vector<std::string>& buildOrder) {
    for (const std::string& target : buildOrder) {
        bool isPhony = (target == "all" || target == "clean");
        if (isOutOfDate(target) || isPhony) {
            std::cout << "Rebuilding " << target << ":" << std::endl;
            const std::string& cmd = rules.at(target).command;
            if (!cmd.empty()) {
                std::cout << "  Executing: " << cmd << std::endl;
                std::system(cmd.c_str());
            }
        } else {
            std::cout << target << " is up to date" << std::endl;
        }
    }
}
