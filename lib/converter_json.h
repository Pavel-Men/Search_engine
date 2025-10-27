#ifndef CONVERTER_JSON_H
#define CONVERTER_JSON_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "structs.h"

using namespace std;
using namespace nlohmann;

class ConverterJSON
{
    ordered_json configJSON;
    ordered_json requestsJSON;
    ordered_json answersJSON;

    int responsesLimit = 5;
    int timeUpdateting = 1;

public:

    ConverterJSON() = default;

    void updateConfigJSON();

    int getTimeUpdateting();

    void StartAndCheck(const float& appVersion);

    vector<string> getTextDocuments();

    vector<string> getRequests();

    void putAnswers(vector<vector<RelativeIndex>> answers);
};

#endif // CONVERTER_JSON_H
