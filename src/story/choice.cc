#include "choice.hh"

namespace libzork::story
{
    Choice::Choice(const Node* target, const std::string& text,
                   condition_type conditions, action_type operations)
        : target_(target)
        , text_(text)
        , conditions_(std::move(conditions))
        , operations_(std::move(operations))
    {}

    const Node* Choice::get_target() const
    {
        return target_;
    }

    const std::string& Choice::get_text() const
    {
        return text_;
    }

    bool Choice::check_conditions() const
    {
        for (auto it = conditions_.begin(); it != conditions_.end(); ++it)
        {
            if (!it->get()->apply())
                return false;
        }
        return true;
    }

    void Choice::apply_operations() const
    {
        for (auto it = operations_.begin(); it != operations_.end(); ++it)
        {
            it->get()->apply();
        }
    }

} // namespace libzork::story
