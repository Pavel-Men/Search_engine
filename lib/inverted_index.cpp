#include "inverted_index.h"
#include <sstream>
#include <thread>


void InvertedIndex::getWordsFromDoc(const size_t& id)
{
    if(id >= docs.size()) return;
    string word;
    map<string, Entry> wordsInDoc;
    stringstream doc(docs[id]);
    while (doc >> word)
    {
        wordsInDoc[word].docId = id;
        wordsInDoc[word].count++;
    }
    freqDictionaryAccess.lock();
    for(const auto& it : wordsInDoc)
    {
        freqDictionary[it.first].push_back(it.second);
    }
    freqDictionaryAccess.unlock();
}

void InvertedIndex::updateDocumentBase(const vector<string>& input_docs)
{
    docs = input_docs;
    vector<thread> threads;
    for(size_t id = 0; id < docs.size(); id++)
    {
        threads.push_back(thread(&InvertedIndex::getWordsFromDoc, this, id));
    }
    for(auto& thread : threads)
    {
        thread.join();
    }
}

vector<Entry> InvertedIndex::getWordCount(const string& word)
{
    if(freqDictionary.contains(word))
    {
        return freqDictionary[word];
    }
    return vector<Entry>();
}
