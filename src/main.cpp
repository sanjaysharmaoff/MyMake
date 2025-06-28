#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include "parser.h"
#include "builder.h"
#include "graph.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <Makefile> [target]" << std::endl;
        return 1;
    }
    std::string makefile = argv[1];
    std::string target = (argc >= 3) ? argv[2] : "all";
    if(target=="clean"){
        std::string cmd="cmd /c del /Q *.o app 2>nul";
        std::cout << "  Executing: " << cmd << std::endl;
        std::system(cmd.c_str());
        return 0;
    }
    MakefileParser parser;
    auto rules = parser.parseMakefile(makefile);
    DependencyGraph graph(rules);
    auto buildOrder = graph.buildOrder();
    std::cout << "Build order:";
    for (const auto& t : buildOrder) {
        std::cout << " " << t;
    }
    std::cout << std::endl;
    std::vector<std::string>::iterator it = std::find(buildOrder.begin(), buildOrder.end(), target);
    if (it == buildOrder.end()) {
        std::cerr << "Target '" << target << "' not found in Makefile." << std::endl;
        return 2;
    }
    std::vector<std::string> toBuild;
    for (auto iter = buildOrder.begin(); iter != it + 1; ++iter) {
        toBuild.push_back(*iter);
    }
    Builder builder(rules);
    builder.execute(toBuild);
    return 0;
}