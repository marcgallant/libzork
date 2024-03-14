#pragma once

#include <filesystem>
#include <libzork/story/node.hh>
#include <memory>

namespace fs = std::filesystem;

namespace libzork::story
{

    class Story
    {
    public:
        virtual ~Story() = default;

        virtual const std::string& get_title() const = 0;
        virtual const Node* get_current() const = 0;
        virtual void set_current(const Node* node) = 0;
        virtual const store::Store* get_store() const = 0;
        virtual std::ostream& display(std::ostream& os) const = 0;
    };

    std::unique_ptr<Story> make_story(const fs::path& path);

} // namespace libzork::story
