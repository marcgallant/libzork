#pragma once

#include <functional>
#include <libzork/vars/action.hh>

namespace libzork::vars
{
    class ActionImpl : public Action
    {
    public:
        ActionImpl(store::Store& store, const std::string& variable,
                   std::function<void(int&, int)> action, int value);
        ~ActionImpl() override = default;

        void apply() const override;

    private:
        store::Store& store_;
        const std::string variable_;
        std::function<void(int&, int)> action_;
        int value_;
    };

} // namespace libzork::vars
