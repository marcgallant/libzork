#include "vars/condition_impl.hh"

#include <algorithm>
#include <map>
#include <utility>

#include "exceptions.hh"

namespace libzork::vars
{

    bool ConditionImpl::apply() const
    {
        return condition_(store_.get_variable(variable_), value_);
    }

    ConditionImpl::ConditionImpl(const store::Store& store,
                                 const std::string& variable,
                                 std::function<bool(int, int)> condition,
                                 int value)
        : store_(store)
        , variable_(variable)
        , condition_(std::move(condition))
        , value_(value)
    {}

} // namespace libzork::vars
