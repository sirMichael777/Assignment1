#include "myWC.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

namespace MSKMIC017 {

    // Function to check if a character is alphanumeric
    bool myIsAlnum(char c) {
        return (c >= 'a' && c <= 'z') ||
               (c >= 'A' && c <= 'Z') ||
               (c >= '0' && c <= '9');
    }

    void countCharsWordsLinesAndPrint() {
        std::string line;
        long lineCount = 0;
        long wordCount = 0;
        long characterCount = 0;
        std::vector<CharInfo> characterFrequency;

        while (std::getline(std::cin, line)) {
            ++lineCount;
            bool hasAlphanumeric = false;

            std::istringstream iss(line);
            std::string word;
            bool lineHasWord = false;
            while (iss >> word) {
                bool hasWordAlphanumeric = false;
                if (!word.empty()) {
                    ++wordCount;
                    lineHasWord = true;
                    for (char c : word) {
                        if (myIsAlnum(c)) { // Using custom function myIsAlnum instead of std::isalnum
                            ++characterCount;
                            char ch = std::tolower(c);
                            auto it = std::find_if(characterFrequency.begin(), characterFrequency.end(), [ch](const CharInfo& info) {
                                return info.character == ch;
                            });
                            if (it != characterFrequency.end()) {
                                ++it->count;
                            } else {
                                characterFrequency.push_back({ch, 1});
                            }
                            hasWordAlphanumeric = true;
                        }
                    }
                }
                
                hasAlphanumeric |= hasWordAlphanumeric;
            }
        }

        std::sort(characterFrequency.begin(), characterFrequency.end(), [](const CharInfo& a, const CharInfo& b) {
            return a.character < b.character;
        });

        std::cout << lineCount << " " << wordCount << " " << characterCount << " [";

        for (const CharInfo& info : characterFrequency) {
            std::cout << info.character << ":" << info.count << " ";
        }

        std::cout << "]" << std::endl; 
    }
}
