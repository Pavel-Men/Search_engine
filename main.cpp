#include <iostream>
#include "lib/converter_json.h"
#include "lib/inverted_index.h"
#include "lib/search_server.h"
#include <thread>
#include <ctime>

const float version = 1.0;

int main()
{
    ConverterJSON converterJson;
    InvertedIndex invertedIndex;
    SearchServer searchServer(invertedIndex);

    try
    {
        converterJson.StartAndCheck(version);
    }
    catch (const string& error_message)
    {
        cerr << "Error: " << error_message << endl;
        cin.get();
        return 1;
    }

    thread program([&converterJson, &invertedIndex, &searchServer]()
    {
        while(true)
        {
            invertedIndex.updateDocumentBase(converterJson.getTextDocuments());

            try
            {
                converterJson.putAnswers(searchServer.search(converterJson.getRequests()));
            }
            catch (const string& error_message)
            {
                cerr << "Error: " << error_message << endl;
                return;
            }

            cout << "The database has been updated! ";

            time_t currentTime = time(nullptr);

            cout <<ctime(&currentTime);

            this_thread::sleep_for(chrono::minutes(converterJson.getTimeUpdateting()));
        }
    });
    program.detach();

    string cmd;
    while(cmd != "exit")
    {
        cout << "Enter \"exit\" for close app: " << endl;
        cin >> cmd;
    }
    return 0;
}
