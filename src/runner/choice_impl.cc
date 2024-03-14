#include "runner/choice_impl.hh"

#include <libzork/exceptions.hh>
#include <sstream>

#include "exceptions.hh"
#include "story/node_impl.hh"

namespace libzork::runner
{
    ChoiceRunnerImpl::ChoiceRunnerImpl(std::unique_ptr<story::Story> story,
                                       std::istream& is, std::ostream& os)
        : ChoiceRunner(std::move(story), is, os)
    {}

    void ChoiceRunnerImpl::print_script() const
    {
        InteractiveRunner::print_script();

        std::vector<std::string> choices =
            story_->get_current()->list_choices();

        int line = 1;
        for (auto i = choices.begin(); i != choices.end(); ++i, line++)
        {
            os_ << std::to_string(line) << ". " << *i << "\n";
        }
        os_ << "\n";
    }

    void ChoiceRunnerImpl::process_input()
    {
        std::string token;
        std::getline(is_, token);

        if (token.find_first_not_of("0123456789") != std::string::npos
            || token.empty())
            throw RunnerInterrupt("Please input only an integer");

        unsigned long n = std::stoul(token);
        unsigned long len = story_->get_current()->list_choices().size();

        if (n <= 0 || n > len)
            throw RunnerInterrupt("Please input an integer between 1 and "
                                  + std::to_string(len));

        const story::Node* node = story_->get_current()->make_choice(n - 1);

        story_->set_current(node);
    }
} // namespace libzork::runner
