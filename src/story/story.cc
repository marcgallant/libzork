#include <fstream>
#include <libzork/story/story.hh>

#include "exceptions.hh"
#include "story/story_impl.hh"
#include "yaml-cpp/parser.h"
#include "yaml-cpp/yaml.h"

namespace libzork::story
{
    Node* find_node(std::string name,
                    const std::vector<std::unique_ptr<Node>>& nodes)
    {
        for (auto i = nodes.begin(); i != nodes.end(); ++i)
        {
            if ((*i)->get_name() == name)
                return (*i).get();
        }
        return nullptr;
    }

    std::unique_ptr<Story> make_story(const fs::path& path)
    {
        YAML::Node doc = YAML::LoadFile(path);
        if (doc.IsNull())
            throw std::runtime_error("Invalid story path");

        auto title = doc["title"].as<std::string>();
        auto script_path = doc["scripts-path"].as<std::string>();

        std::unique_ptr<store::Store> store = store::make_store();
        auto variables = doc["variables"];
        for (auto i = variables.begin(); i != variables.end(); ++i)
        {
            auto name = (*i)["name"].as<std::string>();
            auto value = (*i)["value"].as<int>();
            store->set_variable(name, value);
        }

        std::vector<std::unique_ptr<Node>> nodes;
        std::map<std::string, Node*> map;

        auto story = doc["story"];
        for (auto i = story.begin(); i != story.end(); ++i)
        {
            auto name = (*i)["name"].as<std::string>();
            auto script = (*i)["script"].as<std::string>();

            auto tmp = path.parent_path();
            if (!tmp.parent_path().empty())
            {
                auto node =
                    make_node(name, path.parent_path() / script_path / script);
                nodes.push_back(std::move(node));
            }
            else
            {
                auto node =
                    make_node(name, script_path.append("/").append(script));
                nodes.push_back(std::move(node));
            }
        }

        for (auto i = story.begin(); i != story.end(); ++i)
        {
            auto name = (*i)["name"].as<std::string>();
            Node* node = find_node(name, nodes);

            auto choice = (*i)["choices"];
            for (auto j = choice.begin(); j != choice.end(); ++j)
            {
                auto text = (*j)["text"].as<std::string>();
                auto target = (*j)["target"].as<std::string>();

                std::vector<std::unique_ptr<vars::Condition>> conditions;
                auto condition = (*j)["conditions"];
                for (auto k = condition.begin(); k != condition.end(); ++k)
                {
                    auto condition_name = (*k)["name"].as<std::string>();
                    auto comparison = (*k)["comparison"].as<std::string>();
                    auto value = (*k)["value"].as<int>();

                    conditions.push_back(vars::make_condition(
                        *store, condition_name, comparison, value));
                }

                std::vector<std::unique_ptr<vars::Action>> operations;
                auto actions = (*j)["actions"];
                for (auto k = actions.begin(); k != actions.end(); ++k)
                {
                    auto action_name = (*k)["name"].as<std::string>();
                    auto operation = (*k)["operation"].as<std::string>();
                    auto value = (*k)["value"].as<int>();

                    operations.push_back(vars::make_action(*store, action_name,
                                                           operation, value));
                }

                node->add_choice(find_node(target, nodes), text,
                                 std::move(conditions), std::move(operations));
            }
        }
        return std::make_unique<StoryImpl>(title, script_path, std::move(nodes),
                                           std::move(store));
    }

} // namespace libzork::story
