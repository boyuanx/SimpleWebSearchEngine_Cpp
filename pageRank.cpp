//
// Created by Boyuan Xu on 4/4/18.
//

#include "pageRank.h"
#include <algorithm>
using namespace std;


void pageRank::setup(double RESTART_PROBABILITY, int STEP_NUMBER) {
    restart_prob = RESTART_PROBABILITY;
    step_num = STEP_NUMBER;
}

map<double, set<string>> pageRank::run(std::set<std::string> matchedFiles, set<WebPage*> v, map<string, set<string>> inLinkMap) {
    set<WebPage*> wpSet;
    for (set<string>::iterator it = matchedFiles.begin(); it != matchedFiles.end(); it++) {
        set<WebPage*>::iterator it2 = find_if(v.begin(), v.end(), find_by_path(*it));
        if (it2 == v.end()) {
            cerr << "No match found... WHICH SHOULD NOT HAPPEN!" << endl;
            continue;
        }
        WebPage* temp = *it2;
        string tempPath = temp->getPath();
        temp->addLink(tempPath, tempPath);
        inLinkMap[tempPath].insert(tempPath);
        wpSet.insert(temp);
    }
    // Page Rank implementation:
    const unsigned int numNodes = wpSet.size();
    const double startRank = (1.0/numNodes);
    double currentRank;
    double tempRank;
    unsigned int timesRun = 0;
    map<string, double> tempRankMap;
    map<string, double> rankMap;
    for (int t = -1; t < step_num; t++) {
        for (set<WebPage*>::iterator it = wpSet.begin(); it != wpSet.end(); it++) {
            WebPage *temp = *it;
            if (t == -1) {
                rankMap[temp->getPath()]= (startRank);
                continue;
            }
            if (timesRun >= wpSet.size()) {
                currentRank = rankMap[temp->getPath()];
                int outDegree = temp->getMap().size();
                tempRank = (1.0 - restart_prob)*currentRank*(1.0/outDegree);
                tempRankMap[temp->getPath()] = tempRank;
            }
            else if (t == 0) {
                timesRun++;
                int outDegree = temp->getMap().size();
                tempRank = (1.0 - restart_prob)*startRank*(1.0/outDegree);
                tempRankMap[temp->getPath()] = tempRank;
            }
        }

        if (t != -1) {
            for (set<WebPage *>::iterator it = wpSet.begin(); it != wpSet.end(); it++) {
                WebPage *temp = *it;
                string path = temp->getPath();
                double totalRank = 0;
                if (inLinkMap.count(path)) {
                    for (set<string>::iterator it2 = inLinkMap[path].begin(); it2 != inLinkMap[path].end(); it2++) {
                        totalRank = totalRank + tempRankMap[*it2];
                    }
                }
                totalRank = totalRank + restart_prob/numNodes;
                rankMap[path]=(totalRank);
            }
        }
    }
    map<double, set<string>> outputMap;
    for (map<string, double>::iterator it = rankMap.begin(); it != rankMap.end(); it++) {
        outputMap[it->second].insert(it->first);
    }
    return outputMap;
}