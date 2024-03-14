#include <libzork/exceptions.hh>
#include <libzork/runner/interactive.hh>

#include "exceptions.hh"

namespace libzork::runner
{
    InteractiveRunner::InteractiveRunner(std::unique_ptr<story::Story> story,
                                         std::istream& is, std::ostream& os)
        : Runner(std::move(story))
        , is_(is)
        , os_(os)
    {}

    void InteractiveRunner::print_script() const
    {
        const story::Node* node = story_->get_current();
        if (node != nullptr)
            os_ << node->get_text() << "\n";
    }

    void InteractiveRunner::run()
    {
        bool tmp = true;
        while (story_->get_current()->list_choices().size() != 0)
        {
            if (tmp)
                print_script();

            os_ << "> ";
            try
            {
                process_input();
                tmp = true;
            }
            catch (const RunnerInterrupt& e)
            {
                os_ << e.what() << "\n";
                tmp = false;
            }
        }
        print_script();
    }

} // namespace libzork::runner
