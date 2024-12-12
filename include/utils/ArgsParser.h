#pragma once

#include <set>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include <optional>

namespace gbg::utils {

/**
 * @brief Enhanced command line argument parser using the Builder pattern
 */
class ArgsParser {
    class ArgumentBuilder;
public:
    /**
	 * @brief Adds an action to execute whenever a specific argument is found.
	 * @param params Set of arguments to search for.
	 * @param action The corresponding action to execute whenever a required param is found
	 */
    bool parse(int argc, char *argv[]);

    /**
     * @brief Creates a builder for defining a new argument
     * @param flag Primary flag for the argument (e.g., "--help")
     * @return Builder object for method chaining
     */
    ArgumentBuilder arg(const std::string& flag);

    /**
     * @brief Get help text for all registered arguments
     */
    std::string getHelpText() const;

private:
    std::string m_programName;
    
    struct ArgumentData {
        std::set<std::string> flags;
        std::string description;
        bool required = false;
        bool requiresValue = false;
        bool earlyExit = false;
        std::optional<std::string> defaultValue;
        std::function<void(std::vector<std::string>&, std::size_t&)> action;
    };

    std::vector<ArgumentData> m_argumentData;
    std::unordered_map<std::string, std::function<void(std::vector<std::string>&, std::size_t&)>> m_actions;

    // Inner builder class
    class ArgumentBuilder {
    public:
        /**
         * @brief Add an alias flag for this argument
         * @param alias Alternative flag (e.g., "-h" as alias for "--help")
         */
        ArgumentBuilder& alias(const std::string& alias);

        /**
         * @brief Add multiple alias flags
         * @param aliases Set of alternative flags
         */
        ArgumentBuilder& aliases(const std::set<std::string>& aliases);

        /**
         * @brief Add description for help text
         */
        ArgumentBuilder& description(const std::string& desc);

        /**
         * @brief Mark this argument as required
         */
        ArgumentBuilder& required();

        /**
         * @brief Set default value for this argument
         */
        ArgumentBuilder& defaultValue(const std::string& value);

        /**
         * @brief Add an action for a flag without value
         */
        ArgumentBuilder& action(std::function<void()> action);

        /**
         * @brief Add an action for a flag with value
         */
        ArgumentBuilder& valueAction(std::function<void(std::string)> action);

        /**
         * @brief Finalize the argument definition
         */
        ArgsParser& build();

        /**
         * @brief Mark this argument as requiring early exit
         */
        ArgumentBuilder& earlyExit();

    private:
        friend class ArgsParser;
        ArgumentBuilder(ArgsParser& parser, const std::string& flag);
        
        ArgsParser& m_parser;
        ArgumentData m_data;
    };
};

}
