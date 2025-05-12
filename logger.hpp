// LOGGER_H
#pragma once

#include <cstdio>


enum class PropertyLevel {
    TRACE_LOG, DEBUG_LOG, ERROR_LOG, CRITICAL_LOG
};

class Logger {
    static PropertyLevel property_level;

public:
    template<typename... Args>
    static void trace_log(const char* msg, Args... args) {
        if (property_level <= PropertyLevel::TRACE_LOG) {
            std::printf("[TRACE]\t");
            std::printf(msg, args...);
            std::printf("\n");
        }
    }

    template<typename... Args>
    static void debug_log(const char* msg, Args... args) {
        if (property_level <= PropertyLevel::DEBUG_LOG) {
            std::printf("[DEBUG]\t");
            std::printf(msg, args...);
            std::printf("\n");
        }
    }

    template<typename... Args>
    static void error_log(const char* msg, Args... args) {
        if (property_level <= PropertyLevel::ERROR_LOG) {
            std::printf("[ERROR]\t");
            std::printf(msg, args...);
            std::printf("\n");
        }
    }

    template<typename... Args>
    static void critical_log(const char* msg, Args... args) {
        if (property_level <= PropertyLevel::CRITICAL_LOG) {
            std::printf("[CRITICAL]\t");
            std::printf(msg, args...);
            std::printf("\n");
        }
    }

    static void lvl(PropertyLevel l) {
        property_level = l;
    }
};

PropertyLevel Logger::property_level = PropertyLevel::ERROR_LOG;