#include "utils/StringTrim.h"

const char *TRIM_VALUE = " \t\n\r\f\v";

void lTrim(std::string &s) {
	s.erase(0, s.find_first_not_of(TRIM_VALUE));
}

void rTrim(std::string &s) {
	s.erase(s.find_last_not_of(TRIM_VALUE) + 1);
}

void trim(std::string &s) {
	lTrim(s);
	rTrim(s);
}
