#pragma once

#include <mutex>
#include <string>
#include <iostream>

namespace gbg {

enum class LogType {
    Error,
    Info,
    Verbose
};

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void setVerbose(bool verbose) {
        m_verbose = verbose;
    }

    void log(const std::string& msg, LogType type = LogType::Info) {
        if (type == LogType::Verbose && !m_verbose) {
            return;
        }

        auto lock = std::lock_guard<std::mutex>(m_logMutex);
        auto& stream = (type == LogType::Error) ? std::cerr : std::cout;

        switch(type) {
            case LogType::Error:
                stream << "[ERROR] ";
                break;
            case LogType::Verbose:
                stream << "[VERBOSE] ";
                break;
            case LogType::Info:
            default:
                stream << "[INFO] ";
                break;
        }

        stream << msg << "\n";
    }

private:
    std::mutex m_logMutex;
    bool m_verbose{false};
};

inline auto& Log = Logger::getInstance;

} // namespace gbg
