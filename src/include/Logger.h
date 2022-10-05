#pragma once

#include <mutex>
#include <string>
#include <iostream>

namespace gbg {

class Logger
{
public:
	static Logger &getInstance()
	{
		static Logger instance;
		return instance;
	}

	template<typename T>
	Logger &operator<<(const T &msg)
	{
		auto lock = std::lock_guard<std::mutex>(m_logMutex);

		std::cout << msg;

		return *this;
	}
private:
	std::mutex m_logMutex;
};

constexpr auto Log = Logger::getInstance;

}
