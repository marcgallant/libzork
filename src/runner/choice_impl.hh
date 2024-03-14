#pragma once

#include <libzork/runner/choice.hh>

namespace libzork::runner
{
    class ChoiceRunnerImpl : public ChoiceRunner
    {
    public:
        ChoiceRunnerImpl(std::unique_ptr<story::Story> story, std::istream& is,
                         std::ostream& os);
        ~ChoiceRunnerImpl() override = default;

        void print_script() const override;
        void process_input() override;
    };

} // namespace libzork::runner
