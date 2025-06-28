#pragma once
#include <string>
#include <vector>
#include <map>
#include "parser.h"

class DependencyGraph {
public:
    DependencyGraph(const std::map<std::string, Rule>& rules);
    std::vector<std::string> buildOrder();
private:
    std::map<std::string, Rule> rules;
};
