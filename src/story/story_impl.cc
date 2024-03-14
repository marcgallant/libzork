#include "story/story_impl.hh"

#include <cassert>
//#include <httplib.h>
#include <algorithm>
#include <libzork/store/store.hh>

//#include "constants.hh"
#include "exceptions.hh"

namespace libzork::story
{
    StoryImpl::StoryImpl(std::string title, std::string script_path,
                         std::vector<std::unique_ptr<Node>> nodes,
                         std::unique_ptr<store::Store> store)
        : title_(title)
        , script_path_(script_path)
        , nodes_(std::move(nodes))
        , store_(std::move(store))
    {
        if (!nodes_.empty())
            store_->set_active_node(nodes_.at(0).get());
    }

    Node* StoryImpl::get_node(std::string name) const
    {
        for (auto i = nodes_.begin(); i != nodes_.end(); ++i)
        {
            if ((*i)->get_name() == name)
                return (*i).get();
        }
        return nullptr;
    }

    const std::string& StoryImpl::get_title() const
    {
        return title_;
    }

    const Node* StoryImpl::get_current() const
    {
        return store_->get_active_node();
    }

    void StoryImpl::set_current(const Node* node)
    {
        store_->set_active_node(node);
    }

    const store::Store* StoryImpl::get_store() const
    {
        return store_.get();
    }

    std::ostream& StoryImpl::display(std::ostream& os) const
    {
        os << "digraph \"" << title_ << "\" {\n";

        for (auto i = nodes_.begin(); i != nodes_.end(); ++i)
        {
            NodeImpl* nodeimpl = dynamic_cast<NodeImpl*>(i->get());
            const std::vector<Choice>& choice = nodeimpl->get_choices();

            for (auto j = choice.begin(); j != choice.end(); ++j)
            {
                os << "\t\"" << nodeimpl->get_name() << "\" -> \""
                   << j->get_target()->get_name() << "\"\n";
            }
        }

        return os << "}\n";
    }

    std::vector<std::unique_ptr<Node>> StoryImpl::get_nodes()
    {
        return std::move(nodes_);
    }
} // namespace libzork::story
