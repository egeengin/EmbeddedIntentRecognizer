#ifndef EMBEDDEDINTENTRECOGNIZER_INTENTFACTORY_H
#define EMBEDDEDINTENTRECOGNIZER_INTENTFACTORY_H

#include "IntentFactory.h"
#include "Intent.h"

#include <string>
#include <set>
#include <vector>

// DESIGN PATTERN: Singleton and Factor Design Patterns
class IntentFactory {
public:
    IntentFactory() = default;

    std::vector<std::string> intentList{"not_found", "weather", "city", "fact"};

    static IntentFactory &GetHandler();

    Intent *GetIntent(std::set<int> intentIDList);
};


#endif //EMBEDDEDINTENTRECOGNIZER_INTENTFACTORY_H
