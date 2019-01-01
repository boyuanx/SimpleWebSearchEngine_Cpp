//
// Created by Boyuan Xu on 3/31/18.
//

#include "configParser.h"
using namespace std;

void configParser::run(std::string fileName) {
    ifstream in(fileName);
    string currentLine;
    while (getline(in, currentLine)) {
        currentLine.erase(remove(currentLine.begin(), currentLine.end(), ' '), currentLine.end());
        if (currentLine[0] == '#') {
            continue;
        }
        if (currentLine.find("INDEX_FILE") != string::npos) {
            indexFilename = extractInfo(currentLine);
        }
        else if (currentLine.find("QUERY_FILE") != string::npos) {
            queryFilename = extractInfo(currentLine);
        }
        else if (currentLine.find("OUTPUT_FILE") != string::npos) {
            outputFilename = extractInfo(currentLine);
        }
        else if (currentLine.find("RESTART_PROBABILITY") != string::npos) {
            RESTART_PROBABILITY = stod(extractInfo(currentLine));
        }
        else if (currentLine.find("STEP_NUMBER") != string::npos) {
            STEP_NUMBER = stoi(extractInfo(currentLine));
        }
    }
}

std::string configParser::extractInfo(std::string currentLine) {
    currentLine.erase(currentLine.begin(), currentLine.begin() + currentLine.find_last_of('='));
    currentLine.erase(0, 1);
    if (currentLine.find('#') != string::npos) {
        currentLine.erase(currentLine.begin() + currentLine.find_first_of('#'), currentLine.end());
    }
    if (currentLine.length() == 0) {
        return 0;
    }
    return currentLine;
}

std::string configParser::getIndexFilename() const {
    return indexFilename;
}

std::string configParser::getQueryFilename() const {
    return queryFilename;
}

std::string configParser::getOutputFilename() const {
    return outputFilename;
}

double configParser::getProb() const {
    return RESTART_PROBABILITY;
}

int configParser::getStep() const {
    return STEP_NUMBER;
}


