//
// Created by Boyuan Xu on 2/23/18.
//

#ifndef HW4_QUERYTOOLS_H
#define HW4_QUERYTOOLS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>
#include "WebPage.h"
#include "pageRank.h"
using namespace std;

class queryTools {
public:
    queryTools();
    ~queryTools();
    void setOutFile(string fileName);
    void read(string fileName);
    void execute(set<WebPage*> &v);
    void write(string fileContent);
    set<string> commandParser(string cmd);
    void pageRank_setup(double rProb, int step, map<string, set<string>> inMap);
private:
    vector<string> query;
    string outputFileName;
    map<string, set<string>> inLinkMap;
    double RESTART_PROBABILITY;
    int STEP_NUMBER;
};


#endif //HW4_QUERYTOOLS_H
