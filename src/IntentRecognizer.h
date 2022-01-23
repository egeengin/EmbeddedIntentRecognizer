#ifndef EMBEDDEDINTENTRECOGNIZER_INTENTRECOGNIZER_H
#define EMBEDDEDINTENTRECOGNIZER_INTENTRECOGNIZER_H

#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include "IntentRecognizerInterface.h"
#include "TrieWithIntents.h"

class Intent {
public:
    const int max_arg_num = 15;
    std::set<int> ID;
};

// Handle command line commands
// DESIGN PATTERN: Factory Design Pattern
class IntentRecognizer : public IntentRecognizerInterface {
public:
    IntentRecognizer() = default;

    static IntentRecognizer &GetHandler();

    IntentRecognizer(const IntentRecognizer &orig) = delete;

    virtual bool Handle(Intent intent);

    bool InputHandler(std::istream &input) override;

    bool HandleUserIntents(std::string line) override;

    virtual ~IntentRecognizer();

private:
    TrieWithIntents *headTrie = new TrieWithIntents();

    std::vector<std::string> intentList{"not_found", "weather", "city", "fact"};

    std::unordered_map<std::string, std::string> wordIntentMap = {
            {"weather", "weather"},
            {"rainy",   "weather"},
            {"fact",    "fact"},
            {"in",      "city"},
    };

    IntentRecognizer *MakeIntentRecognizer(Intent intent);

    bool LineParser(std::string input_str, Intent &intent);

    void MakeLowerCase(std::string &input_str);

    void PrintWrongInput();

    void InitTrie();
};

// Simply add new intent recognizers if defined
class WeatherIntentRecognizer : public IntentRecognizer {
public:
    bool Handle(Intent intent);
};

class WeatherCityIntentRecognizer : public IntentRecognizer {
public:
    bool Handle(Intent intent);
};

class FactIntentRecognizer : public IntentRecognizer {
public:
    bool Handle(Intent intent);
};

class NotFoundIntentRecognizer : public IntentRecognizer {
public:
    bool Handle(Intent intent);
};

#endif //EMBEDDEDINTENTRECOGNIZER_INTENTRECOGNIZER_H
