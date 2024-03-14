#pragma once

#include <filesystem>
#include <libzork/vars/action.hh>
#include <libzork/vars/condition.hh>
#include <memory>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace libzork::story
{

    class Node
    {
    public:
        virtual ~Node() = default;

        virtual const std::string& get_name() const = 0;
        virtual const std::string& get_text() const = 0;

        virtual const Node* make_choice(std::size_t index) const = 0;

        virtual std::vector<std::string>
        list_choices(bool check_conditions = true) const = 0;
        virtual void add_choice(
            const Node* other, const std::string& text,
            std::vector<std::unique_ptr<vars::Condition>> conditions = {},
            std::vector<std::unique_ptr<vars::Action>> operations = {}) = 0;
    };

    std::unique_ptr<Node> make_node(const std::string& name,
                                    const fs::path& script_path);

} // namespace libzork::story
