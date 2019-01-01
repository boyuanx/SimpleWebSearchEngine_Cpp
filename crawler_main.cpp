//
// Created by Boyuan Xu on 4/5/18.
//
#include "crawler.h"
using namespace std;

int main(int argc, char const *argv[]) {
    crawler c;
    if (argc != 2) {
        c.parseSeed("config.txt");
    }
    else {
        c.parseSeed(argv[1]);
    }
    c.crawl();
}
