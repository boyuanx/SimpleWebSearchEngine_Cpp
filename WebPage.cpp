//
// Created by Boyuan Xu on 2/22/18.
//

#include "WebPage.h"

WebPage::WebPage() {

}

WebPage::~WebPage() {

}

void WebPage::setPath(string p) {
    path = p;
}

string WebPage::getPath() const {
    return path;
}

void WebPage::setWords(set<string> &v) {
    wordSet = v;
}

set<string> WebPage::getWords() {
    return wordSet;
}

void WebPage::addWord(string word) {
    for (unsigned int i = 0; i < word.length(); i++) {
        char c = tolower(word[i]);
        word[i] = c;
    }
    wordSet.insert(word);
}

bool WebPage::wordExists(string word) {
    if (wordSet.count(word) || searchAnchor(word)) {
        return true;
    }
    else if (wordSet.count(word + ' ') || searchAnchor(word + ' ')) {
        return true;
    }

    return false;
}

void WebPage::addLink(string anchor, string link) {
    links[anchor] = link;
}

bool WebPage::removeByAnchor(string anchor) {
    map<string, string>::iterator it;
    for (it = links.begin(); it != links.end();) {
        if (it->first == anchor) {
            it = links.erase(it);
            return true;
        }
        else {
            it++;
        }
    }
    return false;
}

bool WebPage::removeByLink(string link) {
    map<string, string>::iterator it;
    for (it = links.begin(); it != links.end();) {
        if (it->second == link) {
            it = links.erase(it);
            return true;
        }
        else {
            it++;
        }
    }
    return false;
}

bool WebPage::searchAnchor(string anchor) {
    return links.find(anchor) != links.end();
}

bool WebPage::searchLink(string link) {
    if (links.count(link)) {
        return true;
    }
    return false;
}

map<string, string> WebPage::getMap() {
    return links;
}

void WebPage::setWordSet(set<string> &s) {
    wordSet = s;
}

set<string> WebPage::getWordSet() {
    return wordSet;
}