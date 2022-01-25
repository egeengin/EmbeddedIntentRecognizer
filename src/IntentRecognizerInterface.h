#ifndef EMBEDDEDINTENTRECOGNIZER_INTENTRECOGNIZERINTERFACE_H
#define EMBEDDEDINTENTRECOGNIZER_INTENTRECOGNIZERINTERFACE_H

#include <string>

// Interface of handling user commands to recognize the intent
// DESIGN PATTERN: Interface Design Pattern
class IntentRecognizerInterface {
public:
    IntentRecognizerInterface() = default;

    virtual std::string GetLine(std::istream &input) = 0; //Any input stream method can be used like std::cin

    virtual bool RecognizeIntents(std::string line) = 0; //Test purposes

    virtual ~IntentRecognizerInterface() = default;
};

#endif //EMBEDDEDINTENTRECOGNIZER_INTENTRECOGNIZERINTERFACE_H