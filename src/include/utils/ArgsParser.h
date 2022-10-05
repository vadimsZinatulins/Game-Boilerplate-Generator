#pragma once

#include <set>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>

namespace gbg::utils {

/**
 *	@brief Simple command line argument parser
 */
class ArgsParser {
public:
	ArgsParser(int argc, char *argv[]);
	~ArgsParser();

	/**
	 * @brief Adds an action to execute whenever a specific argument is found.
	 * @param params Set of arguments to search for.
	 * @param action The corresponding action to execute whenever a required param is found
	 */
	void addAction(std::set<std::string> params, std::function<void()> action);

	/**
	 * @brief Adds an action to execute whenever a specific argument is found and there is a requirement for
	 * an associated parameter.
	 * @param params Set of arguments to search for.
	 * @param action The corresponding action to execute whenever a required param is found
	 */
	void addAction(std::set<std::string> params, std::function<void(std::string)> action);

	/**
	 * @brief parse the arguments
	 */
	void parse();
private:
	std::vector<std::string> m_arguments;
	std::unordered_map<std::string, std::function<void(std::vector<std::string> &, std::size_t&)>> m_actions;
};

}
