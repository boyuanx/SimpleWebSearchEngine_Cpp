//
// Created by Boyuan Xu on 4/4/18.
//

#ifndef HW6_PAGERANK_H
#define HW6_PAGERANK_H
#include "WebPage.h"
#include <set>
#include <map>
#include <iostream>

struct find_by_path {
    find_by_path(const std::string &path) : path(path) {};
    bool operator()(const WebPage* wp) {
        return wp->getPath() == path;
    }
private:
    std::string path;
};

class pageRank {
public:
    map<double, set<string>> run(std::set<std::string> matchedFiles,
                              std::set<WebPage*> v,
                              std::map<std::string, std::set<std::string>> inLinkMap);
    void setup(double RESTART_PROBABILITY, int STEP_NUMBER);
private:
    double restart_prob;
    int step_num;
};


#endif //HW6_PAGERANK_H
