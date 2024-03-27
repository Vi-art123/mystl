#include "TimeCount.h"
#include <iostream>
#include <iomanip>

namespace mystd
{
    void TimeCount::test(const std::string& name, const std::function<void()>& test_func)
    {
        if (test_func == nullptr) return;

        auto start = std::chrono::high_resolution_clock::now();
        test_func();
        auto end = std::chrono::high_resolution_clock::now();
        auto time_count = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::time_t s_time = std::chrono::high_resolution_clock::to_time_t(start);
        std::time_t e_time = std::chrono::high_resolution_clock::to_time_t(end);
        auto mil_start = std::chrono::duration_cast<std::chrono::milliseconds>(start.time_since_epoch()).count()
                    - std::chrono::duration_cast<std::chrono::seconds>(start.time_since_epoch()).count() * 1000;
        auto mil_end = std::chrono::duration_cast<std::chrono::milliseconds>(end.time_since_epoch()).count()
                    - std::chrono::duration_cast<std::chrono::seconds>(end.time_since_epoch()).count() * 1000;
        std::cout << "<<" + name + ">>" << std::endl;
        std::cout << "start time:   " << std::put_time(std::localtime(&s_time), "%X.") << std::setfill('0') << std::setw(3) << mil_start << std::endl;
        std::cout << "end time:     " << std::put_time(std::localtime(&e_time), "%X.") << std::setfill('0') << std::setw(3) << mil_end << std::endl;
        std::cout << "elapsed time: " << std::fixed << static_cast<double>(time_count/1000000.0) << " s" << std::endl;
        std::cout << "------------------------------------------------------------------------------------------------------" << std::endl;
    }
} // namespace mystd
