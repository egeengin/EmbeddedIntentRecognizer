# Embedded Intent Recognizer

Embedded Intent Recognizer is a simple, small, case-insensitive intent recognition command line tool using modern C++. 

## Compilation

Run the following commands to create the binary. 

```bash
$ mkdir build && cmake .. && make
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
## Code structure

Embedded Intent Recognizer has the tree structure given below:

```bash
├─── src
│   ├─── CMakeList.txt
│   ├─── IntentRecognizer.cpp
│   ├─── IntentRecognizer.h
│   ├─── IntentRecognizerInterface.h
│   └─── main.cpp
├─── .gitignore
├─── LICENSE
└─── Readme.md
```

**Readme.md** is a readme file to describe how to code act and how to compile and run.

**CMakeList.txt** file contains a set of directives and instructions describing the project's source
files and targets (executable, library, or both).

**IntentRecognizer (.cpp, .h)** is the class for handling the command line inputs and recognize the intents. If intent 
can not be found, requests a new input. Single enter (without query) and Linux escape (ctrl+c) are handled
as an exit. IntentRecognizer follows the singleton and factory design approaches. The singleton design
approach is used because exactly one intent recognizer is needed to coordinate command-line
actions across the system. A superclass specifies all standard and generic behavior (using pure virtual
"placeholders" for creation steps), and then delegates the creation details to subclasses that are supplied by the 
client in factory design pattern. In this project, there is a factory of handlers having set, get, delete handlers. 
By the advantage of this pattern, any new query can be added as new handler easily.

**IntentRecognizerInterface.h** is the header file for Intent Recognizer Interface class, it consists of a pure
virtual class and any change on the command handler can be handled thanks to the adapter design pattern.

## Used third-party tools

This project is built, tested, and documented using some third-party tools and services listed below.
I would like to thank them.

- [Google Test](https://github.com/google/googletest): Google Test freamwork is used for unit tests.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

MIT License

Copyright (c) [2022] [Ege ENGIN]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.