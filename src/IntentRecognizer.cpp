#include <string>
#include <iostream>
#include <sstream>

#include "IntentRecognizer.h"

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
    int num = 0;

    intent.name = "";
    while (s >> word) {
        LowerString(word);
        if (word == "weather") {
            intent.name = "weather";
        } else if (word == "fact") {
            intent.name = "fact";
        } else if ((word == "in") & (intent.name == "weather")) {
            intent.name = "city";
        }
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

void IntentRecognizer::LowerString(std::string &input_str) {
    int j = 0;
    for (int i = 0; i < input_str.size(); i++) {
        // Store only characters until non-alphabet characters {'.',',',';',...)
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

IntentRecognizer *IntentRecognizer::MakeIntentRecognizer(Intent intent) {
    if (intent.name == intent.intentList[0]) {
        return new WeatherIntentRecognizer;
    } else if (intent.name == intent.intentList[1]) {
        return new WeatherCityIntentRecognizer;
    } else if (intent.name == intent.intentList[2]) {
        return new FactIntentRecognizer;
    } else { // Intent not found
        return new NotFoundIntentRecognizer;
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
