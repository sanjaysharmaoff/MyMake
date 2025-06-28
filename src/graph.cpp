#include <bits/stdc++.h>
#include "graph.h"
#include <queue>
#include <algorithm>

DependencyGraph::DependencyGraph(const std::map<std::string, Rule>& rules) : rules(rules) {}

std::vector<std::string> DependencyGraph::buildOrder() {
    std::map<std::string, int> inDegree;
    std::vector<std::string> buildOrder;
     std::map<std::string,std::vector<std::string>>graph;
    for (const auto& rule : rules) {
            graph[rule.first];
            inDegree[rule.first]=0;
    }

    for (const auto& rule : rules) {
        for (const auto& dep : rule.second.dependencies) {
            if (rules.find(dep) != rules.end()) {
                 graph[dep].push_back(rule.first);
                 inDegree[rule.first]++;
            }
        }
    }


    std::queue<std::string> q;
    for (const auto& rule : rules) {
        if (inDegree[rule.first] == 0) {
            q.push(rule.first);
        }
    }


    while (!q.empty()) {
        std::string target = q.front();
        q.pop();
        buildOrder.push_back(target);
        for (auto rr  : graph[target]) {
                inDegree[rr]--;
                if (inDegree[rr] == 0) {
                    q.push(rr);
                }

        }
    }

    return buildOrder;
}
