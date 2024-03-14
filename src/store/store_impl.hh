#pragma once

#include <libzork/store/store.hh>
#include <map>
#include <vector>

namespace libzork::store
{
    class StoreImpl
        : public Store
        , public SaveStore
    {
    public:
        ~StoreImpl() override = default;

        void save(std::ostream& os) const override;

        void restore(std::istream& is, const story::Story& story) override;

        const story::Node* get_active_node() const override;
        void set_active_node(const story::Node* node) override;

        bool has_variable(const std::string& name) const override;
        int get_variable(const std::string& name) const override;
        void set_variable(const std::string& name, int value) override;

    private:
        const story::Node* node_ = nullptr;
        std::map<std::string, int> variables_;
    };

} // namespace libzork::store
