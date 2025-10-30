#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "converter_json.h"


void ConverterJSON::updateConfigJSON()
{
    configJSON.clear();
    ifstream file("config.json");
    if(!file.is_open())
    {
        throw string("config file is missing");
    }
    file >> configJSON;
    file.close();
};

void ConverterJSON::StartAndCheck(const float& appVersion)
{
    updateConfigJSON();

    if(!configJSON.contains("config"))
    {
        throw string("config file is empty");
    }

    if((float)configJSON["config"]["version"] != appVersion)
    {
        throw string("config.json has incorrect file version");
    }

    if(configJSON["config"].contains("name"))
    {
        cout << "Starting: " << configJSON["config"]["name"] << endl;
    }

    cout << "Version: " << configJSON["config"]["version"] << endl;

    if(configJSON["config"].contains("max_responses")
        && configJSON["config"]["max_responses"].is_number_integer())
    {
        responsesLimit = configJSON["config"]["max_responses"];
    }
    cout << "Max count of responses: " << responsesLimit << endl;

    if(configJSON["config"].contains("time_updateting")
        && configJSON["config"]["time_updateting"].is_number_integer())
    {
        timeUpdateting = configJSON["config"]["time_updateting"];
    }
    cout << "Frequency of database updates(minutes): "
         << timeUpdateting << endl << endl;
};

vector<string> ConverterJSON::getTextDocuments()
{
    vector<string> textDocuments;

    for(auto i = 0; i < configJSON.at("files").size(); i++)
    {
        ifstream txtFile(configJSON["files"][i]);
        textDocuments.push_back("");
        if(!txtFile.is_open())
        {
            cerr << "File " << configJSON["files"][i] << " not found!" << endl;
            continue;
        }
        getline(txtFile, textDocuments[i]);
        txtFile.close();
    }
    return textDocuments;
}

int ConverterJSON::getTimeUpdateting()
{
    return timeUpdateting;
}

vector<string> ConverterJSON::getRequests()
{
        vector<string> requests;

        ifstream file("requests.json");
        if(!file.is_open())
        {
            throw string("requests file is missing");
        }
        file >> requestsJSON;
        file.close();
        if(!requestsJSON.contains("requests"))
        {
            throw string("requests file is empty");
        }

        for(auto i = 0; i < requestsJSON.at("requests").size(); i++)
        {
            requests.push_back("");
            requests[i] = requestsJSON["requests"][i];
        }
        return requests;
}

void ConverterJSON::putAnswers(const vector<vector<RelativeIndex>>& answers)
{
    for(auto i = 0; i < answers.size(); i++)
    {
        stringstream num;
        num << setw(3) << setfill('0') << (i+1);
        string requestNum = "request" + num.str();

        if(answers[i].size() > 0)
        {
            answersJSON["answers"][requestNum]["result"] = true;
            for(auto j = 0; j < answers[i].size() && j < responsesLimit; j++)
            {
                answersJSON["answers"][requestNum]["relevance"][j]["docid"] = answers[i][j].doc_id;
                answersJSON["answers"][requestNum]["relevance"][j]["rank"] = answers[i][j].rank;
            }
        }
        else
        {
            answersJSON["answers"][requestNum]["result"] = false;
        }
    }
    ofstream file("answers.json");
    if(file.is_open())
    {
        file << answersJSON.dump(4);
        file.close();
    }
    else cerr << "answers.json could not be created!" << endl;
}
