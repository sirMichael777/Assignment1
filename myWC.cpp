#include "myWC.h"
#include <iostream>
#include <vector>
#include <cctype>
#include <sstream>
#include <algorithm>

namespace MSKMIC017 {
    void countCharsWordsLinesAndPrint() {
        std::string line;
        long lineCount = 0;
        long wordCount = 0;
        long charCount = 0;
        std::vector<CharInfo> charFreq;

        while (std::getline(std::cin, line)) {
            ++lineCount;
            bool hasAlphanumeric = false;

            std::istringstream iss(line);
            std::string word;
            while (iss >> word) {
                bool hasWordAlphanumeric = false;
                if (!word.empty()) { // Check if the word is not empty
                    ++wordCount;
                    for (char c : word) {
                        if (std::isalnum(c)) {
                            ++charCount;
                            char ch = std::tolower(c);
                            auto it = std::find_if(charFreq.begin(), charFreq.end(), [ch](const CharInfo& info) {
                                return info.character == ch;
                            });
                            if (it != charFreq.end()) {
                                ++it->count;
                            } else {
                                charFreq.push_back({ch, 1});
                            }
                            hasWordAlphanumeric = true;
                        }
                    }
                }
                hasAlphanumeric |= hasWordAlphanumeric;
            }
            if (!hasAlphanumeric) {
                --wordCount;
            }
        }

        // Sort alphabetically
        std::sort(charFreq.begin(), charFreq.end(), [](const CharInfo& a, const CharInfo& b) {
            return a.character < b.character;
        });

        // prints out the number of lines, words and characters
        std::cout << lineCount << " " << wordCount << " " << charCount << " [";

        // Print the character frequency table to the console
        for (const CharInfo& info : charFreq) {
            std::cout << info.character << ":" << info.count << " ";
        }

        std::cout << "]" << std::endl; 
    }
}
