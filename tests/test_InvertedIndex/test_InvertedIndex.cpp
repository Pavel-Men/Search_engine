#include <gtest/gtest.h>
#include "../../lib/inverted_index.h"

using namespace std;

void TestInvertedIndexFunctionality(const vector<string>& docs,
                                    const vector<string>& requests,
                                    const vector<vector<Entry>>& expected)
{
    vector<vector<Entry>> result;
    InvertedIndex idx;
    idx.updateDocumentBase(docs);
    for(auto& request : requests) {
        vector<Entry> wordCount = idx.getWordCount(request);
        result.push_back(wordCount);
    }
    ASSERT_EQ(result, expected);
}

TEST(TestCaseInvertedIndex, TestBasic) {
    const vector<string> docs = {
        "london is the capital of great britain",
        "big ben is the nickname for the Great bell of the striking clock"
    };
    const vector<string> requests = {"london", "the"};
    const vector<vector<Entry>> expected = {
        {
            {0, 1}
        }, {
            {0, 1}, {1, 3}
        }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}

TEST(TestCaseInvertedIndex, TestBasic2) {
    const vector<string> docs = {
        "milk milk milk milk water water water",
        "milk water water",
        "milk milk milk milk milk water water water water water",
        "americano cappuccino"
    };
    const vector<string> requests = {"milk", "water", "cappuccino"};
    const vector<vector<Entry>> expected = {
        {
            {0, 4}, {1, 1}, {2, 5}
        }, {
            {0, 3}, {1, 2}, {2, 5}
        }, {
            {3, 1}
        }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}

TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord) {
    const vector<string> docs = {
        "a b c d e f g h i j k l",
        "statement"
    };
    const vector<string> requests = {"m", "statement"};
    const vector<vector<Entry>> expected = {
        {
        }, {
            {1, 1}
        }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}



