#ifndef SEARCH_SERVER_H
#define SEARCH_SERVER_H

#include <vector>
#include <set>
#include "inverted_index.h"

using namespace std;

class SearchServer
{
    InvertedIndex* idx;

    void getUniqueWords(const string& request, set<string>& uniqueRequest);

    void getDocIdCount(const set<string>& request, map<size_t, float>& docIdCount);

public:
    SearchServer(InvertedIndex& idx);

    vector<vector<RelativeIndex>> search(const vector<string>& requests);
};

#endif // SEARCH_SERVER_H
