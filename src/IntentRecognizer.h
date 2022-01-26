#ifndef EMBEDDEDINTENTRECOGNIZER_INTENTRECOGNIZER_H
#define EMBEDDEDINTENTRECOGNIZER_INTENTRECOGNIZER_H

#include "IntentRecognizerInterface.h"
#include "TrieWithIntents.h"
#include "IntentFactory.h"
#include "Intent.h"

#include "json.hpp"

#include <string>
#include <vector>
#include <set>
#include <unordered_map>

// Handle command line commands
// DESIGN PATTERN: Singleton Design Pattern
class IntentRecognizer : public IntentRecognizerInterface {
public:
    static IntentRecognizer &GetHandler();

    IntentRecognizer(const IntentRecognizer &orig) = delete;

    std::string GetLine(std::istream &input) override;

    bool RecognizeIntents(std::string line) override;

    virtual ~IntentRecognizer() = default;

private:
    const int maxArgNum = 15;

    TrieWithIntents *headTrie = new TrieWithIntents();

    IntentFactory &intentFactory = IntentFactory::GetHandler();

    std::set<int> listIntentID;

    std::unordered_map<std::string, std::string> wordIntentMap = {
            {"weather", "weather"},
            {"rainy",   "weather"},
            {"fact",    "fact"},
            {"in",      "city"},
    };

    inline static const std::string Word2IntentFile = "Word2Intent.json";

    bool ReadJsonFile(nlohmann::json &jsonObject, std::string fileName);

    IntentRecognizer();

    bool InitTrie();

    bool StringToIntentConverter(std::string input_str);

    void MakeLowerCase(std::string &inputStr);

    bool HandleIntent(Intent *intent);

    Intent *GetIntent();

    void PrintWrongInput();
};

#endif //EMBEDDEDINTENTRECOGNIZER_INTENTRECOGNIZER_H