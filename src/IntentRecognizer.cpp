#include <string>
#include <iostream>
#include <sstream>

#include "IntentRecognizer.h"

// #define DEBUG

using namespace std;

// IntentRecognizer returns the same instance to adapt singleton pattern
IntentRecognizer &IntentRecognizer::GetHandler() {
    static IntentRecognizer handler;
    return handler;
}

bool WeatherIntentRecognizer::Handle(Intent intent) {
    cout << "Intent: Get Weather" << endl;
    return EXIT_SUCCESS;
}

bool WeatherCityIntentRecognizer::Handle(Intent intent) {
    cout << "Intent: Get Weather City" << endl;
    return EXIT_SUCCESS;
}

bool FactIntentRecognizer::Handle(Intent intent) {
    cout << "Intent: Get Fact" << endl;
    return EXIT_SUCCESS;
}

bool NotFoundIntentRecognizer::Handle(Intent intent) {
#ifdef EXIT_AFTER_WRONG_INPUT
    cout << "Intent: Not found" << endl;
    return EXIT_FAILURE; // If exit after wrong input is the specification
#else
    cout << "Intent: Not Found, Please Try Again" << endl;
    return EXIT_SUCCESS; // If continue processing after wrong input is the specification
#endif
}

bool IntentRecognizer::LineParser(std::string input_str, Intent &intent) {
    stringstream s(input_str);
    string word;
    int num = 0, intent_id;

    static bool initialized;
    if (!initialized) {
        initialized = true;
        InitTrie();
    }

    intent.ID.clear();
    while (s >> word) {
        MakeLowerCase(word);
        intent_id = headTrie->search(word);
#ifdef DEBUG
        cout << "Word: " << word << " -> Intent: " << intentList[intent_id] << endl;
#endif
        if (intent_id)
            intent.ID.insert(intent_id);
        num++;
    }

    // Check argument num
    if (num == 0) { // Enter returns as exit function
        return EXIT_FAILURE;   // Return to command line, Exit Function
    } else if (num >= intent.max_arg_num) {
        PrintWrongInput();
        return EXIT_FAILURE;
    } else {
        return EXIT_SUCCESS;
    }
}

void IntentRecognizer::MakeLowerCase(std::string &input_str) {
    int j = 0;
    for (int i = 0; i < input_str.size(); i++) {
        // Store only letters until non-alphabet characters {'.',',',';',...)
        if (input_str[i] >= 'A' && input_str[i] <= 'Z') {
            input_str[j] = input_str[i] - 'Z' + 'z';
            j++;
        } else if (input_str[i] >= 'a' && input_str[i] <= 'z') {
            input_str[j] = input_str[i];
            j++;
        } else {
            input_str = input_str.substr(0, j);
            break;
        }
    }
}

void IntentRecognizer::PrintWrongInput() {
    cout << "Wrong input" << endl;
}

void IntentRecognizer::InitTrie() {
    int intentId;

    auto GetIndex = [](vector<string> S, std::string K) {
        int Index = 0;
        // Traverse the vector
        for (auto u: S) {
            if (u == K)
                return Index;
            Index++;
        }
        return -1; // If not in vector
    };

    for (const auto&[word, intent]: wordIntentMap) {
        intentId = GetIndex(intentList, intent);
        if (intentId != -1) {
            headTrie->insert(word, intentId);
        }
#ifdef DEBUG
        else
            cout << "Not in intent list but in a map: " << intent << endl;
#endif
    }

}

IntentRecognizer *IntentRecognizer::MakeIntentRecognizer(Intent intent) {
    if (intent.ID.size() == 1) {
        for (const int &id: intent.ID) {
#ifdef DEBUG
            cout << "Intents found: " << intentList[id] << endl;
#endif
            switch (id) {
                case 1:
                    return new WeatherIntentRecognizer;
                case 3:
                    return new FactIntentRecognizer;
                default:
                    return new NotFoundIntentRecognizer;
            }
        }
    } else if (intent.ID.size() == 2) {
        bool isWeatherInSet = intent.ID.find(1) != intent.ID.end();
        bool isCityInSet = intent.ID.find(2) != intent.ID.end();
        if (isWeatherInSet && isCityInSet)
            return new WeatherCityIntentRecognizer;
        else
            return new NotFoundIntentRecognizer; // not recognized
    } else {
        return new NotFoundIntentRecognizer; // not recognized
    }
}

bool IntentRecognizer::HandleUserIntents(std::string line) {
    Intent intent;
    IntentRecognizer *intentRecognizer;
    if (LineParser(line, intent)) {
        return EXIT_FAILURE; // Exit sequence is entered
    } else {
        intentRecognizer = MakeIntentRecognizer(intent);
    }
    intentRecognizer->Handle(intent);
    delete intentRecognizer;
    return EXIT_SUCCESS;
}

bool IntentRecognizer::InputHandler(std::istream &input = std::cin) {
    string line;
    getline(input, line);
    return HandleUserIntents(line);
}

IntentRecognizer::~IntentRecognizer() {

}

bool IntentRecognizer::Handle(Intent intent) {
    return EXIT_FAILURE;
}
