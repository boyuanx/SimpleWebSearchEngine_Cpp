//
// Created by Boyuan Xu on 2/22/18.
//

#ifndef HW4_INDEXPARSER_H
#define HW4_INDEXPARSER_H

#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <map>
#include "WebPage.h"

using namespace std;

class indexParser {
public:
    indexParser();
    ~indexParser();
    void run(string fileName);
    set<WebPage*> getPages(); // Gets all pages
    void addPage(WebPage* WP);
    map<string, set<string>> getIncomingLinks();
private:
    set<WebPage*> parsedIndex;
    map<string, set<string>> incomingLinkMap; //<target file, incoming link source>
};


#endif //HW4_INDEXPARSER_H
