#pragma once

#include <libzork/store/store.hh>
#include <string>

namespace libzork::vars
{

    class Action
    {
    public:
        virtual ~Action() = default;

        virtual void apply() const = 0;
    };

    std::unique_ptr<Action> make_action(store::Store& store,
                                        const std::string& variable,
                                        const std::string& action, int value);

} // namespace libzork::vars
