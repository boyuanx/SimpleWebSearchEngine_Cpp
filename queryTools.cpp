//
// Created by Boyuan Xu on 2/23/18.
//

#include "queryTools.h"
#include "setutility.h"

queryTools::queryTools() {

}

queryTools::~queryTools() {

}

void queryTools::setOutFile(string fileName) {
    outputFileName = fileName;
}

void queryTools::read(string fileName) {
    ifstream in(fileName);
    string currentLine;
    while(getline(in, currentLine)) {
        if (currentLine == "") {
            continue;
        }
        if (currentLine.find("PRINT") == string::npos && currentLine.find("INCOMING") == string::npos && currentLine.find("OUTGOING") == string::npos) {
            for (unsigned int i = 0; i < currentLine.length(); i++) {
                char c = tolower(currentLine[i]);
                currentLine[i] = c;
            }
        }
        query.push_back(currentLine);
    }
}

void queryTools::execute(set<WebPage*> &v) {
    vector<string>::iterator it;
    for (it = query.begin(); it != query.end(); it++) {
        bool cmdIsPrint = false;
        bool runPageRank = false;
        bool invalidCmd = false;
        bool invalidQuery = false;
        int matchedCount = 0;
        set<string> matchedFiles;
        string currentLine = *it;
        string command = currentLine.substr(0, currentLine.find(' '));
        // NOTE: All characters have been converted into lowercase, except for PRINT
        if (command == "and" && currentLine.length() != 3) {
            currentLine.erase(0, 4); // Removes "and "
            set<string> wordList = commandParser(currentLine);
            set<set<string>> wpSet;
            for (set<string>::iterator it = wordList.begin(); it != wordList.end(); it++) {
                set<string> currentWordFound;
                for (set<WebPage*>::iterator it2 = v.begin(); it2 != v.end(); it2++) {
                    WebPage* currentPage = *it2;
                    if (currentPage->wordExists(*it)) {
                        currentWordFound.insert(currentPage->getPath());
                        if (currentPage->getMap().size() > 0) {
                            map<string, string> tempMap = currentPage->getMap();
                            for (map<string, string>::iterator it4 = tempMap.begin();
                                 it4 != tempMap.end(); it4++) {
                                currentWordFound.insert(it4->second);
                            }
                        }
                        if (inLinkMap.count(currentPage->getPath())) {
                            for (set<string>::iterator it3 = inLinkMap[currentPage->getPath()].begin();
                                 it3 != inLinkMap[currentPage->getPath()].end(); it3++) {
                                currentWordFound.insert(*it3);
                            }
                        }
                    }
                }
                wpSet.insert(currentWordFound);
            }
            set<string> begin = *wpSet.begin();
            for (set<set<string>>::iterator it = wpSet.begin(); it != wpSet.end(); it++) {
                set<string> currentWord = *it;
                begin = intersectSet(begin, currentWord);
            }
            for (set<string>::iterator it = begin.begin(); it != begin.end(); it++) {
                matchedFiles.insert(*it);
                matchedCount++;
            }
            runPageRank = true;
        }
        else if (command == "or" && currentLine.length() != 2) {
            currentLine.erase(0, 3); // Removes "or "

            set<string> wordList = commandParser(currentLine);

            set<set<string>> wpSet;
            for (set<string>::iterator it = wordList.begin(); it != wordList.end(); it++) {
                set<string> currentWordFound;
                for (set<WebPage*>::iterator it2 = v.begin(); it2 != v.end(); it2++) {
                    WebPage* currentPage = *it2;
                    if (currentPage->wordExists(*it)) {
                        currentWordFound.insert(currentPage->getPath());
                        if (currentPage->getMap().size() > 0) {
                            map<string, string> tempMap = currentPage->getMap();
                            for (map<string, string>::iterator it4 = tempMap.begin();
                                 it4 != tempMap.end(); it4++) {
                                currentWordFound.insert(it4->second);
                            }
                        }
                        if (inLinkMap.count(currentPage->getPath())) {
                            for (set<string>::iterator it3 = inLinkMap[currentPage->getPath()].begin();
                                 it3 != inLinkMap[currentPage->getPath()].end(); it3++) {
                                currentWordFound.insert(*it3);
                            }
                        }
                    }
                }
                wpSet.insert(currentWordFound);
            }
            set<string> begin = *wpSet.begin();
            for (set<set<string>>::iterator it = wpSet.begin(); it != wpSet.end(); it++) {
                set<string> currentWord = *it;
                begin = unionSet(begin, currentWord);
            }
            for (set<string>::iterator it = begin.begin(); it != begin.end(); it++) {
                matchedFiles.insert(*it);
                matchedCount++;
            }
            runPageRank = true;
        }
        else if (command == "PRINT" && currentLine.length() != 5) {
            currentLine.erase(0, 6); // Removes "print "
            ifstream in(currentLine);
            string temp;
            bool firstTimeRun = true;
            while(getline(in, temp)) {
                unsigned long found = temp.find('(');
                if (found != string::npos) {
                    unsigned long found2 = temp.find(')');
                    temp.erase(found, found2-found+1);
                }
                if (firstTimeRun) {
                    temp = currentLine + "\n" + temp;
                    firstTimeRun = false;
                }
                write(temp);
            }
            cmdIsPrint = true;
        }
        else if (command == "INCOMING" && currentLine.length() != 8) {
            currentLine.erase(0, 9); // Removes "incoming "
            while (currentLine.find(' ') != string::npos) {
                currentLine.erase(currentLine.find(' '), 1);
            }
            if (inLinkMap.count(currentLine)) {
                for (set<string>::iterator it = inLinkMap[currentLine].begin(); it != inLinkMap[currentLine].end(); it++) {
                    matchedFiles.insert(*it);
                    matchedCount++;
                }
            }
        }
        else if (command == "OUTGOING" && currentLine.length() != 8) {
            currentLine.erase(0, 9); // Removes "outgoing "
            while (currentLine.find(' ') != string::npos) {
                currentLine.erase(currentLine.find(' '), 1);
            }
            set<WebPage*>::iterator it;
            for (it = v.begin(); it != v.end(); it++) {
                WebPage* currentPage = *it;
                string currentPath = currentPage->getPath();

                cout << currentPath << endl;
                cout << currentLine << endl;
                if (currentPath == currentLine) {
                    map<string, string> currentMap = currentPage->getMap();
                    int linkCount = 0;
                    set<string> links;
                    for (map<string, string>::iterator it2 = currentMap.begin(); it2 != currentMap.end(); it2++) {
                        links.insert(it2->second);
                        linkCount++;
                    }
                    write(to_string(linkCount));
                    for (set<string>::iterator it3 = links.begin(); it3 != links.end(); it3++) {
                        write(*it3);
                    }
                }
            }
            cmdIsPrint = true;
        }
        else { // Only a single word present
            if (currentLine.find(' ') == string::npos) {
                for (unsigned int i = 0; i < currentLine.length(); i++) {
                    if (!isalnum(currentLine[i])) {
                        //write("0");
                        write("Invalid query");
                        invalidCmd = true;
                    }
                }
                if (invalidCmd) {
                    continue;
                }
                set<WebPage*>::iterator it;
                for (it = v.begin(); it != v.end(); it++) {
                    WebPage* currentPage = *it;
                    if (currentPage->wordExists(currentLine)) {
                        if (!matchedFiles.count(currentPage->getPath())) {
                            matchedFiles.insert(currentPage->getPath());
                            matchedCount++;
                        }
                        if (currentPage->getMap().size() > 0) {
                            map<string, string> tempMap = currentPage->getMap();
                            for (map<string, string>::iterator it4 = tempMap.begin();
                                 it4 != tempMap.end(); it4++) {
                                if (!matchedFiles.count(it4->second)) {
                                    matchedFiles.insert(it4->second);
                                    matchedCount++;
                                }
                            }
                        }
                        if (inLinkMap.count(currentPage->getPath())) {
                            for (set<string>::iterator it3 = inLinkMap[currentPage->getPath()].begin();
                                 it3 != inLinkMap[currentPage->getPath()].end(); it3++) {
                                if (!matchedFiles.count(*it3)) {
                                    matchedFiles.insert(*it3);
                                    matchedCount++;
                                }
                            }
                        }
                    }
                }
                runPageRank = true;
            }
            else {
                if (!invalidCmd) {
                    write("Invalid query");
                    invalidQuery = true;
                }
            }
        }
        // Prints results
        if (!cmdIsPrint && !runPageRank && !invalidQuery) {
            write(to_string(matchedCount));
            set<string>::iterator it2;
            for (it2 = matchedFiles.begin(); it2 != matchedFiles.end(); it2++) {
                write(*it2);
            }
        }
        if (runPageRank) {
            pageRank pR;
            pR.setup(RESTART_PROBABILITY, STEP_NUMBER);
            map<double, set<string>> pageRankMap = pR.run(matchedFiles, v, inLinkMap);
            write(to_string(matchedCount));
            for (map<double, set<string>>::reverse_iterator it = pageRankMap.rbegin(); it != pageRankMap.rend(); it++) {
                set<string> tempSet = it->second;
                for (set<string>::iterator it2 = tempSet.begin(); it2 != tempSet.end(); it2++) {
                    write(*it2);
                }
            }
        }
    }
}

void queryTools::write(string fileContent) {
    ofstream out(outputFileName, ios::app);
    while (fileContent.find('(') != string::npos) {
        fileContent.erase(fileContent.begin() + fileContent.find_first_of('('), fileContent.begin() + fileContent.find_last_of(')'));
    }
    while (fileContent.find(')') != string::npos) {
        fileContent.erase(fileContent.begin() + fileContent.find_first_of(')'));
    }
    while (fileContent.find('(') != string::npos) {
        fileContent.erase(fileContent.begin() + fileContent.find_first_of('('));
    }
    out << fileContent << endl;
    out.flush();
    out.close();
}

set<string> queryTools::commandParser(string cmd) { // Reads words into a vector
    set<string> wordList;
    stringstream ss(cmd);
    string temp;
    while(getline(ss, temp, ' ')) {
        wordList.insert(temp);
    }
    return wordList;
}

void queryTools::pageRank_setup(double rProb, int step, map<string, set<string>> inMap) {
    RESTART_PROBABILITY = rProb;
    STEP_NUMBER = step;
    inLinkMap = inMap;
}
