#include "store/store_impl.hh"

#include <libzork/story/story.hh>
#include <yaml-cpp/yaml.h>

//#include "constants.hh"
#include "exceptions.hh"
#include "story/story_impl.hh"

namespace libzork::store
{
    const story::Node* StoreImpl::get_active_node() const
    {
        return node_;
    }

    void StoreImpl::set_active_node(const story::Node* node)
    {
        node_ = node;
    }

    bool StoreImpl::has_variable(const std::string& name) const
    {
        return variables_.find(name) != variables_.end();
    }

    int StoreImpl::get_variable(const std::string& name) const
    {
        auto i = variables_.find(name);
        if (i == variables_.end())
            throw InvalidVariable(name);

        return i->second;
    }

    void StoreImpl::set_variable(const std::string& name, int value)
    {
        auto i = variables_.find(name);
        if (i == variables_.end())
            variables_.emplace(name, value);
        else
            i->second = value;
    }

    void StoreImpl::save(std::ostream& os) const
    {
        YAML::Emitter emitter;
        emitter << YAML::BeginMap;

        if (node_ != nullptr)
            emitter << YAML::Key << "active-node" << YAML::Value
                    << node_->get_name();
        else
            emitter << YAML::Key << "active-node" << YAML::Value << "null";

        emitter << YAML::Key << "variables";
        emitter << variables_;

        emitter << YAML::EndMap;
        os << emitter.c_str();
    }

    void StoreImpl::restore(std::istream& is, const story::Story& story)
    {
        YAML::Node doc = YAML::Load(is);
        if (doc.IsNull())
            throw std::runtime_error("Invalid input stream");

        auto node_name = doc["active-node"].as<std::string>();
        auto variables = doc["variables"].as<std::map<std::string, int>>();

        const auto* story_impl = dynamic_cast<const story::StoryImpl*>(&story);
        story::Node* node = story_impl->get_node(node_name);

        node_ = node;
        variables_ = variables;
    }

} // namespace libzork::store
