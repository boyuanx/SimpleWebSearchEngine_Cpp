CXX = g++
CPPFLAGS = -g -Wall -std=c++11

crawler: crawler_main.cpp crawler.cpp
	$(CXX) $(CPPFLAGS) crawler_main.cpp crawler.cpp -o crawler

search: main.cpp indexParser.cpp indexParser.h queryTools.cpp queryTools.h WebPage.cpp WebPage.h configParser.cpp configParser.h pageRank.cpp pageRank.h setutility.h
	$(CXX) $(CPPFLAGS) main.cpp indexParser.cpp queryTools.cpp WebPage.cpp configParser.cpp pageRank.cpp -o search

clean:
	-@rm -rf crawler
	-@rm -rf search