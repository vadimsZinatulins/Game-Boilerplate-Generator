#include "utils/replaceAll.h"

std::string replaceAll(const std::string &subject, const std::string &search, const std::string &replace) {
    std::string result = subject;
    size_t pos = 0;
    while((pos = result.find(search, 0)) != std::string::npos) {
        result.replace(pos, search.length(), replace);
    }
    return result;
}