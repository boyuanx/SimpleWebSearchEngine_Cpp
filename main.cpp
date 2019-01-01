#include <iostream>
#include "indexParser.h"
#include "queryTools.h"
#include "WebPage.h"
#include "configParser.h"
#include "crawler.h"
#include <set>
using namespace std;

int main(int argc, char const *argv[]) {
    indexParser iP;
    queryTools qT;
    configParser cP;
    if (argc != 2) {
        cP.run("config.txt");
    }
    else {
        cP.run(argv[1]);
    }
    iP.run(cP.getIndexFilename());
    qT.setOutFile(cP.getOutputFilename());
    qT.read(cP.getQueryFilename());
    set<WebPage*> WPSet = iP.getPages();
    qT.pageRank_setup(cP.getProb(), cP.getStep(), iP.getIncomingLinks());
    qT.execute(WPSet);
    return 0;
}

