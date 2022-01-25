#include "IntentRecognizer.h"

#include <signal.h>
#include <string>
#include <iostream>

using namespace std;

// Define the function to be called when ctrl-c (SIGINT) is sent to process
void signal_callback_handler(int signum) {
    exit(signum); // Terminate program
}

int main() {
    string line;
    IntentRecognizerInterface &intentRecognizer = IntentRecognizer::GetHandler();

    signal(SIGINT, signal_callback_handler); // Register signal and signal handler

    while (1) {
        line = intentRecognizer.GetLine(std::cin);
        if (intentRecognizer.RecognizeIntents(line))
            return EXIT_SUCCESS;
    }
}
