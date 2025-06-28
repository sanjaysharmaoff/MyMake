#include "parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>

std::map<std::string, Rule> MakefileParser::parseMakefile(const std::string& filename) {
    std::map<std::string, Rule> rules;
    std::ifstream file(filename);
    std::string line, target;
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return rules;
    }
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        if (line.find(":") != std::string::npos && line.find_first_not_of(" \t") == 0) {
            std::istringstream iss(line);
            iss >> target;
            if (!target.empty() && target.back() == ':')
                target.pop_back();
            std::string dep;
            while (iss >> dep) {
                rules[target].dependencies.push_back(dep);
            }
        }
        if (!line.empty() && (line[0] == '\t' || (line.size() >= 4 && line.substr(0,4) == "    "))) {
            size_t cmd_start = (line[0] == '\t') ? 1 : 4;
            rules[target].command = line.substr(cmd_start);
        }
    }
    return rules;
}
