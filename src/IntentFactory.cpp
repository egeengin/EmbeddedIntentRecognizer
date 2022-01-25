#include "IntentFactory.h"

//#define DEBUG

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

// IntentFactory returns the same instance to adapt singleton pattern
IntentFactory &IntentFactory::GetHandler() {
    static IntentFactory handler;
    return handler;
}

Intent *IntentFactory::GetIntent(std::set<int> intentIDList) {
    if (intentIDList.size() == 1) {
        for (const int &id: intentIDList) {
#ifdef DEBUG
            cout << "Intents found for ID: " << id << endl;
#endif
            switch (id) {
                case 1:
                    return new WeatherIntent;
                case 3:
                    return new FactIntent;
                default:
                    return new NotFoundIntent;
            }
        }
    } else if (intentIDList.size() == 2) {
        bool isWeatherInSet = intentIDList.find(1) != intentIDList.end();
        bool isCityInSet = intentIDList.find(2) != intentIDList.end();
        if (isWeatherInSet && isCityInSet)
            return new WeatherCityIntent;
        else
            return new NotFoundIntent; // not recognized
    }
    return new NotFoundIntent; // not recognized
}