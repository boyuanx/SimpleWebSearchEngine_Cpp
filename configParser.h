//
// Created by Boyuan Xu on 3/31/18.
//

#ifndef HW6_CONFIGPARSER_H
#define HW6_CONFIGPARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

class configParser {
public:
    void run(std::string fileName);
    std::string getIndexFilename() const;
    std::string getQueryFilename() const;
    std::string getOutputFilename() const;
    double getProb() const;
    int getStep() const;
private:
    std::string extractInfo(std::string currentLine);
    std::string indexFilename;
    std::string queryFilename;
    std::string outputFilename;
    double RESTART_PROBABILITY;
    int STEP_NUMBER;
};


#endif //HW6_CONFIGPARSER_H
