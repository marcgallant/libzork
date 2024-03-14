#pragma once

#include <memory>
#include <string>

namespace libzork::story
{

    // Forward declaration because of the recursive dependencies
    // store.hh -> node.hh -> (action|condition).hh -> store.hh
    class Node;
    class Story;

} // namespace libzork::story

namespace libzork::store
{

    class Store
    {
    public:
        virtual ~Store() = default;

        virtual const story::Node* get_active_node() const = 0;
        virtual void set_active_node(const story::Node* node) = 0;

        virtual bool has_variable(const std::string& name) const = 0;
        virtual int get_variable(const std::string& name) const = 0;
        virtual void set_variable(const std::string& name, int value) = 0;
    };

    std::unique_ptr<Store> make_store();

    class UndoStore
    {
    public:
        virtual ~UndoStore() = default;

        virtual void new_state() = 0;
        virtual bool undo() = 0;
        virtual bool redo() = 0;
    };

    class SaveStore
    {
    public:
        virtual ~SaveStore() = default;

        virtual void save(std::ostream& os) const = 0;
        virtual void restore(std::istream& is, const story::Story& story) = 0;
    };

} // namespace libzork::store
