#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <vector>
#include <string>
#include <map>
#include <mutex>
#include "structs.h"

using namespace std;


class InvertedIndex
{
    vector<string> docs;
    map<string, vector<Entry>> freqDictionary;
    mutex freqDictionaryAccess;

public:
    InvertedIndex() = default;

    void updateDocumentBase(vector<string> input_docs);

    vector<Entry> getWordCount(const string& word);

    void getWordsFromDoc(const size_t id);

};


#endif // INVERTED_INDEX_H
