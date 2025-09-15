
#include "Timestamp.h"

Timestamp::Timestamp():timepoint_(std::chrono::system_clock::now())
{
}

Timestamp::Timestamp(std::chrono::time_point<std::chrono::system_clock> timepoint): timepoint_(timepoint) 
{
}

// 当前时间。
Timestamp Timestamp::now() 
{ 
    return Timestamp();   // 返回当前时间。
}

std::chrono::system_clock::time_point Timestamp::timepoint() const
{
    return timepoint_;
}
time_t Timestamp::timestamp() const
{
    return std::chrono::system_clock::to_time_t(timepoint_);
}

std::string Timestamp::tostring() const

{
    return std::format("{:%Y-%m-%d %H:%M:%S}",std::chrono::time_point_cast<std::chrono::seconds>(timepoint_+8h));
}


