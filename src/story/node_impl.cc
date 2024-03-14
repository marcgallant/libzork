#include "story/node_impl.hh"

#include <algorithm>
#include <vector>

#include "exceptions.hh"

namespace libzork::story
{
    NodeImpl::NodeImpl(std::string name, std::string text)
        : name_(name)
        , text_(text)
    {}

    const std::string& NodeImpl::get_name() const
    {
        return name_;
    }

    const std::string& NodeImpl::get_text() const
    {
        return text_;
    }

    const std::vector<Choice>& NodeImpl::get_choices() const
    {
        return choices_;
    }

    const Node* NodeImpl::make_choice(size_t index) const
    {
        for (auto it = choices_.begin(); it != choices_.end(); ++it)
        {
            if (it->check_conditions())
            {
                if (index == 0)
                {
                    it->apply_operations();
                    return it->get_target();
                }

                index--;
            }
        }

        return nullptr;
    }
    std::vector<std::string> NodeImpl::list_choices(bool check_conditions) const
    {
        std::vector<std::string> res;
        for (auto it = choices_.begin(); it != choices_.end(); ++it)
        {
            if (!check_conditions || it->check_conditions())
                res.push_back(it->get_text());
        }
        return res;
    }

    void NodeImpl::add_choice(const Node* other, const std::string& text,
                              condition_type conditions, action_type operations)
    {
        Choice choice(other, text, std::move(conditions),
                      std::move(operations));
        choices_.push_back(std::move(choice));
    }

} // namespace libzork::story
