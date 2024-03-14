#pragma once

#include <libzork/story/node.hh>

#include "yaml-cpp/node/node.h"

using condition_type = std::vector<std::unique_ptr<libzork::vars::Condition>>;
using action_type = std::vector<std::unique_ptr<libzork::vars::Action>>;

namespace libzork::story
{
    class Choice
    {
    public:
        Choice(const Node* target, const std::string& text,
               condition_type conditions = {}, action_type operations = {});

        const Node* get_target() const;
        const std::string& get_text() const;

        bool check_conditions() const;

        void apply_operations() const;

    private:
        const Node* target_;
        std::string text_;
        condition_type conditions_;
        action_type operations_;
    };
} // namespace libzork::story
