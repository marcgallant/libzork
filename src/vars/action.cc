#include <functional>
#include <libzork/vars/action.hh>

#include "exceptions.hh"
#include "vars/action_impl.hh"

namespace libzork::vars
{

    std::unique_ptr<Action> make_action(store::Store& store,
                                        const std::string& variable,
                                        const std::string& action, int value)
    {
        std::function<void(int&, int)> cmp;

        if (action.compare("assign") == 0)
            cmp = [](int& a, int b) { a = b; };
        else if (action.compare("add") == 0)
            cmp = [](int& a, int b) { a += b; };
        else if (action.compare("sub") == 0)
            cmp = [](int& a, int b) { a -= b; };
        else
            throw InvalidComparison(action);

        return std::make_unique<ActionImpl>(store, variable, cmp, value);
    }

} // namespace libzork::vars
