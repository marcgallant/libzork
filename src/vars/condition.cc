#include <libzork/store/store.hh>
#include <libzork/vars/condition.hh>

#include "exceptions.hh"
#include "vars/condition_impl.hh"

namespace libzork::vars
{

    std::unique_ptr<Condition> make_condition(const store::Store& store,
                                              const std::string& variable,
                                              const std::string& comparison,
                                              int value)
    {
        std::function<bool(int, int)> cmp;
        if (comparison.compare("equal") == 0)
            cmp = [](int a, int b) { return a == b; };
        else if (comparison.compare("greater") == 0)
            cmp = [](int a, int b) { return a > b; };
        else if (comparison.compare("lower") == 0)
            cmp = [](int a, int b) { return a < b; };
        else if (comparison.compare("greater_equal") == 0)
            cmp = [](int a, int b) { return a >= b; };
        else if (comparison.compare("lower_equal") == 0)
            cmp = [](int a, int b) { return a <= b; };
        else
            throw InvalidComparison(comparison);

        return std::make_unique<ConditionImpl>(store, variable, cmp, value);
    }

} // namespace libzork::vars
