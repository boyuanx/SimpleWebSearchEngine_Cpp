//
// Created by Boyuan Xu on 2/22/18.
//

#ifndef HW4_WEBPAGE_H
#define HW4_WEBPAGE_H

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <fstream>
using namespace std;

class WebPage {
public:
    WebPage();
    ~WebPage();
    void setPath(string p);
    string getPath() const;
    void setWords(set<string> &v);
    set<string> getWords();
    void setWordSet(set<string> &s);
    set<string> getWordSet();
    void addWord(string word);
    bool wordExists(string word);
    void addLink(string anchor, string link);
    bool removeByAnchor(string anchor);
    bool removeByLink(string link);
    bool searchAnchor(string anchor);
    bool searchLink(string link);
    map<string, string> getMap();
private:
    string path;
    set<string> wordSet; // Sorted, used for searching
    map<string, string> links;
};


#endif //HW4_WEBPAGE_H
