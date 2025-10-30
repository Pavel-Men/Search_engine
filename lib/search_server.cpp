#include "search_server.h"
#include <map>
#include <sstream>
#include <functional>


void SearchServer::getUniqueWords(const string& request,
                                  set<string>& uniqueRequest)
{
    string word;
    stringstream temporary(request);
    while (temporary >> word)
    {
       uniqueRequest.insert(word);
    }
}

void SearchServer::getDocIdCount(const set<string>& request,
                                map<size_t, float>& docIdCount)
{
    for(const auto& word : request)
    {
        vector<Entry> wordEntry = idx->getWordCount(word);
        if(wordEntry.empty()) continue;
        for(const auto& entry : wordEntry)
        {
            if(docIdCount.contains(entry.docId))
                docIdCount[entry.docId] += entry.count;
            else
                docIdCount[entry.docId] = entry.count;
        }
    }
}

SearchServer::SearchServer(InvertedIndex& invertedIndex)
{
    idx = &invertedIndex;
}

vector<vector<RelativeIndex>> SearchServer::search(
                    const vector<string>& requests)
{
    vector<vector<RelativeIndex>> answers;

    for(size_t i = 0; i < requests.size(); i++)
    {
        answers.push_back(vector<RelativeIndex>());
        if(requests[i].empty()) continue;

        set<string> request;
        getUniqueWords(requests[i], request);

        map<size_t, float> docIdCount; // <"DocID", "count">
        getDocIdCount(request, docIdCount);

        if(!docIdCount.empty())
        {
            multimap<float, size_t, greater<float>> relativeIndex; //<"rank", "DocID">
            for(const auto& it : docIdCount)
            {
                relativeIndex.emplace(it.second, it.first);
            }

            float maxCount = relativeIndex.begin()->first;
            for(const auto& it : relativeIndex)
            {
                answers[i].push_back({it.second, it.first / maxCount});
            }
        }
    }
    return answers;
}
