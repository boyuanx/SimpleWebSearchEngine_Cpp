//
// Created by Boyuan Xu on 3/31/18.
//

#ifndef HW6_CRAWLER_H
#define HW6_CRAWLER_H
#include <iostream>
#include <set>
#include <vector>

class crawler {
public:
    void parseSeed(std::string fileName);
    void crawl();
    std::set<std::string> getIndex();
    std::string getOutput();
private:
    void parseLinks(std::string fileName);
    void write();
    std::set<std::string> indexFiles;
    std::string outputFile;
    std::vector<std::string> crawlResult;
    std::set<std::string> crawlResultSet;
};

#endif //HW6_CRAWLER_H
