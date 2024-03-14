#include <libzork/runner/choice.hh>

#include "exceptions.hh"
#include "runner/choice_impl.hh"

namespace libzork::runner
{
    std::unique_ptr<ChoiceRunner>
    make_choice_runner(std::unique_ptr<story::Story> story, std::istream& is,
                       std::ostream& os)
    {
        return std::make_unique<ChoiceRunnerImpl>(std::move(story), is, os);
    }

} // namespace libzork::runner
