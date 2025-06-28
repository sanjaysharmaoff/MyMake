#pragma once
#include <string>
#include <vector>
#include <map>

struct Rule {
    std::vector<std::string> dependencies;
    std::string command;
};

class MakefileParser {
public:
    std::map<std::string, Rule> parseMakefile(const std::string& filename);
};
