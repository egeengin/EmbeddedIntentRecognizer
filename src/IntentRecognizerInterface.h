#ifndef EMBEDDEDINTENTRECOGNIZER_INTENTRECOGNIZERINTERFACE_H
#define EMBEDDEDINTENTRECOGNIZER_INTENTRECOGNIZERINTERFACE_H

#include <string>

// Interface of handling user commands to recognize the intent
// DESIGN PATTERN: Interface Design Pattern
class IntentRecognizerInterface {
public:
    IntentRecognizerInterface() {
    };

    virtual bool InputHandler(std::istream &input) = 0; //Any input stream method can be used like std::cin

    virtual bool HandleUserIntents(std::string line) = 0; //Test purposes

    virtual ~IntentRecognizerInterface() {
    };
};

#endif //EMBEDDEDINTENTRECOGNIZER_INTENTRECOGNIZERINTERFACE_H