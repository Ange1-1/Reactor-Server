#pragma once

#include <string>
#include <chrono>
#include <format>
using namespace std::chrono_literals;

// 时间戳
class Timestamp
{
private:
    std::chrono::system_clock::time_point timepoint_;          //时间点成员

public:
    Timestamp();                                       // 用当前系统时间点初始化对象。UTC+0
    Timestamp(std::chrono::system_clock::time_point timepoint);    // 用另一个时间点初始化对象。

    static Timestamp now();                     // 返回当前系统时间的Timestamp对象。

    std::chrono::system_clock::time_point timepoint() const;// 返回时间点成员。
    time_t timestamp() const;                            // 返回整数时间戳表示的时间。
    std::string tostring() const;                 // 返回字符串表示的时间，格式：yyyy-mm-dd hh24:mi:ss
};