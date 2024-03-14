#pragma once

#include <iostream>
#include <libzork/runner/runner.hh>

namespace libzork::runner
{

    class InteractiveRunner : public Runner
    {
    public:
        using Runner::Runner;

        InteractiveRunner(std::unique_ptr<story::Story> story,
                          std::istream& is = std::cin,
                          std::ostream& os = std::cout);

        ~InteractiveRunner() override = default;

        void run() override;

        virtual void print_script() const;
        virtual void process_input() = 0;

    protected:
        std::istream& is_;
        std::ostream& os_;
    };

} // namespace libzork::runner
