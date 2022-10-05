#include "utils/ArgsParser.h"

#include <sstream>
#include <vector>

namespace gbg::utils {

ArgsParser::ArgsParser(int argc, char *argv[]) : m_arguments({argv + 1, argv + argc}) {} 
ArgsParser::~ArgsParser() {}

void ArgsParser::addAction(std::set<std::string> params, std::function<void()> action) {
	for(const auto &arg : params) {
		m_actions[arg] = [action] (std::vector<std::string> &, std::size_t&) { action(); };
	}
}

void ArgsParser::addAction(std::set<std::string> params, std::function<void(std::string)> action) {
	for(const auto &arg : params) {
		m_actions[arg] = [action] (std::vector<std::string> &args, std::size_t &index) { action(args[++index]); };
	}
}

void ArgsParser::parse() {
	for(std::size_t i = 0; i < m_arguments.size(); ++i) {
		auto ptr = m_actions.find(m_arguments[i]);
		if(ptr != m_actions.end()) {
			ptr->second(m_arguments, i);
		}
	}
}

}
