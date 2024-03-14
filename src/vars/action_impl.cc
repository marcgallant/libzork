#include "vars/action_impl.hh"

#include <algorithm>
#include <map>
#include <utility>

#include "exceptions.hh"

namespace libzork::vars
{

    void ActionImpl::apply() const
    {
        int val = store_.get_variable(variable_);
        action_(val, value_);

        store_.set_variable(variable_, val);
    }

    ActionImpl::ActionImpl(store::Store& store, const std::string& variable,
                           std::function<void(int&, int)> action, int value)
        : store_(store)
        , variable_(variable)
        , action_(std::move(action))
        , value_(value)
    {}

} // namespace libzork::vars
