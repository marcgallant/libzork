#pragma once

#include <libzork/story/story.hh>

#include "node_impl.hh"
#include "store/store_impl.hh"
#include "yaml-cpp/node/node.h"

namespace libzork::story
{
    class StoryImpl : public Story
    {
    public:
        StoryImpl(std::string title, std::string script_path,
                  std::vector<std::unique_ptr<Node>> nodes,
                  std::unique_ptr<store::Store> store);
        ~StoryImpl() override = default;

        const std::string& get_title() const override;
        const Node* get_current() const override;
        void set_current(const Node* node) override;

        Node* get_node(std::string name) const;
        std::vector<std::unique_ptr<Node>> get_nodes();
        const store::Store* get_store() const override;
        std::ostream& display(std::ostream& os) const override;

    private:
        std::string title_;
        fs::path script_path_;
        std::vector<std::unique_ptr<Node>> nodes_;
        std::unique_ptr<store::Store> store_;
    };

} // namespace libzork::story
