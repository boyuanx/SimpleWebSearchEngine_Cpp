//
// Created by Boyuan Xu on 3/31/18.
//

#include "crawler.h"
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

void crawler::parseSeed(std::string fileName) {
    ifstream in(fileName);
    string currentLine;
    while(getline(in, currentLine)) {
        currentLine.erase(remove(currentLine.begin(), currentLine.end(), ' '), currentLine.end());
        if (currentLine.find("OUTPUT_FILE=") != string::npos) {
            currentLine.erase(currentLine.begin(), currentLine.begin() + currentLine.find_first_of('='));
            currentLine.erase(0, 1);
            outputFile = currentLine;
        }
        else if (currentLine.find("INDEX_FILE=") != string::npos) {
            currentLine.erase(currentLine.begin(), currentLine.begin() + currentLine.find_first_of('='));
            currentLine.erase(0, 1);
            indexFiles.insert(currentLine);
        }
        else if (currentLine.find('#') != string::npos || currentLine.find('=') != string::npos) {
            continue;
        }
        else {
            indexFiles.insert(currentLine);
        }
    }
}

void crawler::crawl() {
    for (set<string>::iterator it = indexFiles.begin(); it != indexFiles.end(); it++) {
        ifstream in(*it);
        string currentLine;
        while (getline(in, currentLine)) {
            parseLinks(currentLine);
        }
    }
    write();
}

void crawler::parseLinks(std::string fileName) {
    if (!crawlResultSet.count(fileName)) {
        crawlResult.push_back(fileName);
        crawlResultSet.insert(fileName);
    }
    ifstream in(fileName);
    string currentLine;
    while (getline(in, currentLine)) {
        stringstream ss(currentLine);
        int ssLength = ss.str().length();
        for (int i = 0; i < ssLength; i++) {
            string linkBuffer;
            char c;
            ss >> noskipws >> c; // or else it'll mess up the count
            if (c == '(') {
                while (c != ')') {
                    ss >> noskipws >> c;
                    if (c != ')') {
                        linkBuffer = linkBuffer + c;
                    }
                    i++;
                }
                ifstream test(linkBuffer);
                if (!test.fail()) {
                    parseLinks(linkBuffer);
                }
                else {
                    return;
                }
            }
        }
    }
}

set<string> crawler::getIndex() {
    return indexFiles;
}

string crawler::getOutput() {
    return outputFile;
}

void crawler::write() {
    ofstream out(outputFile);
    for (vector<string>::iterator it = crawlResult.begin(); it != crawlResult.end(); it++) {
        out << *it << endl;
    }
    out.flush();
    out.close();
}
