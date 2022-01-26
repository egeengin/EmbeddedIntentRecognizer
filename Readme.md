# Embedded Intent Recognizer

Embedded Intent Recognizer is a simple, small, case-insensitive intent recognition command line tool using modern C++.
User can fill the human-readable .json file easily with "word": "intent" pairs as in sample file to handle user-specific
word-intent pairs. If new intent is introduced, new intent class must be inserted in Intent class and called on
IntentFactory class.

## Compilation

Run the following commands to create the binary.

```bash
$ mkdir build && cd build && cmake .. && make
```

## Usage

Example usage is given below:

```bash
$ ./EmbeddedIntentRecognizer
> What is the weather like today?
Intent: Get Weather
> What is the weather like in Paris today?
Intent: Get Weather City
> Tell me an interesting fact.
Intent: Get Fact
> Make me a joke.
Intent: Not Found, Please Try Again
> What is the weAthEr. like in Paris today?
Intent: Get Weather City
>
```

## Input modification

Word2Intent.json file in data directory should contain word to intent pairs as stated below:

```json
{
  "fact": "fact",
  "weather": "weather",
  "sunny": "weather",
  "ANKARA": "city"
}
```

This example states that when word "fact" is handled the intent "Fact" will be returned. Likewise, when "weather" or "
sunny" is handled, intent "Weather" will be returned. For "Weather City" intent, it is needed to get "weather" and "
city" intents together to be handled.

**Note:** Optional configuration of intents can be done in IntentFactory class.

## Code structure

Embedded Intent Recognizer has the tree structure given below:

```bash
├─── data
│   ├─── Word2Intent.json
├─── lib
│   ├─── nlohmann
│       ├─── json.hpp
├─── src
│   ├─── CMakeList.txt
│   ├─── Intent.cpp
│   ├─── Intent.h
│   ├─── IntentFactory.cpp
│   ├─── IntentFactory.h
│   ├─── IntentRecognizer.cpp
│   ├─── IntentRecognizer.h
│   ├─── IntentRecognizerInterface.h
│   ├─── main.cpp
│   ├─── TrieWithIntents.cpp
│   └─── TrieWithIntents.h
├─── tst
│   ├─── CMakeList.txt
│   ├─── main.cpp
│   └─── testIntentRecognizer.cpp
├─── .gitignore
├─── LICENSE
└─── Readme.md
```

**Readme.md** is a readme file to describe how to code act and how to compile and run.

**CMakeList.txt** file contains a set of directives and instructions describing the project's source files and targets (
executable, library, or both).

**IntentRecognizer (.cpp, .h)** is the class for handling the command line inputs and recognize the intents. If intent
can not be found, requests a new input. Single enter (without query) and Linux escape (ctrl+c) are handled as an exit.
IntentRecognizer follows the singleton and factory design approaches. The singleton design approach is used because
exactly one intent recognizer is needed to coordinate command-line actions across the system. IntentRecognizer first
initializes the modified Trie using TrieWithIntents class with the inputs in Word2Intent.json handled using nlohmann::
json library.

**IntentRecognizerInterface.h** is the header file for Intent Recognizer Interface class, it consists of a pure virtual
class and any change on the intent recognizer handler can be handled thanks to the adapter design pattern.

**IntentFactory (.cpp, .h)** is the class for getting Intent objects. This class has a Simple factory pattern that it
has one creation method with a large conditional that based on method parameters chooses which product class to
instantiate and then return. The returned Intent objects can be called with their handle methods in IntentRecognizer. By
the advantage of this pattern, any new inserted query can be called easily.

**Intent (.cpp, .h)** is the class for creating Intent objects. Current supported intents are {"Weather","Weather City"
, "Fact"}. A new intent can be inserted with its handle to enlarge recognition capability to be called in IntentFactory.

**TrieWithIntents (.cpp, .h)** is the class to create modified Trie which is a Trie having ID on their bottom leaf.

**testIntentRecognizer (.cpp,)** is the test file for IntentRecognizer class using Google Test.

## Used third-party tools

This project is built, tested, and documented using some third-party tools and services listed below. All third-party
libraries are placed under the lib directory. I would like to thank them.

### [Nlohman-Json](https://github.com/nlohmann/json): JSON for Modern C++

Nlohmann library is used for retrieving word-intent pairs in json file which is commonly used for any key-pair storage.
The reasons for selecting this library can be counted as:

- Wide aspect of usage such that any device that wants to operate with this file can.
- Easy adaptation: Any change on words or intents stored in json file affects program on first run.
- Easy to use: Inside functions can be called with a brief introduction and add single hpp to use the library
- Human-readable file: User can enter and check their word-intent pairs with any text editor. Of course, for security
  reasons, any cryptography application can be adapted.

### [Google Test](https://github.com/google/googletest): Google Test framework

GoogleTest is Google’s C++ testing and mocking framework. The GoogleTest is used for unit tests in this project due to
the following reasons:

- Platform independence (Linux, Mac, Windows)
- Independent and repeatable tests
- Easy to adapt and use
- Portability: Can portable between different compilers
- Speed: The tests run fast.

With configurations on CMakeLists.txt, the Google Test content is fetched. To follow current Google Test commits, it is
useful to update URL in CMakeLists.txt frequently.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

MIT License

Copyright (c) [2022] [Ege ENGIN]

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.