#include <gtest/gtest.h>
#include <iostream>
#include "testIntentRecognizer.h"
#include "IntentRecognizer.h"

using namespace std;

IntentRecognizerInterface *pIntentRecognizer = &IntentRecognizer::GetHandler();

TEST(IntentRecognizerInterface_UnitTests, Weather) {
    string input_line = "What is the weather like today?";
    testing::internal::CaptureStdout();
    pIntentRecognizer->HandleUserIntents(input_line);
    string cmd_output = testing::internal::GetCapturedStdout();

    if (testIntentRecognizer::PrintInputs)
        std::cout << "Input: " << input_line << endl;

    EXPECT_EQ("Intent: Get Weather\n", cmd_output);
}

TEST(IntentRecognizerInterface_UnitTests, WeatherCity) {
    string input_line = "What is the weather like in Paris today?";
    testing::internal::CaptureStdout();
    pIntentRecognizer->HandleUserIntents(input_line);
    string cmd_output = testing::internal::GetCapturedStdout();

    if (testIntentRecognizer::PrintInputs)
        std::cout << "Input: " << input_line << endl;

    EXPECT_EQ("Intent: Get Weather City\n", cmd_output);
}

TEST(IntentRecognizerInterface_UnitTests, Fact) {
    string input_line = "Tell me an interesting fact.";
    testing::internal::CaptureStdout();
    pIntentRecognizer->HandleUserIntents(input_line);
    string cmd_output = testing::internal::GetCapturedStdout();

    if (testIntentRecognizer::PrintInputs)
        std::cout << "Input: " << input_line << endl;

    EXPECT_EQ("Intent: Get Fact\n", cmd_output);
}

TEST(IntentRecognizerInterface_UnitTests, NotFound) {
    string input_line = "Make me a joke.";
    testing::internal::CaptureStdout();
    pIntentRecognizer->HandleUserIntents(input_line);
    string cmd_output = testing::internal::GetCapturedStdout();

    if (testIntentRecognizer::PrintInputs)
        std::cout << "Input: " << input_line << endl;

    EXPECT_EQ("Intent: Not Found, Please Try Again\n", cmd_output);
}

TEST(IntentRecognizerInterface_UnitTests, WrongInput) {
    string input = "input";
    string input_line = "";

    for (int i = 0; i<15; i++)
    {
        input_line += input + " ";
    }

    testing::internal::CaptureStdout();
    pIntentRecognizer->HandleUserIntents(input_line);
    string cmd_output = testing::internal::GetCapturedStdout();

    if (testIntentRecognizer::PrintInputs)
        std::cout << "Input: " << input_line << endl;

    EXPECT_EQ("Wrong input\n", cmd_output);
}

TEST(IntentRecognizerInterface_UnitTests, Exit) {
    string input_line = "\n";
    testing::internal::CaptureStdout();
    pIntentRecognizer->HandleUserIntents(input_line);
    string cmd_output = testing::internal::GetCapturedStdout();

    if (testIntentRecognizer::PrintInputs)
        std::cout << "Input: " << input_line << endl;

    EXPECT_EQ("", cmd_output);
}