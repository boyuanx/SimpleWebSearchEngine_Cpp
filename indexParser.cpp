//
// Created by Boyuan Xu on 2/22/18.
//

#include "indexParser.h"

indexParser::indexParser() {

}

indexParser::~indexParser() {
    set<WebPage*>::iterator it;
    for (it = parsedIndex.begin(); it != parsedIndex.end(); it++) {
        delete *it;
    }
}

void indexParser::run(string fileName) {
    ifstream in(fileName);
    string currentLine; // Current line in index.txt, AKA the current line is a file path
    while (getline(in, currentLine)) {
        if (currentLine == "") {
            continue;
        }
        WebPage* newWP = new WebPage();
        newWP->setPath(currentLine);
        ifstream in2(currentLine);
        string currentLine2; // Current line in the webpage file, AKA webpage contents
        string persistAnchor;
        while (getline(in2, currentLine2)) {
            stringstream ss(currentLine2);
            int ssLength = ss.str().length();
            for (int i = 0; i < ssLength; i++) {
                string wordBuffer;
                string anchorBuffer;
                string linkBuffer;
                char c;
                ss >> noskipws >> noskipws >> c;
                if (c == '[') { // Anchor found
                    while (c != ']') {
                        ss >> noskipws >> c;
                        if (c != ']') {
                            anchorBuffer = anchorBuffer + c;
                        }
                        i++;
                    }
                    newWP->addWord(anchorBuffer);
                    persistAnchor = anchorBuffer;
                }
                else if (c == '(') { // Corresponding Link found
                    while (c != ')') {
                        ss >> noskipws >> c;
                        if (c != ')') {
                            linkBuffer = linkBuffer + c;
                        }
                        i++;
                    }
                    newWP->addLink(persistAnchor, linkBuffer);
                    incomingLinkMap[linkBuffer].insert(currentLine);
                }
                else if (isalpha(c) || isdigit(c) || c == '.' || c == ',') { // Letters, numbers, period, comma.
                    while (isalpha(c) || isdigit(c)) {
                        if (i >= ssLength) {
                            break;
                        }
                        wordBuffer = wordBuffer + c;
                        ss >> noskipws >> c;
                        i++;
                    }
                    newWP->addWord(wordBuffer);
                }
            }
        }
        addPage(newWP); //NOTE: all words still have a space bar attached to it, except for the word at the end.
    }
}

set<WebPage*> indexParser::getPages() {
    return parsedIndex;
}

void indexParser::addPage(WebPage* WP) {
    parsedIndex.insert(WP);
}

map<string, set<string>> indexParser::getIncomingLinks() {
    return incomingLinkMap;
}
