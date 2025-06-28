#pragma once
#include <string>
#include <vector>
#include <map>
#include "parser.h"

class Builder {
public:
    Builder(const std::map<std::string, Rule>& rules);
    void execute(const std::vector<std::string>& buildOrder);
private:
    std::map<std::string, Rule> rules;
    bool isOutOfDate(const std::string& target);
};
