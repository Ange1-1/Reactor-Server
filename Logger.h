#pragma once
#include <source_location>
#include <print>
#include <string_view>

inline void log_info(std::string_view msg, const std::source_location& loc = std::source_location::current()) {
    std::println("[INFO][{}:{} {}] {}", loc.file_name(), loc.line(), loc.function_name(), msg);
}

inline void log_warn(std::string_view msg, const std::source_location& loc = std::source_location::current()) {
    std::println("[WARN][{}:{} {}] {}", loc.file_name(), loc.line(), loc.function_name(), msg);
}

inline void log_error(std::string_view msg, const std::source_location& loc = std::source_location::current()) {
    std::println("[ERROR][{}:{} {}] {}", loc.file_name(), loc.line(), loc.function_name(), msg);
}