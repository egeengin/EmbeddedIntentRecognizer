#ifndef EMBEDDEDINTENTRECOGNIZER_INTENTRECOGNIZER_H
#define EMBEDDEDINTENTRECOGNIZER_INTENTRECOGNIZER_H

#include <string>
#include "IntentRecognizerInterface.h"

class Intent {
public:
    static const int num_intent = 3;
    const std::string intentList[num_intent] = {"weather", "city", "fact"};
    const int max_arg_num = 15;
    std::string name;
};

// Handle command line commands
// DESIGN PATTERN: Factory Design Pattern
class IntentRecognizer : public IntentRecognizerInterface {
public:
    IntentRecognizer() = default;

    static IntentRecognizer &GetHandler();

    IntentRecognizer(const IntentRecognizer &orig) = delete;

    virtual bool Handle(Intent intent) ;

    bool InputHandler(std::istream &input) override;

    bool HandleUserIntents(std::string line) override;

    virtual ~IntentRecognizer();

private:
    IntentRecognizer *MakeIntentRecognizer(Intent intent);

    bool LineParser(std::string input_str, Intent &intent);

    void LowerString(std::string &input_str);

    void PrintWrongInput();
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
