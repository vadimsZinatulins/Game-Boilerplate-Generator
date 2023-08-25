#include "utils/replaceAll.h"

std::string replaceAll(const std::string &subject, const ReplaceContent &replaceContent) {
    std::string result = subject;

    for(const auto pair : replaceContent) {
        auto search { pair.first };
        auto replace { pair.second };

        size_t pos = 0;
        while((pos = result.find(search, 0)) != std::string::npos) {
            result.replace(pos, search.length(), replace);
        }
    }

    return result;
}