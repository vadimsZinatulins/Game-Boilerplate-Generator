#include "utils/ArgsParser.h"
#include <sstream>
#include <algorithm>
#include <filesystem>

namespace gbg::utils {

struct ArgumentData {
    std::set<std::string> flags;
    std::string description;
    bool required = false;
    bool requiresValue = false;
    bool earlyExit = false;
    std::optional<std::string> defaultValue;
    std::function<void(std::vector<std::string>&, std::size_t&)> action;
};

ArgsParser::ArgumentBuilder ArgsParser::arg(const std::string& flag) {
    return ArgumentBuilder(*this, flag);
}

bool ArgsParser::parse(int argc, char *argv[]) {
	std::vector<std::string> arguments(argv + 1, argv + argc);

	// First pass: check for early exit flags
	for(const auto& arg : arguments) {
		// Find the argument data that matches this flag
		auto argData = std::find_if(m_argumentData.begin(), m_argumentData.end(),
			[&arg](const ArgumentData& data) {
				return data.flags.find(arg) != data.flags.end();
			});

		if(argData != m_argumentData.end() && argData->earlyExit) {
			// Find the action and execute it
			auto it = m_actions.find(arg);
			if(it != m_actions.end()) {
				std::size_t index = 0;
				it->second(arguments, index);
				return false;  // Indicate early exit
			}
		}
	}

    // Check required arguments and collect missing ones
    std::vector<std::string> missingArgs;
    for(const auto& arg : m_argumentData) {
        if(arg.required) {
            bool found = false;
            for(const auto& flag : arg.flags) {
                if(std::find(arguments.begin(), arguments.end(), flag) != arguments.end()) {
                    found = true;
                    break;
                }
            }
            if(!found && !arg.defaultValue) {
                missingArgs.push_back(*arg.flags.begin());
            }
        }
    }
    
    if(!missingArgs.empty()) {
        std::stringstream errorMsg;
        errorMsg << "Required arguments missing:";
        for(const auto& arg : missingArgs) {
            errorMsg << " " << arg;
        }
        throw std::runtime_error(errorMsg.str());
    }

    for(std::size_t i = 0; i < arguments.size(); ++i) {
        auto it = m_actions.find(arguments[i]);
        if(it != m_actions.end()) {
            it->second(arguments, i);
		}	
    }

    return true;  // Indicate normal execution
}

std::string ArgsParser::getHelpText() const {
    std::stringstream ss;
    ss << "Usage: gbgen --name PROJECT_NAME [OPTIONS...]\n";
    ss << "Generates a base game structure that uses SDL3 (and optionally SDL3_Image) ready to build using CMake\n\n";
    ss << "List of options:\n";

    // First pass to find the longest flag combination
    size_t maxFlagLength = 0;
    for(const auto& arg : m_argumentData) {
        std::string flagsStr;
        bool first = true;
        for(const auto& flag : arg.flags) {
            if(!first) {
                flagsStr += ",\t";
            }
            flagsStr += flag;
            first = false;
        }
        if(arg.requiresValue) {
            flagsStr += " <value>";
        }
        maxFlagLength = std::max(maxFlagLength, flagsStr.length());
    }

    // Add padding to align to next tab stop
    maxFlagLength = ((maxFlagLength + 8) / 8) * 8;

    for(const auto& arg : m_argumentData) {
        ss << "\t";
        
        // Format flags
        std::string flagsStr;
        bool first = true;
        for(const auto& flag : arg.flags) {
            if(!first) {
                flagsStr += ",\t";
            }
            flagsStr += flag;
            first = false;
        }

        // Add value placeholder if needed
        if(arg.requiresValue) {
            flagsStr += " <value>";
        }

        ss << flagsStr;

        // Add padding spaces for alignment
        size_t padding = maxFlagLength - flagsStr.length();
        ss << std::string(padding, ' ');

        // Add description and metadata
        ss << arg.description;
        if(arg.defaultValue) {
            ss << " (default: " << *arg.defaultValue << ")";
        }
        if(arg.required) {
            ss << " (required)";
        }
        ss << "\n";
    }

    return ss.str();
}

// ArgumentBuilder implementation
ArgsParser::ArgumentBuilder::ArgumentBuilder(ArgsParser& parser, const std::string& flag)
    : m_parser(parser) {
    m_data.flags.insert(flag);
}

ArgsParser::ArgumentBuilder& ArgsParser::ArgumentBuilder::alias(const std::string& alias) {
    m_data.flags.insert(alias);
    return *this;
}

ArgsParser::ArgumentBuilder& ArgsParser::ArgumentBuilder::aliases(const std::set<std::string>& aliases) {
    m_data.flags.insert(aliases.begin(), aliases.end());
    return *this;
}

ArgsParser::ArgumentBuilder& ArgsParser::ArgumentBuilder::description(const std::string& desc) {
    m_data.description = desc;
    return *this;
}

ArgsParser::ArgumentBuilder& ArgsParser::ArgumentBuilder::required() {
    m_data.required = true;
    return *this;
}

ArgsParser::ArgumentBuilder& ArgsParser::ArgumentBuilder::defaultValue(const std::string& value) {
    m_data.defaultValue = value;
    return *this;
}

ArgsParser::ArgumentBuilder& ArgsParser::ArgumentBuilder::action(std::function<void()> action) {
    m_data.requiresValue = false;
    m_data.action = [action](std::vector<std::string>&, std::size_t&) {
        action();
    };
    return *this;
}

ArgsParser::ArgumentBuilder& ArgsParser::ArgumentBuilder::valueAction(std::function<void(std::string)> action) {
    m_data.requiresValue = true;
    m_data.action = [action](std::vector<std::string>& args, std::size_t& index) {
        if (index + 1 < args.size()) {
            action(args[++index]);
        }
    };
    return *this;
}

ArgsParser::ArgumentBuilder& ArgsParser::ArgumentBuilder::earlyExit() {
    m_data.earlyExit = true;
    return *this;
}

ArgsParser& ArgsParser::ArgumentBuilder::build() {
    // Store the argument data for help text generation
    m_parser.m_argumentData.push_back(m_data);

    // Register the action for all flags
    for (const auto& flag : m_data.flags) {
        m_parser.m_actions[flag] = m_data.action;
    }
    
    return m_parser;
}

}
