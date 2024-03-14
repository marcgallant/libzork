#pragma once

#include <libzork/story/node.hh>

#include "story/choice.hh"
#include "yaml-cpp/node/node.h"

using condition_type = std::vector<std::unique_ptr<libzork::vars::Condition>>;
using action_type = std::vector<std::unique_ptr<libzork::vars::Action>>;

namespace libzork::story
{
    class NodeImpl : public Node
    {
    public:
        NodeImpl(std::string name, std::string text);
        ~NodeImpl() override = default;

        const std::string& get_name() const override;
        const std::string& get_text() const override;

        const std::vector<Choice>& get_choices() const;

        const Node* make_choice(std::size_t index) const override;
        std::vector<std::string>
        list_choices(bool check_conditions = true) const override;
        void add_choice(const Node* other, const std::string& text,
                        condition_type conditions = {},
                        action_type operations = {}) override;

    private:
        std::string name_;
        std::string text_;
        std::vector<Choice> choices_;
    };

} // namespace libzork::story
