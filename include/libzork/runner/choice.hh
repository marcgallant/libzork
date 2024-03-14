#pragma once

#include <libzork/runner/interactive.hh>

namespace libzork::runner
{

    class ChoiceRunner : public InteractiveRunner
    {
    public:
        using InteractiveRunner::InteractiveRunner;

        ~ChoiceRunner() override = default;
    };

    std::unique_ptr<ChoiceRunner>
    make_choice_runner(std::unique_ptr<story::Story> story,
                       std::istream& is = std::cin,
                       std::ostream& os = std::cout);

} // namespace libzork::runner
