#pragma once

#include <stdexcept>

namespace libzork
{

    class RunnerQuit : public std::exception
    {
    public:
        RunnerQuit() = default;
        ~RunnerQuit() override = default;
    };

    class RunnerInterrupt : public std::runtime_error
    {
    public:
        using super_type = std::runtime_error;
        using super_type::super_type;
        ~RunnerInterrupt() override = default;
    };

} // namespace libzork
